#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

int printf(const char *fmt, ...) {
  panic("Not implemented");
}

int vsprintf(char *out, const char *fmt, va_list ap) {
  panic("Not implemented");
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

int snprintf(char *out, size_t n, const char *fmt, ...) {
  panic("Not implemented");
}

int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
  panic("Not implemented");
}

#endif
