#include <stdw32/buffer.h>
#include <windows.h>

#ifdef __cplusplus
const void *
memchr
(const void *ptr, int value, size_t num)
{
   const unsigned char *cast = ( (const unsigned char *)ptr );
   unsigned char search = ( (unsigned char)value );
   size_t index;

   for (index=0; index<num; ++index)
      if (*(cast+index) == search)
         return (cast+index);

   return NULL;
}
#endif

void *
memchr
(void *ptr, int value, size_t num)
{
   unsigned char *cast = ( (unsigned char *)ptr );
   unsigned char search = ( (unsigned char)value );
   size_t index;

   for (index=0; index<num; ++index)
      if (*(cast+index) == search)
         return (cast+index);

   return NULL;
}

int
memcmp
(const void *ptr1, const void *ptr2, size_t num)
{
   const unsigned char *lCast = ( (const unsigned char *)ptr1 );
   const unsigned char *rCast = ( (const unsigned char *)ptr2 );
   size_t index;

   for (index=0; index<num; ++index)
   {
      char result = *(rCast+index) - *(lCast+index);

      if (result != 0)
         return result;
   }

   return 0;
}

void *
memcpy
(void *destination, const void *source, size_t num)
{
   CopyMemory(destination, source, num);

   return destination;
}

void *
memmove
(void *destination, const void *source, size_t num)
{
   MoveMemory(destination, source, num);

   return destination;
}

void *
memset
(void *ptr, int value, size_t num)
{
   FillMemory(ptr, value, num);

   return ptr;
}

void *
memzero
(void *ptr, size_t num)
{
   ZeroMemory(ptr, num);

   return ptr;
}
