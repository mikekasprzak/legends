// - ------------------------------------------------------------------------------------------ - //
#ifndef _WIN32_WCE
#include <stdio.h>
#include <stdlib.h>
#else // _WIN32_WCE //
#include <stddef.h>
#endif // _WIN32_WCE //
// - ------------------------------------------------------------------------------------------ - //
//#include "PVRTexture_Load.h"
// - ------------------------------------------------------------------------------------------ - //

//// - ------------------------------------------------------------------------------------------ - //
//#ifdef IPHONE_BUILD
//const char* MyAppName = "Smiles.app";
//#endif // IPHONE_BUILD //
//// - ------------------------------------------------------------------------------------------ - //
//
//// - ------------------------------------------------------------------------------------------ - //
//extern unsigned int gelLoadTexture( const char* MyFile );
//// - ------------------------------------------------------------------------------------------ - //
//unsigned int gelLoadTexture( const char* MyFile ) {
//	char File[1024];
//
//#ifdef IPHONE_BUILD
//	sprintf(File,"%s/%s/Content/%s", getenv("HOME"), MyAppName, MyFile);
//#else // IPHONE_BUILD //
//	sprintf(File,"Content/%s", MyFile);
//#endif // IPHONE_BUILD //
//
//	const char* DataFile = &File[0];
//	
//	return LoadGL_PVRTexture( DataFile );
//}
//// - ------------------------------------------------------------------------------------------ - //
