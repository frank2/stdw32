#include <stdw32/buffer.h>
#include <stdw32/headers.h>
#include <stdw32/stream.h>
#include <stdw32/string.h>

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

size_t
printfLenA
(const char *format, va_list args)
{
   /* while we're trying to avoid the c-runtime, we're not trying to avoid it entirely--
      we need the C runtime because the classically Windows-named function
      StringC(ch|b)VPrintfEx[AW] relies on msvcrt!_vsnw?printf. What we don't want is the
      compiled-in C runtime nonsense that invades our entrypoint, which is kind of the
      entire point of this library. */
   
   STDW32_IMPORT("msvcrt.dll", _vsnprintf);
   return _vsnprintf(NULL, 0, format, args);
}

size_t
printfLenW
(const wchar_t *format, va_list args)
{
   STDW32_IMPORT("msvcrt.dll", _vsnwprintf);
   return _vsnwprintf(NULL, 0, format, args);
}

/* and now, externals */

int
fclose
(FILE *stream)
{
   STDW32_IMPORT("kernel32.dll", CloseHandle);

   if (!CloseHandle(stream))
      return -1;

   return 0;
}

int
fflush
(FILE *stream)
{
   STDW32_IMPORT("kernel32.dll", FlushFileBuffers);

   if (!FlushFileBuffers(fp))
      return -1;

   return 0;
}

FILE *
fopen
(const char *filename, const char *mode)
{
   STDW32_IMPORT("kernel32.dll", CreateFileA);

   DWORD access, disposition;

   parseMode(mode, &access, &disposition);

   if (access == 0 || disposition == 0)
      return NULL;

   fp = CreateFileA(filename
                    ,access
                    ,0
                    ,NULL
                    ,disposition
                    ,FILE_ATTRIBUTE_NORMAL
                    ,NULL);

   if (fp == ( (void *)-1 ))
      return NULL;

   return ( (FILE *)fp );
}

int
fprintf
(FILE *stream, const char *format, ...)
{
   va_list args;

   va_start(args, format);
   
   return vfprintf(stream, format, args);
}

int
fwprintf
(FILE *stream, const wchar_t *format, ...)
{
   va_list args;

   va_start(args, format);

   return vfwprintf(stream, format, args);
}

size_t
fread
(void *ptr, size_t size, size_t count, FILE *stream)
{
   STDW32_IMPORT("kernel32.dll", ReadFile);
   
   unsigned int bytesRead = 0;
   
   if (size == 0 || count == 0)
      return 0;

   if (!ReadFile(fp, ptr, count, &bytesRead, NULL))
      return 0;

   return ( (size_t)bytesRead );
}

FILE *
freopen
(const char *filename, const char *mode, FILE *stream)
{
   void *stdin, *stdout, *stderr;
   DWORD access, disposition;
   DWORD stdHandle = 0xFFFFFFFF;
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

   if (stdHandle != 0xFFFFFFFF)
      SetStdHandle(stdHandle, (HANDLE)result);

   return result;
}

int
fseek
(FILE *stream, long int offset, int origin)
{
   STDW32_IMPORT("kernel32.dll", SetFilePointer);

   if (stream == NULL)
      return -1;

   if (SetFilePointer(stream, (DWORD)origin, NULL, offset) == 0xFFFFFFFF)
      return -1;

   return 0;
}

int
fgetpos
(FILE *stream, fpos_t *pos)
{
   DWORD result;

   STDW32_IMPORT("kernel32.dll", SetFilePointer);

   if (stream == NULL || pos == NULL)
      return -1;

   result = SetFilePointer(stream, 0, &pos->upper, SEEK_CUR);

   if (result == 0xFFFFFFFF)
      return -1;

   pos->lower = result;

   return 0;
}

int
fsetpos
(FILE *stream, fpos_t *pos)
{
   DWORD result;
   
   STDW32_IMPORT("kernel32.dll", SetFilePointer);
   
   if (stream == NULL || pos == NULL)
      return -1;

   result = SetFilePointer(stream, pos->lower, &pos->upper, SEEK_SET);

   if (result == 0xFFFFFFFF)
      return -1;

   pos->lower = result;

   return 0;
}

