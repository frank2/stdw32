#include <stdw32/memory.h>
#include <stdw32/headers.h>

void *
calloc
(size_t num, size_t size)
{
   return malloc(size * num);
}

void
free
(void *ptr)
{
   GlobalFree_t GlobalFree = ( (GlobalFree_t)resolveWin32("kernel32.dll", "GlobalFree") );
   
   GlobalFree(ptr);
}

void *
malloc
(size_t size)
{
   GlobalAlloc_t GlobalAlloc = ( (GlobalAlloc_t)resolveWin32("kernel32.dll", "GlobalAlloc") );
   
   return ( (void *)GlobalAlloc(0 /* GMEM_FIXED */
                                ,size) );
}

void *
realloc
(void *ptr, size_t size)
{
   GlobalReAlloc_t GlobalReAlloc = ( (GlobalReAlloc_t)resolveWin32("kernel32.dll", "GlobalReAlloc") );
   return ( (void *)GlobalReAlloc(ptr, size, 0) );
}
