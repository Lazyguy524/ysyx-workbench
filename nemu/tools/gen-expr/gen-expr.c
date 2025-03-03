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
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>

#define BUF_SIZE 65536
#define MAX_DEPTH 10  // 限制表达式嵌套深度，防止过于复杂

// this should be enough
static char buf[BUF_SIZE] = {};
static char code_buf[65536 + 128] = {}; // a little larger than `buf`
static char *code_format =
"#include <stdio.h>\n"
"int main() { "
"  unsigned result = %s; "
"  printf(\"%%u\", result); "
"  return 0; "
"}";

static size_t pos = 0; // 跟踪buf的位置
static int expr_depth = 0; // 跟踪表达式嵌套深度

// 生成单个字符
static void gen_char(char c) {
  if (pos < BUF_SIZE - 1) {
    buf[pos++] = c;
    buf[pos] = '\0';
  }
}

// 生成随机数字，范围为0-19
static void gen_num() {
  if (pos >= BUF_SIZE - 3) return;
  int num = rand() % 20; // 生成0到19的数字
  pos += sprintf(buf + pos, "%d", num);
}

// 生成随机操作符，增加权重减少除法出现频率
static void gen_rand_op() {
  if (pos >= BUF_SIZE - 1) return;
  int op_choice = rand() % 10; // 使用更大范围调整操作符权重
  char op;
  
  if (op_choice < 4) {
    op = '+'; // 40%的几率是加法
  } else if (op_choice < 7) {
    op = '-'; // 30%的几率是减法
  } else if (op_choice < 9) {
    op = '*'; // 20%的几率是乘法
  } else {
    op = '/'; // 只有10%的几率是除法
  }
  
  gen_char(op);
}

// 前向声明
static void gen_safe_expr();

// 生成安全的除法表达式，确保除数不为0
static void gen_safe_division() {
  gen_char('(');
  
  // 左操作数可以是任意表达式
  gen_safe_expr();
  
  gen_char('/');
  
  // 右操作数(除数)：1-9的数字或者1+复杂表达式，避免为0
  if (rand() % 2 == 0 || expr_depth > MAX_DEPTH/2) {
    // 直接使用非零数字
    int divisor = rand() % 9 + 1; // 1到9的数字
    pos += sprintf(buf + pos, "%d", divisor);
  } else {
    // 使用1+表达式，确保结果大于0
    gen_char('(');
    gen_char('1');
    gen_char('+');
    gen_char('(');
    
    expr_depth++;
    gen_safe_expr();
    expr_depth--;
    
    gen_char(')');
    gen_char(')');
  }
  
  gen_char(')');
}

// 生成安全的表达式
static void gen_safe_expr() {
  if (pos >= BUF_SIZE - 10 || expr_depth > MAX_DEPTH) {
    // 如果缓冲区接近满或表达式嵌套太深，只生成简单数字
    gen_num();
    return;
  }
  
  expr_depth++;
  
  // 调整生成选项的权重，增加数字和简单运算的概率
  int choice;
  if (expr_depth < 3) {
    // 深度较浅时，更倾向于生成复杂表达式
    choice = rand() % 10;
  } else if (expr_depth < 6) {
    // 中等深度时，减少复杂表达式的生成
    choice = rand() % 10;
    if (choice >= 6) choice = 0; // 增加生成数字的概率
  } else {
    // 深度较深时，大幅减少复杂表达式
    choice = rand() % 10;
    if (choice >= 3) choice = 0; // 大大增加生成数字的概率
  }
  
  if (choice < 4) { // 40%的几率生成数字
    gen_num();
  }
  else if (choice < 7) { // 30%的几率生成括号表达式
    gen_char('(');
    gen_safe_expr();
    gen_char(')');
  }
  else if (choice < 9) { // 20%的几率生成普通二元运算
    gen_char('('); // 用括号包裹以确保正确的运算顺序
    
    gen_safe_expr();
    
    // 根据运算符类型分别处理
    int op_type = rand() % 10;
    if (op_type < 9) { // 90%是+,-,*运算符
      gen_rand_op();
      gen_safe_expr();
    } else { // 10%是除法，需要特殊处理
      gen_char('/');
      // 确保除数非零
      if (rand() % 2 == 0) {
        int divisor = rand() % 9 + 1; // 1到9的非零数
        pos += sprintf(buf + pos, "%d", divisor);
      } else {
        gen_char('(');
        gen_char('1');
        gen_char('+');
        gen_safe_expr();
        gen_char(')');
      }
    }
    
    gen_char(')');
  }
  else { // 10%的几率生成安全除法表达式
    gen_safe_division();
  }
  
  expr_depth--;
}

// 主表达式生成入口函数
static void gen_rand_expr() {
  pos = 0;
  buf[0] = '\0';
  expr_depth = 0;
  gen_safe_expr();
}

// 验证表达式的合法性
static int validate_expr(const char *expr) {
  // 检查是否含有连续的操作符，这通常是非法的
  for (int i = 0; expr[i] && expr[i+1]; i++) {
    if ((expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/') &&
        (expr[i+1] == '+' || expr[i+1] == '-' || expr[i+1] == '*' || expr[i+1] == '/')) {
      return 0; // 发现连续操作符，非法
    }
  }
  
  // 简单检查括号匹配
  int bracket_count = 0;
  for (int i = 0; expr[i]; i++) {
    if (expr[i] == '(') bracket_count++;
    else if (expr[i] == ')') bracket_count--;
    
    if (bracket_count < 0) return 0; // 右括号多于左括号，非法
  }
  if (bracket_count != 0) return 0; // 左括号多于右括号，非法
  
  return 1; // 通过基本合法性检查
}

int main(int argc, char *argv[]) {
  int seed = time(0);
  srand(seed);
  int loop = 1;
  if (argc > 1) {
    sscanf(argv[1], "%d", &loop);
  }
  
  int i;
  for (i = 0; i < loop; i++) {
    // 生成并验证表达式，最多尝试10次
    int valid = 0;
    int attempts = 0;
    
    while (!valid && attempts < 10) {
      gen_rand_expr();
      valid = validate_expr(buf);
      attempts++;
      
      if (!valid) {
        // 如果表达式不合法，清空缓冲区重新生成
        pos = 0;
        buf[0] = '\0';
      }
    }
    
    // 如果10次尝试后仍然无法生成合法表达式，生成一个简单的有效表达式
    if (!valid) {
      pos = 0;
      pos += sprintf(buf + pos, "5"); // 使用一个简单的数字(0-9范围内)
    }
    
    sprintf(code_buf, code_format, buf);
    
    FILE *fp = fopen("/tmp/.code.c", "w");
    assert(fp != NULL);
    fputs(code_buf, fp);
    fclose(fp);
    
    int ret = system("gcc /tmp/.code.c -o /tmp/.expr");
    if (ret != 0) {
      printf("编译失败: %s\n", buf);
      continue; // 编译失败，跳过当前表达式
    }
    
    fp = popen("/tmp/.expr", "r");
    assert(fp != NULL);
    unsigned result;
    ret = fscanf(fp, "%u", &result);
    pclose(fp);
    
    if (ret == 1) { // 确保成功读取了结果
      printf("%u %s\n", result, buf);
    } else {
      printf("计算失败: %s\n", buf);
    }
  }
  
  return 0;
}