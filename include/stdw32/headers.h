#ifndef __STDW32_HEADERS_H
#define __STDW32_HEADERS_H

#include <stddef.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif

/* in the event you dislike the way that functions are loaded, simply redefine this
   preprocessor variable to a function with the following prototype:

   void *importFunction(char *library, char *function)

   now all the imports reroute through that function. you can do the same with
   STDW32_IMPORT as well.

   note that to get this to work properly, you have to recompile the entire library
   with the header set. otherwise that will only go to your local instance, and you
   will be unhappy and uncertain why you're still calling that dastardly
   resolveWin32 function. */

#define STDW32_LOADER resolveWin32
#define STDW32_IMPORT(lib, func) \
   static func##_t func = NULL;\
   if (func == NULL) { func = ( (func##_t)STDW32_LOADER(lib, #func) ); }

   /* here are some general helpers to make this slightly less annoying. */

#define MAX_PATH 260
   
   typedef bool (*CloseHandle_t)(void *handle);
   typedef void (*CopyMemory_t)(void *destination, const void *source, size_t size);
   typedef void *(*CreateFileA_t)(const char *filename
                                 ,unsigned int access
                                 ,unsigned int shareMode
                                 ,void *securityAttributes
                                 ,unsigned int disposition
                                 ,unsigned int attributes
                                 ,void *template);
   typedef bool (*FlushFileBuffers_t)(void *handle);
   typedef unsigned int (*GetTempFileNameA_t)(const char *pathName
                                              ,const char *prefix
                                              ,unsigned int unique
                                              ,char *tempFileName);
   typedef unsigned int (*GetTempPathA_t)(unsigned int bufferLength, char *buffer);
   typedef void *(*GlobalAlloc_t)(unsigned int flags, size_t size);
   typedef void *(*GlobalReAlloc_t)(void *ptr, size_t newSize, unsigned int flags);
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
   typedef bool (*ReadFile_t)(void *file
                              ,void *buffer
                              ,unsigned int bytesToRead
                              ,unsigned int *bytesRead
                              ,void *overlapped);
   typedef int (*_vsnprintf_t)(char *buffer, size_t count, const char *format, va_list args);
   typedef int (*_vsnwprintf_t)(wchar_t *buffer
                                ,size_t count
                                ,const wchar_t *format
                                ,va_list args);
   typedef bool (*WriteFile_t)(void *file
                               ,const void *buffer
                               ,unsigned int bytesToWrite
                               ,unsigned int *bytesWritten
                               ,void *overlapped);
   typedef int (*wvsprintfA_t)(char *buffer, const char *format, va_list args);
   typedef int (*wvsprintfW_t)(wchar_t *buffer, const wchar_t *format, va_list args);
   
   /* here, we'll translate some basic headers from their non-win32 counterparts. */
   void *resolveWin32(const char *library, const char *function);

#ifdef __cplusplus
}
#endif

#endif
