#ifndef __STDW32_STREAM_H
#define __STDW32_STREAM_H

#include <stdarg.h>
#include <stddef.h>

#include <stdw32/config.h>

#ifdef __cplusplus
extern "C"
{
#endif

   /* 
      this makes (FILE *) and (HANDLE) equivalent casts, because HANDLE is:

      typedef PVOID HANDLE;

      so, (FILE *) == (void *) == (PVOID) == (HANDLE)

      FILE shouldn't be defined since we're trying to replace the stdlib after all.
   */
   typedef void FILE;

   /* apparently fpos_t is implementation-dependent, so let's just make our own. */
   typedef union __fpos_t
   {
      struct
      {
         unsigned long lower;
         unsigned long upper;
      } split;

      unsigned long long combined;
   } fpos_t;

   STDW32_DECL int fclose(FILE *stream);
   STDW32_DECL int fflush(FILE *stream);
   STDW32_DECL FILE *fopen(const char *filename, const char *mode);
   STDW32_DECL int fprintf(FILE *stream, const char *format, ...);
   STDW32_DECL size_t fread(void *ptr, size_t size, size_t count, FILE *stream);
   STDW32_DECL FILE *freopen(const char *filename, const char *mode, FILE *stream);
   STDW32_DECL int fseek(FILE *stream, long int offset, int origin);
   STDW32_DECL int fsetpos(FILE *stream, fpos_t *pos);
   STDW32_DECL long int ftell(FILE *stream);
   STDW32_DECL size_t fwrite(const void *ptr, size_t size, size_t count, FILE *stream);
   STDW32_DECL void rewind(FILE *stream);
   STDW32_DECL int snprintf(char *str, size_t len, const char *format, ...);
   STDW32_DECL int sprintf(char *str, const char *format, ...);
   STDW32_DECL char *tmpnam(char *str);
   STDW32_DECL int vfprintf(FILE *stream, const char *format, va_list args);
   STDW32_DECL int vsnprintf(char *str, size_t len, const char *format, va_list args);
   STDW32_DECL int vsprintf(char *str, const char *format, va_list args);
   STDW32_DECL int wsnprintf(wchar_t *str, size_t len, const wchar_t *format, va_list args);
   STDW32_DECL int wsprintf(wchar_t *str, const wchar_t *format, ...);
   /* wvsprintf is technically already defined in windows.h, so skip it */
   
#ifdef __cplusplus
}
#endif

#endif
