#include <stdw32/headers.h>
#include <windows.h>

void *
resolve
(const char *library, const char *function)
{
   HMODULE libHandle;

   libHandle = LoadLibraryA(library);

   if (libHandle == NULL)
      return NULL;

   return ( (void *)GetProcAddress(libHandle, function) );
}
