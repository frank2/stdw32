#include <stdw32/buffer.h>

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
      int result = *(rCast+index) - *(lCast+index);

      if (result != 0)
         return result;
   }

   return 0;
}

void *
memcpy
(void *destination, const void *source, size_t num)
{
   CopyMemory_t CopyMemory = ( (CopyMemory_t)resolveWin32("kernel32.dll", "CopyMemory") );
   
   CopyMemory(destination, source, num);

   return destination;
}

void *
memmove
(void *destination, const void *source, size_t num)
{
   MoveMemory_t MoveMemory = ( (MoveMemory_t)resolveWin32("kernel32.dll", "MoveMemory") );
   
   MoveMemory(destination, source, num);

   return destination;
}

void *
memset
(void *ptr, int value, size_t num)
{
   unsigned char cVal;
   unsigned char *cPtr;
   size_t index, ptrSize;

   if (ptr == NULL || num == 0)
      return ptr;

   cVal = ( (unsigned char)value );
   cPtr = ( (unsigned char *)ptr );
   ptrSize = sizeof(void *);
   index = 0;

   if (num > ptrSize)
   {
      char blockSet[sizeof(void *)];
      size_t *blockPtr = ( (size_t *)&blockSet[0] );

      for (index; index<ptrSize; ++index)
         blockSet[index] = cVal;

      for (index=0; index+ptrSize<num; index+=ptrSize)
         *( (size_t *)&cPtr[index] ) = *blockPtr;
   }

   for (index; index<num; ++index)
      *(cPtr+index) = cVal;
   
   return ptr;
}

void *
memzero
(void *ptr, size_t num)
{
   return memset(ptr, 0, num);
}
