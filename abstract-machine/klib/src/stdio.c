#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>
//TODO: stdarg是如何实现的?

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)
int print_num(char *out,size_t out_offset,int val);
int print_str(char *out,size_t out_offset,char* val);
int sprintf(char *out, const char *fmt, ...);
int vsprintf(char *out, const char *fmt, va_list args);

// int printf(const char *fmt, ...) {
//   char out[500];
//   size_t out_offset=0;
//   va_list args;
//   va_start(args,fmt);
//   const char *p = fmt;
//   while(*p!='\0'){
//     switch (*p)
//     {
//     case '\\':
//       break;
//     case '%':
//       if(*(++p)=='d'){
//         out_offset=print_num(out,out_offset,va_arg(args,unsigned));
//       }else if(*(p)=='s'){
//         out_offset=print_str(out,out_offset,va_arg(args,char *));
//       }
//       break;
//     // case '':
//     //   break;
//     default:
//       out[out_offset++]=*p;
//       break;
//     }
//     p++;
//   }
//   out[out_offset]='\0';
//   putstr(out);
//   return out_offset;
//   // return 0;
// }

int printf(const char *fmt, ...){
  char out[40000];
  va_list args;
  va_start(args,fmt);
  int len=vsprintf(out,fmt,args);
  va_end(args);
  putstr(out);
  return len;
}

int vsprintf(char *out, const char *fmt, va_list args) {
  size_t out_offset=0;
  const char *p = fmt;
  while(*p!='\0'){
    switch (*p)
    {
    case '\\':
      break;
    case '%':
      if(*(++p)=='d'){
        out_offset=print_num(out,out_offset,va_arg(args,int));
      }else if(*(p)=='s'){
        out_offset=print_str(out,out_offset,va_arg(args,char *));
      }
      break;
    // case '':
    //   break;
    default:
      out[out_offset++]=*p;
      break;
    }
    p++;
  }
  out[out_offset]='\0';
  return out_offset;
  // panic("Not implemented3");
}
//TOW Helper Func Defined By Myself
//递归打印val
int print_num(char *out,size_t out_offset,int val){
  if(val<0){
  out[out_offset++]='-';
  val=-val;
  }
  int append=val%10;
  if(val/10!=0)
    out_offset=print_num(out,out_offset,val/10);
  out[out_offset]=append+'0';
  return out_offset+1;
}
//打印字符串
int print_str(char *out,size_t out_offset,char* val){
  size_t i=0;
  while(val[i]!='\0'){
    out[out_offset++]=val[i++];
  }
  return out_offset;
}
int sprintf(char *out, const char *fmt, ...) {
  va_list args;
  va_start(args,fmt);
  int len=vsprintf(out,fmt,args);
  va_end(args);
  putstr(out);
  return len;
}
// int sprintf(char *out, const char *fmt, ...) {

//   size_t out_offset=0;
//   va_list args;
//   va_start(args,fmt);
//   const char *p = fmt;
//   while(*p!='\0'){
//     switch (*p)
//     {
//     case '\\':
//       break;
//     case '%':
//       if(*(++p)=='d'){
//         out_offset=print_num(out,out_offset,va_arg(args,int));
//       }else if(*(p)=='s'){
//         out_offset=print_str(out,out_offset,va_arg(args,char *));
//       }
//       break;
//     // case '':
//     //   break;
//     default:
//       out[out_offset++]=*p;
//       break;
//     }
//     p++;
//   }
//   out[out_offset]='\0';
//   return out_offset;
// }


int snprintf(char *out, size_t n, const char *fmt, ...) {
  panic("Not implemented1");
}

int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
  panic("Not implemented2");
}

#endif
