#include <stdw32/memory.h>
#include <windows.h>

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
   GlobalFree(ptr);
}

void *
malloc
(size_t size)
{
   return ( (void *)GlobalAlloc(GMEM_FIXED, size) );
}

void *
realloc
(void *ptr, size_t size)
{
   return ( (void *)GlobalReAlloc(ptr, size, 0) );
}
