// - ------------------------------------------------------------------------------------------ - //
// Uncomment this once webOS is all PDK friendly //
//#define DONT_USE_DLSYM
// - ------------------------------------------------------------------------------------------ - //
#ifndef DONT_USE_DLSYM
#include <dlfcn.h>
#endif // DONT_USE_DLSYM //
// - ------------------------------------------------------------------------------------------ - //
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
// - ------------------------------------------------------------------------------------------ - //
#ifndef PALM_APPID
#error PALM_APPID NOT DEFINED
#endif // PALM_APPID //
// - ------------------------------------------------------------------------------------------ - //

#ifndef DONT_USE_DLSYM
#define RTLD_DEFAULT ((void *) 0)
#endif // DONT_USE_DLSYM //

// - ------------------------------------------------------------------------------------------ - //
typedef enum {
    PDL_NOERROR         = 0,
    PDL_EMEMORY,        /* Memory failure */
    PDL_ECONNECTION,    /* Connection error */
    PDL_INVALIDINPUT,   /* Problem with the sent-in params */
    PDL_EOTHER,         /* Other error */
    PDL_UNINIT,         /* The function relies on a client-called init function that has never been called */
    PDL_NOTALLOWED,     /* A configurable option prevents the operation from succeeding (Ex: Location Services disabled by user = GPS won't work) */
    PDL_LICENSEFAILURE, /* The license of the application is invalid or missing. */
    PDL_STRINGTOOSMALL, /* A sent-in string that was to be filled was too small for the data needed */
} PDL_Err;
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
extern PDL_Err PDL_Init(unsigned int flags) __attribute__((weak));
// - ------------------------------------------------------------------------------------------ - //
PDL_Err WebOS_PDL_Init(unsigned int flags);
// - ------------------------------------------------------------------------------------------ - //
PDL_Err WebOS_PDL_Init(unsigned int flags) {
#ifndef DONT_USE_DLSYM
	if ( dlsym(RTLD_DEFAULT, "PDL_Init") )
		return PDL_Init( flags );
 
	return PDL_NOERROR;
#else // DONT_USE_DLSYM //
	return PDL_Init( flags );
#endif // DONT_USE_DLSYM //
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
extern PDL_Err PDL_GetDataFilePath(const char *dataFileName, char *buffer, int bufferLen) __attribute__((weak));
// - ------------------------------------------------------------------------------------------ - //
PDL_Err WebOS_PDL_GetDataFilePath(const char *dataFileName, char *buffer, int bufferLen);
// - ------------------------------------------------------------------------------------------ - //
PDL_Err WebOS_PDL_GetDataFilePath(const char *dataFileName, char *buffer, int bufferLen) {
#ifndef DONT_USE_DLSYM
	if ( dlsym(RTLD_DEFAULT, "PDL_GetDataFilePath") )
		return PDL_GetDataFilePath( dataFileName, buffer, bufferLen );
 
 	mkdir( "//media/internal/appdata", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH );
 	mkdir( "//media/internal/appdata/" PALM_APPID, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH );
	snprintf(buffer, bufferLen, "//media/internal/appdata/" PALM_APPID "/%s", dataFileName);
	return PDL_NOERROR;
#else // DONT_USE_DLSYM //
	return PDL_GetDataFilePath( dataFileName, buffer, bufferLen );
#endif // DONT_USE_DLSYM //
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
extern PDL_Err PDL_GetCallingPath(char *buffer, int bufferLen) __attribute__((weak));
// - ------------------------------------------------------------------------------------------ - //
PDL_Err WebOS_PDL_GetCallingPath(char *buffer, int bufferLen);
// - ------------------------------------------------------------------------------------------ - //
PDL_Err WebOS_PDL_GetCallingPath(char *buffer, int bufferLen) {
#ifndef DONT_USE_DLSYM
	if ( dlsym(RTLD_DEFAULT, "PDL_GetCallingPath") )
		return PDL_GetCallingPath( buffer, bufferLen );
 
	snprintf(buffer, bufferLen, "/media/cryptofs/apps/usr/palm/applications/" PALM_APPID "/");
	return PDL_NOERROR;
#else // DONT_USE_DLSYM //
	return PDL_GetCallingPath( buffer, bufferLen );
#endif // DONT_USE_DLSYM //
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
extern int PDL_isAppLicensedForDevice(const char *appid) __attribute__((weak));
// - ------------------------------------------------------------------------------------------ - //
int WebOS_PDL_isAppLicensedForDevice(const char *appid);
// - ------------------------------------------------------------------------------------------ - //
int WebOS_PDL_isAppLicensedForDevice(const char *appid) {
#ifndef DONT_USE_DLSYM
	if ( dlsym(RTLD_DEFAULT, "PDL_isAppLicensedForDevice") )
		return PDL_isAppLicensedForDevice( appid );
 
	return 1;
#else // DONT_USE_DLSYM //
	return PDL_isAppLicensedForDevice( appid );
#endif // DONT_USE_DLSYM //
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
PDL_Err WebOS_145Patch_GetDataFilePath( const char *dataFileName, char *buffer, int bufferLen);
// - ------------------------------------------------------------------------------------------ - //
// Per request from Palm (Ben C), store load/save data in the App directory //
PDL_Err WebOS_145Patch_GetDataFilePath( const char *dataFileName, char *buffer, int bufferLen) {
	WebOS_PDL_GetCallingPath( buffer, bufferLen );
	
	size_t Length = strlen( buffer );
	
	snprintf( &buffer[Length], bufferLen-Length, "%s", dataFileName );
	
	return PDL_NOERROR;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
PDL_Err WebOS_140Patch_GetDataFilePath( const char *dataFileName, char *buffer, int bufferLen);
// - ------------------------------------------------------------------------------------------ - //
// Returns only the path, does not create directories //
PDL_Err WebOS_140Patch_GetDataFilePath( const char *dataFileName, char *buffer, int bufferLen) {
	snprintf(buffer, bufferLen, "//media/internal/appdata/" PALM_APPID "/%s", dataFileName);
	return PDL_NOERROR;
}
// - ------------------------------------------------------------------------------------------ - //

/*
// - ------------------------------------------------------------------------------------------ - //
extern int PDL_GetHardwareID(void) __attribute__((weak));
// - ------------------------------------------------------------------------------------------ - //
int WebOS_PDL_GetHardwareID(void);
// - ------------------------------------------------------------------------------------------ - //
int WebOS_PDL_GetHardwareID(void) {
#ifndef DONT_USE_DLSYM
	if ( dlsym(RTLD_DEFAULT, "PDL_GetHardwareID") )
		return PDL_GetHardwareID();
	
	return -1; // HARDWARE_UNKNOWN //
#else // DONT_USE_DLSYM //
	return PDL_GetHardwareID();
#endif // DONT_USE_DLSYM //
}
// - ------------------------------------------------------------------------------------------ - //
*/
