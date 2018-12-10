#ifndef __STDW32_VARARGS_H
#define __STDW32_VARARGS_H

#ifdef __cplusplus
extern "C"
{
#endif

   typedef char *va_list;

#define intsizeof(n)    ((sizeof(n) + sizeof(int) - 1) &~(sizeof(int) - 1))
#define va_start(ap, v) (ap = (va_list)&(v) + intsizeof(v))
#define va_arg(ap, t)   (*(t *) ((ap += intsizeof(t)) - intsizeof(t)))
#define va_end(ap)      (ap = (va_list)0)

#ifdef __cplusplus
}
#endif

#endif
