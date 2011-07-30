// - ------------------------------------------------------------------------------------------ - //
// GelStorageHandle - File IO wrapping and utility library for reading/writing save data //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_GELCore_GelStorageHandle_H__
#define __Library_GELCore_GelStorageHandle_H__
// - ------------------------------------------------------------------------------------------ - //
// File IO Methods //
#include "GelFile.h"
//#include "GelZipFile.h"

// Utilities for associating FileIO methods with the function types
#include "File_MakeHandleUtil.h"
#include "File_ReadWriteUtil.h"

MAKE_GEL_FILE_HANDLE_FUNCTIONS( GelFile, GelStorageHandle );
MAKE_GEL_FILE_HANDLEINIT_FUNCTIONS( GelFile, GelStorageHandle );
MAKE_GEL_FILE_READWRITE_UTIL_FUNCTIONS( GelStorageHandle );
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_GELCore_GelStorageHandle_H__ //
// - ------------------------------------------------------------------------------------------ - //
