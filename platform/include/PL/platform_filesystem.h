/*
This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <http://unlicense.org>
*/

#pragma once

#include "platform.h"

#define plBytesToKilobytes(a)   ((double)((a)) / 1000)
#define plBytesToMegabytes(a)   (plBytesToKilobytes(a) / 1000)
#define plBytesToGigabytes(a)   (plBytesToMegabytes(a) / 1000)

#define plBytesToKibibytes(a)   ((double)((a)) / 1024)
#define plBytesToMebibytes(a)   (plBytesToKibibytes(a) / 1024)
#define plBytesToGibibytes(a)   (plBytesToMebibytes(a) / 1024)

typedef struct PLFile PLFile;

PL_EXTERN_C

PL_EXTERN char *plGetUserName(char *out, size_t n);

PL_EXTERN const char* plGetWorkingDirectory( void );
PL_EXTERN void plSetWorkingDirectory( const char* path );

PL_EXTERN char* plGetApplicationDataDirectory( const char* app_name, char* out, size_t n );

PL_EXTERN void plStripExtension( char* dest, size_t length, const char* in );

PL_EXTERN const char* plGetFileExtension( const char* in );
PL_EXTERN const char* plGetFileName( const char* path );

PL_EXTERN bool plLocalFileExists( const char* path );
PL_EXTERN bool plFileExists( const char* path );
PL_EXTERN bool plLocalPathExists( const char* path );
PL_EXTERN bool plPathExists( const char* path );

PL_EXTERN void plScanDirectory( const char* path,
								const char* extension,
								void (* Function)( const char* ),
								bool recursive );

PL_EXTERN bool plCreateDirectory( const char* path );
PL_EXTERN bool plCreatePath( const char* path );

// File I/O ...

PL_EXTERN PLFile* plOpenLocalFile( const char* path, bool cache );
PL_EXTERN PLFile* plOpenFile( const char* path, bool cache );
PL_EXTERN void plCloseFile( PLFile* ptr );

PL_EXTERN bool plCopyFile( const char* path, const char* dest );
PL_EXTERN bool plWriteFile( const char* path, const uint8_t* buf, size_t length );
PL_EXTERN bool plDeleteFile( const char* path );

PL_EXTERN bool plIsFileModified( time_t oldtime, const char* path );
PL_EXTERN bool plIsEndOfFile( const PLFile* ptr );

PL_EXTERN time_t plGetLocalFileTimeStamp( const char *path );
PL_EXTERN size_t plGetLocalFileSize( const char *path );

PL_EXTERN const char* plGetFilePath( const PLFile* ptr );
PL_EXTERN const uint8_t* plGetFileData( const PLFile* ptr );
PL_EXTERN time_t plGetFileTimeStamp( PLFile *ptr );
PL_EXTERN size_t plGetFileSize( const PLFile* ptr );
PL_EXTERN size_t plGetFileOffset( const PLFile* ptr );

PL_EXTERN size_t plReadFile( PLFile* ptr, void* dest, size_t size, size_t count );

PL_EXTERN char plReadInt8( PLFile* ptr, bool* status );
PL_EXTERN int16_t plReadInt16( PLFile* ptr, bool big_endian, bool* status );
PL_EXTERN int32_t plReadInt32( PLFile* ptr, bool big_endian, bool* status );
PL_EXTERN int64_t plReadInt64(PLFile* ptr, bool big_endian, bool* status);

PL_EXTERN char* plReadString(PLFile* ptr, char* str, size_t size);

typedef enum PLFileSeek {
#if defined( SEEK_SET ) && defined( SEEK_CUR ) && defined( SEEK_END )
	PL_SEEK_SET = SEEK_SET,
	PL_SEEK_CUR = SEEK_CUR,
	PL_SEEK_END = SEEK_END
#else
	PL_SEEK_SET, PL_SEEK_CUR, PL_SEEK_END
#endif
} PLFileSeek;

PL_EXTERN bool plFileSeek( PLFile* ptr, long int pos, PLFileSeek seek );
PL_EXTERN void plRewindFile( PLFile* ptr );

/** FS Mounting **/

typedef struct PLFileSystemMount PLFileSystemMount;

PL_EXTERN PLFileSystemMount* plMountLocalLocation( const char* path );
PL_EXTERN PLFileSystemMount* plMountLocation( const char* path );

PL_EXTERN void plClearMountedLocation( PLFileSystemMount* location );
PL_EXTERN void plClearMountedLocations( void );

/****/

PL_EXTERN_C_END
