#include <stdw32/stream.h>
#include <stdw32/string.h>
#include <stdw32/headers.h>
#include <windows.h>

/* functions internal to this file */
void
parseMode
(const char *mode, PDWORD access, PDWORD disposition)
{
   size_t modeLen = strlen(mode);
   size_t modeIndex;

   if (access == NULL || disposition == NULL)
      return;

   *access = *disposition = 0;

   for (modeIndex=0; modeIndex<modeLen; ++modeIndex)
   {
      switch(mode[modeIndex])
      {
      case 'r':
         *access = GENERIC_READ;
         *disposition = OPEN_EXISTING;
         break;

      case 'w':
         *access = GENERIC_WRITE;
         *disposition = CREATE_ALWAYS;
         break;

      case 'b': /* CreateFile opens everything in binary mode, lol */
         continue;

      case 'a':
         *access = GENERIC_WRITE;
         *disposition = OPEN_EXISTING;
         break;
            
      case '+':
         *access = GENERIC_READ | GENERIC_WRITE;
         break;
      }
   }
}

/* and now, externals */

int
fclose
(FILE *stream)
{
   CloseHandle_t CloseHandle = ( (CloseHandle_t)resolveWin32("kernel32.dll", "CloseHandle") );
   HANDLE fp = ( (HANDLE)stream );

   if (!CloseHandle(fp))
      return -1;

   return 0;
}

int
fflush
(FILE *stream)
{
   FlushFileBuffers_t FlushFileBuffers = ( (FlushFileBuffers_t)resolveWin32
   HANDLE fp = ( (HANDLE)stream );

   if (!FlushFileBuffers(fp))
      return -1;

   return 0;
}

FILE *
fopen
(const char *filename, const char *mode)
{
   HANDLE fp = NULL;
   DWORD access, disposition;

   parseMode(mode, &access, &disposition);

   if (access == 0 || disposition == 0)
      return NULL;

   fp = CreateFileA(filename
                    ,access
                    ,0
                    ,NULL
                    ,disposition
                    ,FILE_ATTRIBUTE_NORMAL);

   if (fp == INVALID_HANDLE_VALUE)
      return NULL;

   return ( (FILE *)fp );
}

size_t
fread
(void *ptr, size_t size, size_t count, FILE *stream)
{
   HANDLE fp = ( (HANDLE)stream );
   DWORD bytesRead = 0;
   
   if (size == 0 || count == 0)
      return 0;

   if (!ReadFile(fp, ptr, (DWORD)count, &bytesRead, NULL))
      return 0;

   return ( (size_t)bytesRead );
}

FILE *
freopen
(const char *filename, const char *mode, FILE *stream)
{
   HANDLE stdin, stdout, stderr;
   DWORD access, disposition;
   DWORD stdHandle = 0;
   FILE *result = NULL;

   if (stream == NULL || mode == NULL)
      return result;

   parseMode(mode, &access, &disposition);

   stdin = GetStdHandle(STD_INPUT_HANDLE);
   stdout = GetStdHandle(STD_OUTPUT_HANDLE);
   stderr = GetStdHandle(STD_ERROR_HANDLE);

   switch(stream)
   {
   case stdin:
      stdHandle = STD_INPUT_HANDLE;
      break;

   case stdout:
      stdHandle = STD_OUTPUT_HANDLE;
      break;

   case stderr:
      stdHandle = STD_ERROR_HANDLE;
      break;
   }

   if (filename != NULL)
   {
      fclose(stream);
      result = fopen(filename, mode);
   }
   else
   {
      HANDLE fp = ReOpenFile(stream, access, 0, 0);

      if (fp == INVALID_HANDLE_VALUE)
         return NULL;
      
      result = ( (FILE *)fp );
   }

   if (stdHandle != 0)
      SetStdHandle(stdHandle, (HANDLE)result);

   return result;
}
      
      
   
