#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

int printf(const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);

  int count = 0;

  while (*fmt != '\0') {
    if (*fmt == '%') {
      fmt++;
      switch (*fmt) {
        case 'd': {
          int d = va_arg(args, int);
          char buffer[32];
          itoa(d, buffer, 10);
          for (int i = 0; buffer[i]; i++) {
            putch(buffer[i]);
            count++;
          }
          break;
        }
        case 's': {
          char *s = va_arg(args, char *);
          while (*s != '\0') {
            putch(*s++);
            count++;
          }
          break;
        }
        case 'c': {
          char c = (char)va_arg(args, int);
          putch(c);
          count++;
          break;
        }
        case 'x': {
          int x = va_arg(args, int);
          char buffer[32];
          itoa(x, buffer, 16);
          for (int i = 0; buffer[i]; i++) {
            putch(buffer[i]);
            count++;
          }
          break;
        }
        case '%': {
          putch('%');
          count++;
          break;
        }
        default:
          putch(*fmt);
          count++;
          break;
      }
    } else {
      putch(*fmt);
      count++;
    }
    fmt++;
  }

  va_end(args);
  return count;
}

int vsprintf(char *out, const char *fmt, va_list ap) {
  panic("Not implemented");
}

int sprintf(char *out, const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);

  char *dest = out;

  while (*fmt != '\0') {
    if (*fmt == '%') {
      fmt++;
      switch (*fmt) {
        case 'd': {
          int d = va_arg(args, int);
          char num_buf[32];
          itoa(d, num_buf, 10);
          int i = 0;
          while (num_buf[i]) {
            *dest++ = num_buf[i++];
          }
          break;
        }
        case 's': {
          char *s = va_arg(args, char *);
          while (*s != '\0') {
            *dest++ = *s++;
          }
          break;
        }
        case 'c': {
          char c = (char)va_arg(args, int);
          *dest++ = c;
          break;
        }
        case 'x': {
          int x = va_arg(args, int);
          char num_buf[32];
          itoa(x, num_buf, 16);
          int i = 0;
          while (num_buf[i]) {
            *dest++ = num_buf[i++];
          }
          break;
        }
        case '%': {
          *dest++ = '%';
          break;
        }
        default:
          *dest++ = *fmt;
          break;
      }
    } else {
      *dest++ = *fmt;
    }
    fmt++;
  }

  *dest = '\0';
  va_end(args);

  return dest - out;
}

int snprintf(char *out, size_t n, const char *fmt, ...) {
  panic("Not implemented");
}

int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
  panic("Not implemented");
}

#endif
