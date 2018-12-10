#ifndef __STDW32_BUFFER_H
#define __STDW32_BUFFER_H

#include <stddef.h>

#include <stdw32/config.h>

#ifdef __cplusplus
   STDW32_DECL const void *memchr(const void *ptr, int value, size_t num);
#endif

#ifdef __cplusplus
extern "C"
{
#endif
   
   STDW32_DECL void *memchr(void *ptr, int value, size_t num);
   STDW32_DECL int memcmp(const void *ptr1, const void *ptr2, size_t num);
   STDW32_DECL void *memcpy(void *destination, const void *source, size_t num);
   STDW32_DECL void *memmove(void *destination, const void *source, size_t num);
   STDW32_DECL void *memset(void *ptr, int value, size_t num);
   STDW32_DECL void *memzero(void *ptr, size_t num);

#ifdef __cplusplus
}
#endif

#endif