long int
ftell
(FILE *stream)
{
   fpos_t result;
   
   STDW32_IMPORT("kernel32.dll", SetFilePointer);

   if (stream == NULL)
      return -1;

   if (fgetpos(stream, &result) == -1)
      return -1;

   return result.combined;
}

size_t
fwrite
(const void *ptr, size_t size, size_t count, FILE *stream)
{
   size_t result;
   size_t index;

   STDW32_IMPORT("kernel32.dll", WriteFile);

   result = 0;

   for (index=0; index<count; ++index)
   {
      unsigned int bytesWritten = 0;
      
      if (!WriteFile(stream
                    ,ptr
                    ,(unsigned int)size
                    ,&bytesWritten
                     ,NULL))
         return result;

      result += bytesWritten;

      if (bytesWritten != (unsigned int)size)
         return result;
   }

   return result;
}

void
rewind
(FILE *stream)
{
   fpos_t pos;

   memzero(&pos, sizeof(fpos_t));
   fsetpos(stream, &pos);
}

int
snprintf
(char *str, size_t len, const char *format, ...)
{
   va_list args;
      
   va_start(args, format);

   return vsnprintf(str, len, format, args);
}

int
sprintf
(char *str, const char *format, ...)
{
   va_list args;

   va_start(args, format);

   return vsprintf(str, format, args);
}

char *
tmpnam
(char *str)
{
   static char internalBuffer[MAX_PATH+1];
   char tempPath[MAX_PATH+1];
   unsigned int tempPathSize, tempFileID;

   STDW32_IMPORT("kernel32.dll", GetTempFileNameA);
   STDW32_IMPORT("kernel32.dll", GetTempPathA);

   if (str == NULL)
   {
      memzero(internalBuffer, MAX_PATH+1);
      str = &internalBuffer[0];
   }

   memzero(tempPath, MAX_PATH+1);
   tempPathSize = GetTempPathA(MAX_PATH+1, &tempPath[0]);

   if (tempPathSize == 0)
      return NULL;

   tempFileID = GetTempFileNameA(tempPath, NULL, 0, str);

   if (tempFileID == 0)
      return NULL;

   return str;
}

int
vfprintf
(FILE *stream, const char *format, va_list args)
{
   char *buffer;
   size_t bufferSize;
   int result;

   bufferSize = printfLenA(format, args)+1;
   buffer = ( (char *)malloc(bufferSize) );
   memzero(buffer, bufferSize);

   result = vsnprintf(buffer, bufferSize, format, args);

   if (result <= 0 || result > bufferSize)
      goto printfError;

   result = fwrite(buffer, result, 1, stream);

printfError:
   free(buffer);
   buffer = NULL;

   return result;
}

int
vfwprintf
(FILE *stream, const wchar_t *format, va_list args)
{
   wchar_t *buffer;
   size_t charSize, bufferSize;
   int result;
   
   charSize = printfLenW(format, args)+1;
   bufferSize = charSize * sizeof(wchar_t);

   buffer = ( (char *)malloc(bufferSize) );
   memzero(buffer, bufferSize);

   result = vsnwprintf(buffer, charSize, format, args);

   if (result <= 0 || result > bufferSize)
      goto printfError;

   result = fwrite(buffer, result*sizeof(wchar_t), 1, stream);

printfError:
   free(buffer);
   buffer = NULL;

   return result;
}

int
vsnprintf
(char *str, size_t len, const char *format, va_list args)
{
   size_t formatSize;
   STDW32_IMPORT("user32.dll", wvsprintfA);

   formatSize = printfLenA(format, args)+1;

   if (formatSize > len)
      return formatSize;

   return vsprintf(str, format, args);
}

int
vsnwprintf
(wchar_t *str, size_t len, const wchar_t *format, va_list args)
{
   size_t formatChars, formatSize;
   STDW32_IMPORT("user32.dll", wvsprintfW);

   formatChars = printfLenA(format, args)+1;
   formatSize = formatChars * sizeof(wchar_t);

   if (formatSize > len)
      return formatSize;

   return vswprintf(str, format, args);
}

int
vsprintf
(char *str, const char *format, va_list args)
{
   STDW32_IMPORT("user32.dll", wvsprintfA);

   return wvsprintfA(str, format, args);
}

int
vswprintf
(char *str, const char *format, va_list args)
{
   STDW32_IMPORT("user32.dll", wvsprintfW);

   return wvsprintfW(str, format, args);
}
   
