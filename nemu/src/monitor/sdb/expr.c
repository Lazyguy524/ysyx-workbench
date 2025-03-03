/***************************************************************************************
* Copyright (c) 2014-2024 Zihao Yu, Nanjing University
*
* NEMU is licensed under Mulan PSL v2.
* You can use this software according to the terms and conditions of the Mulan PSL v2.
* You may obtain a copy of Mulan PSL v2 at:
*          http://license.coscl.org.cn/MulanPSL2
*
* THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
* EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
* MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
*
* See the Mulan PSL v2 for more detail    "../tools/gen-expr/input",              // 上一级目录
    // "../../tools/gen-expr/input",           // 上两级目录
    // "../../../tools/gen-expr/input",        // 上三级目录
    // "/home/用户名/ysyx-workbench/nemu/tools/gen-expr/input"  // 替换为你的实际用户名s.
***************************************************************************************/

#include <isa.h>

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <regex.h>

enum {
  TK_NOTYPE = 256, TK_EQ, TK_NUM,

  /* TODO: Add more token types */

};

static struct rule {
  const char *regex;
  int token_type;
} rules[] = {

  /* TODO: Add more rules.
   * Pay attention to the precedence level of different rules.
   */

  {" +", TK_NOTYPE},    // spaces
  {"\\+", '+'},         // plus
  {"==", TK_EQ},        // equal
  {"\\-", '-'},         // minus
  {"\\*", '*'},         // mult
  {"\\/", '/'},         // div
  {"\\(", '('},         // paren_l
  {"\\)", ')'},         // paren_r
  {"[0-9][0-9]*", TK_NUM},   // 使用TK_NUM而不是num，保持一致性
};

#define NR_REGEX ARRLEN(rules)

static regex_t re[NR_REGEX] = {};

/* Rules are used for many times.
 * Therefore we compile them only once before any usage.
 */
void init_regex() {
  int i;
  char error_msg[128];
  int ret;

  for (i = 0; i < NR_REGEX; i ++) {
    ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
    if (ret != 0) {
      regerror(ret, &re[i], error_msg, 128);
      panic("regex compilation failed: %s\n%s", error_msg, rules[i].regex);
    }
  }
}

typedef struct token {
  int type;
  char str[32];
} Token;

static Token tokens[32] __attribute__((used)) = {};
static int nr_token __attribute__((used))  = 0;

static bool make_token(char *e) {
  int position = 0;
  int i;
  regmatch_t pmatch;

  // 初始化tokens数组
  memset(tokens, 0, sizeof(tokens));
  nr_token = 0;

  while (e[position] != '\0') {
    /* Try all rules one by one. */
    for (i = 0; i < NR_REGEX; i ++) {
      if (regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) {
        char *substr_start = e + position;
        int substr_len = pmatch.rm_eo;

        Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s",
            i, rules[i].regex, position, substr_len, substr_len, substr_start);

        position += substr_len;

        if (rules[i].token_type == TK_NOTYPE) {
          break; // 忽略空格
        }

        if (nr_token >= 32) {
          printf("Error: Too many tokens, tokens array is full.\n");
          return false;
        }
        
        /* 记录token */
        tokens[nr_token].type = rules[i].token_type;
        
        // 保存数字的完整值，而不仅仅是第一个字符
        if (rules[i].token_type == TK_NUM) {
          if (substr_len >= 32) {
            printf("Error: Number too long.\n");
            return false;
          }
          strncpy(tokens[nr_token].str, substr_start, substr_len);
          tokens[nr_token].str[substr_len] = '\0';
        } else {
          // 对于操作符，只需要保存一个字符
          tokens[nr_token].str[0] = *substr_start;
          tokens[nr_token].str[1] = '\0';
        }
        
        nr_token++;
        break;
      }
    }

    if (i == NR_REGEX) {
      printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
      return false;
    }
  }
  
  return true;
}

