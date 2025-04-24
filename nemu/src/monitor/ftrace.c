#include "ftrace.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <gelf.h>
#include <libelf.h>
#include <errno.h>

// 定义日志函数（根据你的 NEMU 中的日志实现调整）
#ifndef Log
#define Log printf
#endif

// // 外部全局变量，表示 ELF 文件路径
// extern char *elf_file;

// 函数信息结构体
static struct funtion_info {
  char *name;
  long addr;
  long size;
} funtion_info_table[100];

static int funtion_index = 0;
static bool is_ret = false;
static uint32_t stack_num = 0;
static char* last_func_name = NULL;

// 添加函数信息
static void funtion_push(char *name, long addr, long size) {
  funtion_info_table[funtion_index].name = strdup(name); // 复制字符串
  funtion_info_table[funtion_index].addr = addr;
  funtion_info_table[funtion_index].size = size;
  funtion_index++;
}

// 根据地址获取函数索引
static int get_funt_index(long addr) {
  for (int i = 0; i < funtion_index; i++) {
    if (funtion_info_table[i].addr <= addr &&
        addr < funtion_info_table[i].addr + funtion_info_table[i].size) {
      return i;
    }
  }
  return -1;
}

// 根据地址获取函数名
char *get_func_name(long addr) {
  int index = get_funt_index(addr);
  if (index == -1) {
    return NULL;
  }
  return funtion_info_table[index].name;
}

// 设置是否为返回指令
void set_ret_flag(bool flag) {
  is_ret = flag;
}

void func_called_detect(uint32_t pc) {
  char* func_name = get_func_name(pc);
  
  // 只有当目标地址能解析到函数名时才处理
  if(func_name != NULL) {
    if(is_ret) {
      // 对于返回指令，减少缩进并显示返回信息
      if (stack_num > 0) stack_num--;
      printf("0x%08x: %*sret  [%s]\n", pc, stack_num * 2, "", func_name);
      is_ret = false;
    }
    else if(last_func_name != func_name) {  // 避免连续多次调用同一函数时重复输出
      // 这是一个函数调用
      printf("0x%08x: %*scall [%s@0x%08x]\n", pc, stack_num * 2, "", func_name, pc);
      stack_num++;
    }
    
    last_func_name = func_name;
  }
}

// 加载 ELF 文件并提取函数符号信息
static long load_elf() {
  Elf *elf = NULL;
  Elf_Scn *scn = NULL;
  GElf_Shdr shdr;
  GElf_Ehdr ehdr;
  int symcount = 0;
  int fd = -1;
  int func_count = 0;
  
  // 检查 ELF 文件路径
  if (elf_file == NULL) {
    Log("No ELF file specified. Function tracing will be disabled.");
    return 0;
  }
  
  Log("Loading ELF file: %s", elf_file);
  
  // 打开 ELF 文件
  fd = open(elf_file, O_RDONLY, 0);
  if (fd < 0) {
    Log("Cannot open ELF file '%s': %s", elf_file, strerror(errno));
    return 0;
  }
  
  // 初始化 ELF 库
  if (elf_version(EV_CURRENT) == EV_NONE) {
    Log("ELF library initialization failed: %s", elf_errmsg(-1));
    goto cleanup;
  }
  
  // 开始 ELF 处理
  elf = elf_begin(fd, ELF_C_READ, NULL);
  if (elf == NULL) {
    Log("elf_begin() failed: %s", elf_errmsg(-1));
    goto cleanup;
  }
  
  // 读取 ELF 头
  if (gelf_getehdr(elf, &ehdr) == NULL) {
    Log("Failed to get ELF header: %s", elf_errmsg(-1));
    goto cleanup;
  }
  
  // 验证文件是否为 RISC-V ELF
  if (ehdr.e_machine != EM_RISCV) {
    Log("Warning: ELF file is not for RISC-V architecture (machine type: %d)", ehdr.e_machine);
    // 不要退出，因为这可能只是一个警告
  }
  
  // 寻找符号表
  while ((scn = elf_nextscn(elf, scn)) != NULL) {
    if (gelf_getshdr(scn, &shdr) == NULL) {
      Log("Failed to get section header: %s", elf_errmsg(-1));
      continue;
    }
    
    // 查找符号表部分
    if (shdr.sh_type == SHT_SYMTAB) {
      Elf_Data *data = NULL;
      char *section_name = elf_strptr(elf, ehdr.e_shstrndx, shdr.sh_name);
      
      if (section_name) {
        Log("Found symbol table section: %s", section_name);
      }
      
      data = elf_getdata(scn, data);
      if (data == NULL) {
        Log("Failed to get section data: %s", elf_errmsg(-1));
        continue;
      }
      
      symcount = shdr.sh_size / shdr.sh_entsize;
      Log("Symbol table contains %d entries", symcount);
      
      // 遍历符号表
      for (int i = 0; i < symcount; i++) {
        GElf_Sym sym;
        
        if (gelf_getsym(data, i, &sym) == NULL) {
          Log("Failed to get symbol at index %d: %s", i, elf_errmsg(-1));
          continue;
        }
        
        // 只处理函数符号
        if (GELF_ST_TYPE(sym.st_info) == STT_FUNC) {
          char *name = elf_strptr(elf, shdr.sh_link, sym.st_name);
          
          if (name != NULL && sym.st_size > 0) {
            // 记录函数信息并递增函数计数
            funtion_push(name, sym.st_value, sym.st_size);
            func_count++;
            
            if (func_count <= 10) { // 只打印前10个函数，避免日志过多
              Log("Found function: %s at 0x%lx, size: %lu", 
                  name, (unsigned long)sym.st_value, (unsigned long)sym.st_size);
            }
          } else if (name != NULL) {
            // 函数没有大小或者其他问题
            Log("Skipping function: %s (invalid size: %lu)", 
                name, (unsigned long)sym.st_size);
          }
        }
      }
      
      // 如果找到了符号表，就不需要继续搜索其他节区
      break;
    }
  }
  
  if (func_count > 0) {
    Log("Successfully loaded %d functions from ELF file", func_count);
  } else {
    Log("No valid function symbols found in ELF file");
  }
  
cleanup:
  // 清理资源
  if (elf) {
    elf_end(elf);
  }
  if (fd >= 0) {
    close(fd);
  }
  
  return func_count;
}

// 初始化 ftrace
bool init_ftrace(const char *filename) {
  if (filename) {
    elf_file = strdup(filename);
  }
  
  long symcount = load_elf();
  if (symcount > 0) {
    Log("Successfully loaded %ld function symbols from ELF file", symcount);
    return true;
  }
  
  return false;
}

// 清理资源
void cleanup_ftrace() {
  for (int i = 0; i < funtion_index; i++) {
    if (funtion_info_table[i].name) {
      free(funtion_info_table[i].name);
    }
  }
  funtion_index = 0;
  stack_num = 0;
  last_func_name = NULL;
  
  if (elf_file) {
    free(elf_file);
    elf_file = NULL;
  }
}
