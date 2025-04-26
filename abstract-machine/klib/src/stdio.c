#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

int printf(const char *fmt, ...) {
  static char buf[4096]; // 静态缓冲区，避免栈溢出
  va_list ap;
  int ret;
  
  va_start(ap, fmt);
  ret = vsprintf(buf, fmt, ap);
  va_end(ap);
  
  for (int i = 0; i < ret; i++) {
    putch(buf[i]); 
  }
  
  return ret;
}

int vsprintf(char *out, const char *fmt, va_list ap) {
  char *str = out;
  char *s;
  int d;
  char c;
  unsigned int u;
  char buf[32]; // 用于数字转换的临时缓冲区
  
  for (; *fmt != '\0'; fmt++) {
    if (*fmt != '%') {
      *str++ = *fmt;
      continue;
    }
    
    // 跳过%
    fmt++;
    
    // 处理格式说明符
    switch (*fmt) {
      case 'd': // 十进制有符号整数
        d = va_arg(ap, int);
        if (d < 0) {
          *str++ = '-';
          d = -d;
        }
        // 将整数转为字符串
        {
          int i = 0;
          int temp = d;
          // 处理0的特殊情况
          if (d == 0) {
            buf[i++] = '0';
          } else {
            // 计算数字位数
            while (temp > 0) {
              temp /= 10;
              i++;
            }
            // 从最高位开始填充
            int j = i;
            while (j > 0) {
              j--;
              buf[j] = '0' + (d % 10);
              d /= 10;
            }
          }
          // 复制到输出缓冲区
          int j;
          for (j = 0; j < i; j++) {
            *str++ = buf[j];
          }
        }
        break;
      
      case 'x': // 十六进制无符号整数
        u = va_arg(ap, unsigned int);
        // 处理0的特殊情况
        if (u == 0) {
          *str++ = '0';
        } else {
          int i = 0;
          while (u > 0) {
            int digit = u % 16;
            buf[i++] = (digit < 10) ? ('0' + digit) : ('a' + digit - 10);
            u /= 16;
          }
          // 反向复制到输出缓冲区
          while (i > 0) {
            *str++ = buf[--i];
          }
        }
        break;
      
      case 'p': // 指针（十六进制地址）
        *str++ = '0';
        *str++ = 'x';
        u = (unsigned int)(uintptr_t)va_arg(ap, void *);
        // 生成8位十六进制数
        for (int i = 7; i >= 0; i--) {
          int digit = (u >> (i * 4)) & 0xf;
          *str++ = (digit < 10) ? ('0' + digit) : ('a' + digit - 10);
        }
        break;
      
      case 's': // 字符串
        s = va_arg(ap, char *);
        if (!s) s = "(null)";
        while (*s) {
          *str++ = *s++;
        }
        break;
      
      case 'c': // 字符
        c = (char)va_arg(ap, int);
        *str++ = c;
        break;
      
      case '%': // 百分号自身
        *str++ = '%';
        break;
      
      default: // 不支持的格式，原样输出
        *str++ = '%';
        *str++ = *fmt;
    }
  }
  
  // 添加字符串结束符
  *str = '\0';
  
  // 返回写入的字符数（不包括结束符）
  return str - out;
}

// 将整数转换为字符串存储到缓冲区
static void itoa(char **out, int num) {
    char temp[16];
    int i = 0;
    int sign = 0;
    
    // 处理负数
    if (num < 0) {
        sign = 1;
        num = -num; // 如果有abs函数可以使用abs(num)
    }
    
    // 处理0
    if (num == 0) {
        temp[i++] = '0';
    } else {
        // 构建数字字符串（反向）
        while (num > 0) {
            temp[i++] = '0' + (num % 10);
            num /= 10;
        }
    }
    
    // 添加负号
    if (sign) {
        temp[i++] = '-';
    }
    
    // 反向复制到输出缓冲区
    while (i > 0) {
        *((*out)++) = temp[--i];
    }
}

// 实现精简版sprintf函数，只支持%s和%d
int sprintf(char *out, const char *fmt, ...) {
    char *str = out;
    char *s;
    va_list ap;
    
    va_start(ap, fmt);
    
    for (; *fmt; fmt++) {
        if (*fmt != '%') {
            *str++ = *fmt;
            continue;
        }
        
        // 跳过%
        fmt++;
        
        // 处理格式说明符
        switch (*fmt) {
            case 'd': // 十进制整数
                itoa(&str, va_arg(ap, int));
                break;
                
            case 's': // 字符串
                s = va_arg(ap, char *);
                if (!s) s = "(null)"; // 处理空指针
                
                // 复制字符串到输出缓冲区
                while (*s) {
                    *str++ = *s++;
                }
                break;
                
            default: // 不支持的格式，原样输出
                *str++ = '%';
                *str++ = *fmt;
        }
    }
    
    // 添加字符串结束符
    *str = '\0';
    
    va_end(ap);
    
    // 返回写入的字符数（不包括结束符）
    return str - out;
}

