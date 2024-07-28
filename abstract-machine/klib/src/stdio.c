#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>
// TODO: stdarg是如何实现的?

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)
// #if defined(__NATIVE_USE_KLIB__)
int print_num(char *out, size_t out_offset, int val);
int print_str(char *out, size_t out_offset, char *val);
int sprintf(char *out, const char *fmt, ...);
int vsprintf(char *out, const char *fmt, va_list args);
int print_num_hex(char *out, size_t out_offset, int val);
int print_num_long(char *out, size_t out_offset, long val);

int printf(const char *fmt, ...)
{

  char out[10];
  va_list args;
  va_start(args, fmt);
  int len = vsprintf(out, fmt, args);
  va_end(args);
  putstr(out);
  return len;
}

int vsprintf(char *out, const char *fmt, va_list args)
{
  size_t out_offset = 0;
  const char *p = fmt;
  while (*p != '\0')
  {
    switch (*p)
    {
    case '\\':
      break;
    case '%':
      p++;
      switch (*(p))
      {
        case 'd':
          out_offset = print_num(out, out_offset, va_arg(args, int));
          break;
        case 's':
          out_offset = print_str(out, out_offset, va_arg(args, char *));
          break;
        case 'c':
          out[out_offset++] = va_arg(args, int);
          break;
        case 'x':
          out_offset = print_num_hex(out, out_offset, va_arg(args, int));
          break;
        case 'l':
          p++;
          if(*(p)=='d'){//%ld
            out_offset=print_num_long(out, out_offset, va_arg(args, long));
          }
      }
      break;
    // case '':
    //   break;
    default:
      out[out_offset++] = *p;
      break;
    }
    p++;
  }
  out[out_offset] = '\0';
  return out_offset;
}
// TOW Helper Func Defined By Myself
// 递归打印val
int print_num(char *out, size_t out_offset, int val)
{
  if (val < 0)
  {
    out[out_offset++] = '-';
    val = -val;
  }
  int append = val % 10;
  if (val / 10 != 0)
    out_offset = print_num(out, out_offset, val / 10);
  out[out_offset] = append + '0';
  return out_offset + 1;
}
int print_num_hex(char *out, size_t out_offset, int val)
{
  if (val < 0)
  {
    out[out_offset++] = '-';
    val = -val;
  }
  int append = val % 16;
  if (val / 16 != 0)
    out_offset = print_num(out, out_offset, val / 16);
  out[out_offset] = append <= 9 ? append + '0' : append - 10 + 'a';
  return out_offset + 1;
}
int print_num_long(char *out, size_t out_offset, long val)
{
  if (val < 0)
  {
    out[out_offset++] = '-';
    val = -val;
  }
  long append = val % 10;
  if (val / 10 != 0)
    out_offset = print_num(out, out_offset, val / 10);
  out[out_offset] = append + '0';
  return out_offset + 1;
}
// 打印字符串
int print_str(char *out, size_t out_offset, char *val)
{
  size_t i = 0;
  while (val[i] != '\0')
  {
    out[out_offset++] = val[i++];
  }
  return out_offset;
}
int sprintf(char *out, const char *fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  int len = vsprintf(out, fmt, args);
  va_end(args);
  // putstr(out);
  return len;
}

int snprintf(char *out, size_t n, const char *fmt, ...)
{
  panic("Not implemented1");
}

int vsnprintf(char *out, size_t n, const char *fmt, va_list ap)
{
  panic("Not implemented2");
}

#endif
