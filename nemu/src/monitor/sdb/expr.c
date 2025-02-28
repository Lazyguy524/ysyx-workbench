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
* See the Mulan PSL v2 for more details.
***************************************************************************************/

#include <isa.h>

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <regex.h>

enum {
  TK_NOTYPE = 256, TK_EQ,num,

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
  {"[0-9]+", num},    //num
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

  nr_token = 0;
  int num_pot = -1;
  while (e[position] != '\0') {
    /* Try all rules one by one. */
    for (i = 0; i < NR_REGEX; i ++) {
      if (regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) {
        char *substr_start = e + position;
        int substr_len = pmatch.rm_eo;

        Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s",
            i, rules[i].regex, position, substr_len, substr_len, substr_start);

        position += substr_len;
        if (nr_token >= 32) {
          printf("Error: Too many tokens, tokens array is full.\n");
          return false;
        }
        /* TODO: Now a new token is recognized with rules[i]. Add codes
         * to record the token in the array `tokens'. For certain types
         * of tokens, some extra actions should be performed.
         */
        switch (rules[i].token_type) {
          case num:
            num_pot = nr_token;
            tokens[num_pot].type = rules[i].token_type;
            tokens[num_pot].str[0] = *substr_start;
            tokens[num_pot].str[1] = '\0';
            nr_token++;
            break;
          case '+':
            num_pot = nr_token;
            tokens[num_pot].type = rules[i].token_type;
            tokens[num_pot].str[0] = *substr_start;
            tokens[num_pot].str[1] = '\0';
            nr_token++;
            break;
          case '-':
            num_pot = nr_token;
            tokens[num_pot].type = rules[i].token_type;
            tokens[num_pot].str[0] = *substr_start;
            tokens[num_pot].str[1] = '\0';
            nr_token++;
            break;
          case '*':
            num_pot = nr_token;
            tokens[num_pot].type = rules[i].token_type;
            tokens[num_pot].str[0] = *substr_start;
            tokens[num_pot].str[1] = '\0';
            nr_token++;
            break;
          case '/':
            num_pot = nr_token;
            tokens[num_pot].type = rules[i].token_type;
            tokens[num_pot].str[0] = *substr_start;
            tokens[num_pot].str[1] = '\0';
            nr_token++;
            break;
          case '(':
            num_pot = nr_token;
            tokens[num_pot].type = rules[i].token_type;
            tokens[num_pot].str[0] = *substr_start;
            tokens[num_pot].str[1] = '\0';
            nr_token++;
            break;
          case ')':
            num_pot = nr_token;
            tokens[num_pot].type = rules[i].token_type;
            tokens[num_pot].str[0] = *substr_start;
            tokens[num_pot].str[1] = '\0';
            nr_token++;
            break;
          default: TODO();
        }

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

// bool check_parentheses(int start_point, int end_point) {
//   int left_count = 0;  // 记录'('的数量
//   int right_count = 0; // 记录')'的数量
//   int left_most = -1; // 记录第一个'('的位置
//   int right_most = -1;   // 记录最后一个')'的位置
//   int size = end_point-start_point+1;
//   printf("Now is in check,the start_point is : %d, the end_point is : %d\n",start_point,end_point);
//   // 遍历数组，统计'('和')'的数量，并记录它们的位置
//   for (int i = start_point; i < size; i++) {
//     if (tokens[i].str[0] == '(') {
//       left_count++;
//       if (left_most == -1) {
//         left_most = i; // 记录第一个'('的位置
//       }
//     } else if (tokens[i].str[0] == ')') {
//       right_count++;
//       right_most = i; // 更新最后一个')'的位置
//     }
//   }

//   // ① 检查'('和')'的数量是否匹配
//   assert(left_count == right_count);

//   // ② 检查每个'('是否与最靠近数组末尾的')'匹配
//   int left_ptr = 0;  // 从左向右扫描
//   int right_ptr = size - 1; // 从右向左扫描
//   while (left_ptr <= right_ptr) {
//     // 找到下一个'('
//     while (left_ptr <= right_ptr && tokens[left_ptr].str[0] != '(') {
//       left_ptr++;
//     }
//     // 找到下一个')'
//     while (left_ptr <= right_ptr && tokens[right_ptr].str[0] != ')') {
//       right_ptr--;
//     }
//     // 如果')'的索引小于'('的索引，则assert
//     if (left_ptr <= right_ptr && right_ptr < left_ptr) {
//       assert(false);
//     }
//     // 匹配成功，继续检查下一对
//     left_ptr++;
//     right_ptr--;
//   }

//   // ③ 检查start_point和end_point位置是否是'('和')'
//   if (left_most != -1 && right_most != -1 &&
//       tokens[left_most].str[0] == '(' &&
//       tokens[right_most].str[0] == ')') {
//     return true;
//   }

//   return false;
// }

bool check_parentheses(int start_point, int end_point) {
  int left_count = 0;  // Count of '('
  int right_count = 0; // Count of ')'
  
  printf("Now is in check, the start_point is: %d, the end_point is: %d\n", start_point, end_point);
  
  // Check if the expression starts with '(' and ends with ')'
  if (tokens[start_point].type != '(' || tokens[end_point].type != ')') {
    return false;
  }
  
  // Check if the outermost brackets match
  int bracket_level = 0;
  for (int i = start_point; i <= end_point; i++) {
    if (tokens[i].type == '(') {
      left_count++;
      bracket_level++;
    } else if (tokens[i].type == ')') {
      right_count++;
      bracket_level--;
      
      // If bracket_level becomes 0 before the end, then the expression is not
      // surrounded by a pair of matching parentheses
      if (bracket_level == 0 && i != end_point) {
        return false;
      }
    }
    
    // Bracket level should never go negative
    if (bracket_level < 0) {
      return false;
    }
  }
  
  // Check if the number of '(' and ')' are equal
  if (left_count != right_count) {
    return false;
  }
  
  // If we reached here, the expression is surrounded by a pair of matching parentheses
  return true;
}

// int find_last_operator(int start_point,int end_point) {
//   int a = -1; // 最小左括号位置
//   int b = -1; // 最大右括号位置
//   int size = end_point - start_point;
//   // ① 找到最小左括号和最大右括号的位置
//   for (int i = 0; i < size; i++) {
//     if (tokens[i].str[0] == '(') {
//       if (a == -1 || i < a) {
//         a = i;
//       }
//     } else if (tokens[i].str[0] == ')') {
//       if (b == -1 || i > b) {
//         b = i;
//       }
//     }
//   }

//   // ② 找到区间外的所有符号，并统计+-和*/的出现次数
//   int plus_minus_count = 0; // +-的计数
//   int mul_div_count = 0;    // */的计数
//   int last_plus_minus_pos = -1; // 最后一个+-符号的位置
//   int last_mul_div_pos = -1;    // 最后一个*/符号的位置

//   for (int i = 0; i < size; i++) {
//     // 如果当前位置在区间外
//     if (i < a || i > b) {
//       if (tokens[i].str[0] == '+' || tokens[i].str[0] == '-') {
//         plus_minus_count++;
//         last_plus_minus_pos = i;
//       } else if (tokens[i].str[0] == '*' || tokens[i].str[0] == '/') {
//         mul_div_count++;
//         last_mul_div_pos = i;
//       }
//     }
//   }

//   // ③ 判断表达式中是否同时存在+-和*/两种运算顺序不同的符号
//   if (plus_minus_count > 0 && mul_div_count > 0) {
//     // 同时存在+-和*/，返回最后一个+-符号的位置
//     return last_plus_minus_pos;
//   } else if (plus_minus_count > 0) {
//     // 只有+-，返回最后一个+-符号的位置
//     return last_plus_minus_pos;
//   } else if (mul_div_count > 0) {
//     // 只有*/，返回最后一个*/符号的位置
//     return last_mul_div_pos;
//   } else {
//     // 既没有+-也没有*/，返回-1表示没有符号
//     return -1;
//   }
// }


  int find_last_operator(int start_point, int end_point) {
  int position = -1;
  int priority = 0;  // Priority: 0 = none, 1 = +/-, 2 = */
  int bracket_level = 0;
  
  // Scan the expression from left to right
  for (int i = start_point; i <= end_point; i++) {
    if (tokens[i].type == '(') {
      bracket_level++;
    } else if (tokens[i].type == ')') {
      bracket_level--;
    } else if (bracket_level == 0) {
      // Only consider operators outside of brackets
      if (tokens[i].type == '+' || tokens[i].type == '-') {
        // +/- has lower precedence, so it should be considered last
        position = i;
        priority = 1;
      } else if ((tokens[i].type == '*' || tokens[i].type == '/') && priority < 1) {
        // */÷ has higher precedence, only update if we haven't found +/-
        position = i;
        priority = 2;
      }
    }
  }
  
  return position;
}

static int eval(int start_point,int end_point){
  printf("Now is caculate :");
  for (int i = start_point; i < end_point +1; i++)
  {
    printf("%s",tokens[i].str);
  }
  printf("\n");
  if ( start_point > end_point){
    assert("Bad Expression!");
  }
  else if (start_point == end_point){
    return atoi(tokens[start_point].str);
  }
  else if (check_parentheses(start_point,end_point) == true){
    printf("delete the leftmost and rightmost!\n");
    return eval(start_point + 1, end_point - 1);
  }
  else {
    int op = find_last_operator(start_point,end_point);
    printf("OUTPUT:get the op is :%s,and op is : %d\n",tokens[op].str,op);
    int op_type = tokens[op].type;
    int val1 = eval(start_point,op - 1);
    printf("OUTPUT:get the val1 is :%d\n",val1);
    int val2 = eval(op+1, end_point);
    printf("OUTPUT:get the val2 is :%d\n",val2);

    switch (op_type)
    {
    case '+':
      printf("%d + %d = %d\n",val1,val2,val1 + val2);
      return val1 + val2;
      break;
    case '-':
      printf("%d - %d = %d\n",val1,val2,val1 - val2);
      return val1 - val2;
      break;
    case '*':
      printf("%d * %d = %d\n",val1,val2,val1 * val2);
      return val1 * val2;
      break;
    case '/':
      printf("%d / %d = %d\n",val1,val2,val1 / val2);
      return val1 / val2;
      break;
    default:assert(0);
      break;
    }
  }
  return -1;
}

// 找到最后一个非空元素的位置
int find_last_non_empty_token() {
  for (int i = ARRLEN(tokens) - 1; i >= 0; i--) {
    if (tokens[i].str[0] != '\0') {
      return i;
    }
  }
  return -1; // 如果数组全部为空，返回-1
}

word_t expr(char *e, bool *success) {
  if (!make_token(e)) {
    *success = false;
    return 0;
  }
  printf("Input is :");
  for (int j = 0; j < ARRLEN(tokens); j++)
  {
    printf("%s",tokens[j].str);
  }
  
  
  printf("\n");
  
  /* TODO: Insert codes to evaluate the expression. */
  //TODO();
  int sum;
  printf("find_last_non_empty_token() is : %d\n",find_last_non_empty_token());
  sum = eval(0,find_last_non_empty_token());
  printf("The caculate result is :%d\n",sum);
  return 0;
}
