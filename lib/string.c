#include <stdw32/string.h>
#include <stdw32/headers.h>

#ifdef __cplusplus
const char *
strchr
(const char *str, int character)
{
   size_t index, size;

   if (str == NULL)
      return NULL;

   size = strlen(str);

   for (index=0; index<size; ++index)
      if (str[index] == (char)character)
         return &str[index];

   return NULL;
}

const wchar_t *
wcschr
(const wchar_t *str, wchar_t character)
{
   size_t index, size;

   if (str == NULL)
      return NULL;

   size = wcslen(str);

   for (index=0; index<size; ++index)
      if (str[index] == (wchar_t)character)
         return &str[index];

   return NULL;
}
#endif

char *
strcat
(char *destination, const char *src)
{
   STDW32_IMPORT("kernel32.dll", lstrcatA);
   
   if (destination == NULL || src == NULL)
      return NULL;

   return lstrcatA(destination, src);
}

wchar_t *
wcscat
(wchar_t *destination, const wchar_t *src)
{
   STDW32_IMPORT("kernel32.dll", lstrcatW);
   
   if (destination == NULL || src == NULL)
      return NULL;

   return lstrcatW(destination, src);
}

char *
strchr
(char *str, int character)
{
   size_t index, size;

   if (str == NULL)
      return NULL;

   size = strlen(str);

   for (index=0; index<size; ++index)
      if (str[index] == (char)character)
         return &str[index];

   return NULL;
}

wchar_t *
wcschr
(wchar_t *str, wchar_t character)
{
   size_t index, size;

   if (str == NULL)
      return NULL;

   size = wcslen(str);

   for (index=0; index<size; ++index)
      if (str[index] == (wchar_t)character)
         return &str[index];

   return NULL;
}

int
strcmp
(const char *str1, const char *str2)
{
   STDW32_IMPORT("kernel32.dll", lstrcmpA);
   
   return lstrcmpA(str1, str2);
}

int
wcscmp
(const wchar_t *str1, const wchar_t *str2)
{
   STDW32_IMPORT("kernel32.dll", lstrcmpW);
   
   return lstrcmpW(str1, str2);
}

int
strcpy
(char *destination, const char *src)
{
   STDW32_IMPORT("kernel32.dll", lstrcpyA);
   
   return lstrcpyA(destination, src);
}

int
wcscpy
(wchar_t *destination, const wchar_t *src)
{
   STDW32_IMPORT("kernel32.dll", lstrcpyW);
   
   return lstrcpyW(destination, src);
}

size_t
strcspn
(const char *search, const char *set)
{
   const char *index;
   
   if (search == NULL || set == NULL)
      return strlen(search);

   index = search;

   while (*index != 0)
   {
      const char *scan = set;

      while (*scan != 0)
         if (*index == *scan)
            goto characterFound;
   }

characterFound:
   return ( (size_t)(index - search) );
}

size_t
wcscspn
(const wchar_t *search, const wchar_t *set)
{
   const wchar_t *index;
   
   if (search == NULL || set == NULL)
      return wcslen(search);

   index = search;

   while (*index != 0)
   {
      const wchar_t *scan = set;

      while (*scan != 0)
         if (*index == *scan)
            goto characterFound;
   }

characterFound:
   return ( (size_t)(index - search) );
}

size_t
strlen
(const char *str)
{
   STDW32_IMPORT("kernel32.dll", lstrlenA);
   
   return lstrlenA(str);
}

size_t
wcslen
(const wchar_t *str)
{
   STDW32_IMPORT("kernel32.dll", lstrlenW);
   
   return lstrlenW(str);
}