// 实现vsnprintf函数 - 带大小限制的格式化输出到字符串
int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
    char *str = out;
    char *s;
    int d;
    char c;
    unsigned int u;
    char buf[32]; // 用于数字转换的临时缓冲区
    size_t count = 0; // 跟踪实际需要的字符数
    
    // 处理特殊情况
    if (n == 0) return 0;
    if (n == 1) {
        *out = '\0';
        return 0;
    }
    
    // 确保至少有一个位置给结束符
    size_t max_chars = n - 1;
    
    for (; *fmt != '\0'; fmt++) {
        if (*fmt != '%') {
            if (count < max_chars) {
                *str++ = *fmt;
            }
            count++;
            continue;
        }
        
        // 跳过%
        fmt++;
        
        // 处理格式说明符
        switch (*fmt) {
            case 'd': // 十进制有符号整数
                d = va_arg(ap, int);
                
                // 处理符号
                if (d < 0) {
                    if (count < max_chars) {
                        *str++ = '-';
                    }
                    count++;
                    d = -d;
                }
                
                // 将整数转为字符串
                {
                    int i = 0;
                    int temp = d;
                    
                    // 处理0的特殊情况
                    if (d == 0) {
                        buf[i++] = '0';
                    } else {
                        // 计算数字位数
                        while (temp > 0) {
                            temp /= 10;
                            i++;
                        }
                        
                        // 从最高位开始填充
                        int j = i;
                        while (j > 0) {
                            j--;
                            buf[j] = '0' + (d % 10);
                            d /= 10;
                        }
                    }
                    
                    // 复制到输出缓冲区，同时检查限制
                    for (int j = 0; j < i; j++) {
                        if (count < max_chars) {
                            *str++ = buf[j];
                        }
                        count++;
                    }
                }
                break;
            
            case 'x': // 十六进制无符号整数
                u = va_arg(ap, unsigned int);
                
                // 处理0的特殊情况
                if (u == 0) {
                    if (count < max_chars) {
                        *str++ = '0';
                    }
                    count++;
                } else {
                    int i = 0;
                    while (u > 0) {
                        int digit = u % 16;
                        buf[i++] = (digit < 10) ? ('0' + digit) : ('a' + digit - 10);
                        u /= 16;
                    }
                    
                    // 反向复制到输出缓冲区
                    while (i > 0) {
                        i--;
                        if (count < max_chars) {
                            *str++ = buf[i];
                        }
                        count++;
                    }
                }
                break;
            
            case 'p': // 指针（十六进制地址）
                if (count < max_chars) {
                    *str++ = '0';
                }
                count++;
                
                if (count < max_chars) {
                    *str++ = 'x';
                }
                count++;
                
                u = (unsigned int)(uintptr_t)va_arg(ap, void *);
                
                // 生成8位十六进制数
                for (int i = 7; i >= 0; i--) {
                    int digit = (u >> (i * 4)) & 0xf;
                    if (count < max_chars) {
                        *str++ = (digit < 10) ? ('0' + digit) : ('a' + digit - 10);
                    }
                    count++;
                }
                break;
            
            case 's': // 字符串
                s = va_arg(ap, char *);
                if (!s) s = "(null)";
                
                while (*s) {
                    if (count < max_chars) {
                        *str++ = *s;
                    }
                    count++;
                    s++;
                }
                break;
            
            case 'c': // 字符
                c = (char)va_arg(ap, int);
                if (count < max_chars) {
                    *str++ = c;
                }
                count++;
                break;
            
            case '%': // 百分号自身
                if (count < max_chars) {
                    *str++ = '%';
                }
                count++;
                break;
            
            default: // 不支持的格式，原样输出
                if (count < max_chars) {
                    *str++ = '%';
                }
                count++;
                
                if (count < max_chars) {
                    *str++ = *fmt;
                }
                count++;
        }
    }
    
    // 添加字符串结束符
    *str = '\0';
    
    // 返回实际需要的字符数（不包括结束符）
    return count;
}

// 实现snprintf函数 - 带大小限制的格式化输出
int snprintf(char *out, size_t n, const char *fmt, ...) {
    va_list ap;
    int ret;
    
    va_start(ap, fmt);
    ret = vsnprintf(out, n, fmt, ap);
    va_end(ap);
    
    return ret;
}

#endif