// 检查表达式是否被一对括号完整包围
bool check_parentheses(int start_point, int end_point) {
  // 如果表达式不是以左括号开始或右括号结束，直接返回false
  if (tokens[start_point].type != '(' || tokens[end_point].type != ')') {
    return false;
  }
  
  // 检查括号是否匹配
  int bracket_level = 0;
  for (int i = start_point; i <= end_point; i++) {
    if (tokens[i].type == '(') {
      bracket_level++;
    } else if (tokens[i].type == ')') {
      bracket_level--;
      
      // 如果在到达end_point之前括号已经完全匹配，则表达式不是被一对括号完整包围
      if (bracket_level == 0 && i != end_point) {
        return false;
      }
    }
    
    // 右括号过多，语法错误
    if (bracket_level < 0) {
      printf("Syntax error: Unmatched parentheses.\n");
      assert(0);
    }
  }
  
  // 确保括号数量匹配
  return (bracket_level == 0);
}

// 查找主操作符
int find_main_operator(int start_point, int end_point) {
  int op_position = -1;
  int priority = 0;  // 优先级: 0=未找到, 1=+/-, 2=*/
  int bracket_level = 0;
  
  // 从左到右扫描表达式
  for (int i = start_point; i <= end_point; i++) {
    if (tokens[i].type == '(') {
      bracket_level++;
    } else if (tokens[i].type == ')') {
      bracket_level--;
    } else if (bracket_level == 0) {
      // 只考虑不在括号内的操作符
      if (tokens[i].type == '+' || tokens[i].type == '-') {
        // +/- 优先级低，应该最后考虑
        op_position = i;
        priority = 1;
      } else if ((tokens[i].type == '*' || tokens[i].type == '/') && priority < 1) {
        // */ 优先级高，只有在没找到 +/- 时更新
        op_position = i;
        priority = 2;
      }
    }
  }
  
  return op_position;
}

// 递归求值函数
static word_t eval(int start_point, int end_point, bool *success) {
  if (start_point > end_point) {
    printf("Error: Bad expression range (%d > %d).\n", start_point, end_point);
    *success = false;
    return 0;
  }
  
  // 单个token，必须是数字
  if (start_point == end_point) {
    if (tokens[start_point].type == TK_NUM) {
      return atoi(tokens[start_point].str);
    } else {
      printf("Error: Expected number, got operator.\n");
      *success = false;
      return 0;
    }
  }
  
  // 处理被括号包围的表达式
  if (check_parentheses(start_point, end_point)) {
    return eval(start_point + 1, end_point - 1, success);
  }
  
  // 查找主操作符
  int op_position = find_main_operator(start_point, end_point);
  
  // 没有找到主操作符，可能是格式错误
  if (op_position == -1) {
    printf("Error: No operator found in expression.\n");
    *success = false;
    return 0;
  }
  
  // 获取操作符类型
  int op_type = tokens[op_position].type;
  
  // 递归计算左右子表达式
  word_t val1 = eval(start_point, op_position - 1, success);
  if (!*success) return 0;
  
  word_t val2 = eval(op_position + 1, end_point, success);
  if (!*success) return 0;
  
  // 执行相应的运算
  switch (op_type) {
    case '+': return val1 + val2;
    case '-': return val1 - val2;
    case '*': return val1 * val2;
    case '/':
      if (val2 == 0) {
        printf("Error: Division by zero.\n");
        *success = false;
        return 0;
      }
      return val1 / val2;
    default:
      printf("Error: Unknown operator type %d.\n", op_type);
      *success = false;
      return 0;
  }
}

word_t expr(char *e, bool *success) {
  *success = true;  // 初始化success标志
  
  if (!make_token(e)) {
    *success = false;
    return 0;
  }
  
  // 检查表达式是否为空
  if (nr_token == 0) {
    printf("Error: Empty expression.\n");
    *success = false;
    return 0;
  }
  
  // 输出解析后的表达式（调试用）
  printf("Parsed expression: ");
  for (int i = 0; i < nr_token; i++) {
    printf("%s", tokens[i].str);
  }
  printf("\n");
  
  // 计算表达式的值
  word_t result = eval(0, nr_token - 1, success);
  
  if (*success) {
    printf("Result: %u\n", result);
  }
  
  return result;
}