#ifndef __FTRACE_H__
#define __FTRACE_H__

#include <stdint.h>
#include <stdbool.h>

extern char *elf_file ;
// 初始化函数跟踪
bool init_ftrace(const char *elf_filename);

// 获取函数名
char *get_func_name(long addr);

// 函数调用检测
void func_called_detect(uint32_t pc);

// 设置当前指令是否为返回指令
void set_ret_flag(bool is_ret);

// 清理函数
void cleanup_ftrace();

#endif