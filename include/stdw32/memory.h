#ifndef __STDW32_MEMORY_H
#define __STDW32_MEMORY_H

#include <stddef.h>

#include <stdw32/config.h>

#ifdef __cplusplus
extern "C"
{
#endif

   STDW32_DECL void *calloc(size_t num, size_t size);
   STDW32_DECL void free(void *ptr);
   STDW32_DECL void *malloc(size_t size);
   STDW32_DECL void *realloc(void *ptr, size_t size);
   
#ifdef __cplusplus
}
#endif

#endif
