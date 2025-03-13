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
#include <cpu/cpu.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "sdb.h"
#include <memory/vaddr.h>

static int is_batch_mode = false;

void init_regex();
void init_wp_pool();

/* We use the `readline' library to provide more flexibility to read from stdin. */
static char* rl_gets() {
  static char *line_read = NULL;

  if (line_read) {
    free(line_read);
    line_read = NULL;
  }

  line_read = readline("(nemu) ");

  if (line_read && *line_read) {
    add_history(line_read);
  }

  return line_read;
}

static int cmd_c(char *args) {
  cpu_exec(-1);
  return 0;
}


static int cmd_q(char *args) {
  nemu_state.state = NEMU_QUIT;
  return -1;
}

static int cmd_help(char *args);

static int cmd_si(char *args) {
  int steps = 1;
  if (args != NULL) {
    char *endptr;
    steps = strtol(args, &endptr, 10);
    if (*endptr != '\0' || steps <= 0) {
      printf("Invalid argument '%s': not a number\n", args);
      return 0;
    } 
  }
  cpu_exec(steps);
  return 0;
}

static int cmd_info(char *args) {
  if (args == NULL) {
    printf("Usage: info r - 显示寄存器状态\n");
    printf("       info w - 显示监视点信息\n");
    return 0;
  }
  
  if (strcmp(args, "r") == 0) {
    isa_reg_display();
  } else if (strcmp(args, "w") == 0) {
    list_watchpoints();
  } else {
    printf("未知的info子命令: %s\n", args);
  }
  return 0;
}

// 添加设置监视点的命令
static int cmd_w(char *args) {
  if (args == NULL) {
    printf("用法: w EXPR - 监视表达式EXPR的值\n");
    return 0;
  }
  
  // 调用set_watchpoint函数，但不直接访问WP结构的成员
  bool success = false;
  int wp_no = set_watchpoint_cmd(args, &success);
  
  if (!success) {
    printf("设置监视点失败\n");
  } else {
    printf("监视点 %d: %s\n", wp_no, args);
  }
  return 0;
}

// 添加删除监视点的命令
static int cmd_d(char *args) {
  if (args == NULL) {
    printf("用法: d N - 删除编号为N的监视点\n");
    return 0;
  }
  
  int NO = atoi(args);
  if (delete_watchpoint(NO)) {
    printf("删除监视点 %d 成功\n", NO);
  } else {
    printf("未找到编号为 %d 的监视点\n", NO);
  }
  return 0;
}

static int cmd_x(char *args) {
  char *arg = strtok(NULL, " ");
  char *expr = strtok(NULL, " ");
  if (arg == NULL || expr == NULL) {
    printf("Usage: x N EXPR\n");
    return 0;
  } else {
    int N = atoi(arg);
    if (N < 0)  {
      printf("Invalid argument '%s': not a number\n", arg);
    } else {
      char *str;
      vaddr_t addr = strtol(expr, &str, 16);
      for(int i = 0; i < N; i++)  {
        word_t data = vaddr_read(addr + i * 4,4);
        printf("0x%08x: ", addr + i * 4);
        for(int j = 0; j < 4; j++) {
          printf("0x%02x ", data & 0xff);
          data >>= 8;
        }
        printf("\n");
      }
    }
  }
  return 0;
}

static int cmd_p(char *args) {
  if (args == NULL || *args == '\0') {
    printf("Please provide an expression to evaluate.\n");
    return 0;
  }
  
  bool success = true;
  word_t result = expr(args, &success);
  
  if (success) {
    printf("Expression: %s\n", args);
    printf("Result: %u\n", result);
  } else {
    printf("Failed to evaluate expression: %s\n", args);
  }
  
  return 0;
}

