// - ------------------------------------------------------------------------------------------ - //
// GelContentHandle - File IO wrapping and utility library for reading/writing assets //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_GELCore_GelContentHandle_H__
#define __Library_GELCore_GelContentHandle_H__
// - ------------------------------------------------------------------------------------------ - //
// File IO Methods //
#include "GelFile.h"
//#include "GelZipFile.h"

// Utilities for associating FileIO methods with the function types
#include "File_MakeHandleUtil.h"
#include "File_ReadWriteUtil.h"

// TODO: Some method of making GelContentHandle Read-only //
MAKE_GEL_FILE_HANDLE_FUNCTIONS( GelFile, GelContentHandle );
MAKE_GEL_FILE_HANDLEINIT_FUNCTIONS( GelFile, GelContentHandle );
MAKE_GEL_FILE_READWRITE_UTIL_FUNCTIONS( GelContentHandle );
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_GELCore_GelContentHandle_H__ //
// - ------------------------------------------------------------------------------------------ - //
