#ifndef __STDW32_STRING_H
#define __STDW32_STRING_H

#include <stddef.h>

#include <stdw32/config.h>

#ifdef __cplusplus
   STDW32_DECL const char *strchr(const char *str, int character);
   STDW32_DECL const wchar_t *wcschr(const wchar_t *str, wchar_t character);
#endif

#ifdef __cplusplus
extern "C"
{
#endif

   STDW32_DECL char *strcat(char *destination, const char *src);
   STDW32_DECL wchar_t *wcscat(wchar_t *destination, const wchar_t *src);

   STDW32_DECL char *strchr(char *str, int character);
   STDW32_DECL wchar_t *wcschr(wchar_t *str, wchar_t character);

   STDW32_DECL int strcmp(const char *str1, const char *str2);
   STDW32_DECL int wcscmp(const wchar_t *str1, const wchar_t *str2);

   STDW32_DECL char *strcpy(char *destination, const char *source);
   STDW32_DECL wchar_t *wcscpy(wchar_t *destination, const char *source);

   STDW32_DECL size_t strcspn(const char *search, const char *set);
   STDW32_DECL size_t wcscspn(const wchar_t *search, const wchar_t *set);

   STDW32_DECL size_t strlen(const char *str);
   STDW32_DECL size_t wcslen(const wchar_t *str);
   
#ifdef __cplusplus
}
#endif

#endif
