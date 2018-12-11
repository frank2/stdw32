#ifndef __STDW32_HEADERS_H
#define __STDW32_HEADERS_H

#include <stddef.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define STDW32_IMPORT(lib, func) func##_t func = ( (func##_t)resolveWin32(lib, #func) )
   
   typedef bool (*CloseHandle_t)(void *handle);
   typedef void (*CopyMemory_t)(void *destination, const void *source, size_t size);
   typedef void *(*GlobalAlloc_t)(unsigned int flags, size_t size);
   typedef void *(*GlobalFree_t)(void *ptr);
   typedef void (*MoveMemory_t)(void *destination, const void *source, size_t size);
   typedef char *(*lstrcatA_t)(char *destination, const char *src);
   typedef wchar_t *(*lstrcatW_t)(wchar_t *destination, const wchar_t *src);
   typedef int (*lstrcmpA_t)(const char *str1, const char *str2);
   typedef int (*lstrcmpW_t)(const wchar_t *str1, const wchar_t *str2);
   typedef int (*lstrcpyA_t)(char *destination, const char *src);
   typedef int (*lstrcpyW_t)(wchar_t *destination, const char *src);
   typedef int (*lstrlenA_t)(const char *str);
   typedef int (*lstrlenW_t)(const wchar_t *str);
   
   /* here, we'll translate some basic headers from their non-win32 counterparts. */
   void *resolveWin32(const char *library, const char *function);

#ifdef __cplusplus
}
#endif