static int cmd_pp(char *args) {
  // 尝试多个可能的路径
  const char *possible_paths[] = {
    "./tools/gen-expr/input",               // 相对于当前目录
  };
  
  FILE *fp = NULL;
  const char *input_path = NULL;
  
  // 尝试每个可能的路径
  for (int i = 0; i < sizeof(possible_paths) / sizeof(possible_paths[0]); i++) {
    fp = fopen(possible_paths[i], "r");
    if (fp != NULL) {
      input_path = possible_paths[i];
      printf("成功打开文件: %s\n", input_path);
      break;
    }
  }
  
  // 如果所有路径都失败，允许用户手动输入路径
  if (fp == NULL) {
    char manual_path[1024];
    printf("无法自动找到input文件,请输入完整路径: ");
    if (fgets(manual_path, sizeof(manual_path), stdin) != NULL) {
      // 移除换行符
      manual_path[strcspn(manual_path, "\n")] = 0;
      fp = fopen(manual_path, "r");
      if (fp != NULL) {
        input_path = manual_path;
        printf("成功打开文件: %s\n", input_path);
      } else {
        printf("无法打开文件: %s\n", manual_path);
        return 1;
      }
    }
  }
  
  char line[1024];
  unsigned expected_result;
  char expression[1024];
  int test_count = 0;
  int passed_count = 0;
  int failed_count = 0;
  
  printf("开始测试表达式计算函数...\n\n");
  
  // 逐行读取文件
  while (fgets(line, sizeof(line), fp) != NULL) {
    // 解析每行内容: "结果 表达式"
    if (sscanf(line, "%u %[^\n]", &expected_result, expression) != 2) {
      continue; // 跳过格式不正确的行
    }
    
    test_count++;
    printf("测试 #%d:\n", test_count);
    printf("表达式: %s\n", expression);
    printf("预期结果: %u\n", expected_result);
    
    // 调用expr函数计算表达式
    bool success = true;
    word_t result = expr(expression, &success);
    
    if (!success) {
      printf("结果: 计算失败\n");
      printf("状态: ❌ 失败 (计算过程出错)\n\n");
      failed_count++;
    } else if (result == expected_result) {
      printf("结果: %u\n", result);
      printf("状态: ✅ 通过\n\n");
      passed_count++;
    } else {
      printf("结果: %u\n", result);
      printf("状态: ❌ 失败 (结果不匹配)\n\n");
      failed_count++;
    }
  }
  
  fclose(fp);
  
  // 打印总结
  printf("测试总结:\n");
  printf("总测试数: %d\n", test_count);
  printf("通过测试: %d (%.1f%%)\n", passed_count, test_count > 0 ? (float)passed_count * 100 / test_count : 0);
  printf("失败测试: %d (%.1f%%)\n", failed_count, test_count > 0 ? (float)failed_count * 100 / test_count : 0);
  
  return 0;
}

static struct {
  const char *name;
  const char *description;
  int (*handler) (char *);
} cmd_table [] = {
  { "help", "Display information about all supported commands", cmd_help },
  { "c", "Continue the execution of the program", cmd_c },
  { "q", "Exit NEMU", cmd_q },
  { "si", "Usage : si N ,Step N instaruction exactly", cmd_si },
  { "info", "Usage info r or info w ,Display the states of functions", cmd_info },
  { "x", "Usage: x N EXPR. Scan the memory from EXPR by N bytes", cmd_x },
  { "p", "Usage: p EXPR. Caculate the value of expression", cmd_p },
  { "pp", "Usage: p EXPR. Caculate the value of expression from ./tool/gen-expr/input", cmd_pp },
  { "w", "Usage: w EXPR. Add a watchpoint on expression", cmd_w },
  { "d", "Usage: d N. Delete the watchpoint with the number N", cmd_d },
  /* TODO: Add more commands */
};

#define NR_CMD ARRLEN(cmd_table)

static int cmd_help(char *args) {
  /* extract the first argument */
  char *arg = strtok(NULL, " ");
  int i;

  if (arg == NULL) {
    /* no argument given */
    for (i = 0; i < NR_CMD; i ++) {
      printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
    }
  }
  else {
    for (i = 0; i < NR_CMD; i ++) {
      if (strcmp(arg, cmd_table[i].name) == 0) {
        printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
        return 0;
      }
    }
    printf("Unknown command '%s'\n", arg);
  }
  return 0;
}

void sdb_set_batch_mode() {
  is_batch_mode = true;
}

void sdb_mainloop() {
  if (is_batch_mode) {
    cmd_c(NULL);
    return;
  }

  for (char *str; (str = rl_gets()) != NULL; ) {
    char *str_end = str + strlen(str);

    /* extract the first token as the command */
    char *cmd = strtok(str, " ");
    if (cmd == NULL) { continue; }

    /* treat the remaining string as the arguments,
     * which may need further parsing
     */
    char *args = cmd + strlen(cmd) + 1;
    if (args >= str_end) {
      args = NULL;
    }

#ifdef CONFIG_DEVICE
    extern void sdl_clear_event_queue();
    sdl_clear_event_queue();
#endif

    int i;
    for (i = 0; i < NR_CMD; i ++) {
      if (strcmp(cmd, cmd_table[i].name) == 0) {
        if (cmd_table[i].handler(args) < 0) { return; }
        break;
      }
    }

    if (i == NR_CMD) { printf("Unknown command '%s'\n", cmd); }
  }
}

void init_sdb() {
  /* Compile the regular expressions. */
  init_regex();

  /* Initialize the watchpoint pool. */
  init_wp_pool();
}
