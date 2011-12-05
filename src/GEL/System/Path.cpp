// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_GEL) && !defined(NO_PLATFORM_H)
#include "../Platform.h"
#endif // USES_GEL && NO_PLATFORM_H //
// -------------------------------------------------------------------------- //

// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_WINDOWS)
// - ------------------------------------------------------------------------------------------ - //
#include <Windows.h>
#include <shlobj.h>
#include <stdio.h>
// - ------------------------------------------------------------------------------------------ - //
#elif defined(USES_WEBOS)
// - ------------------------------------------------------------------------------------------ - //
#include <PDL.h>
#include <PDLPatch.h>
// - ------------------------------------------------------------------------------------------ - //
#elif defined(USES_MACOSX)
// - ------------------------------------------------------------------------------------------ - //
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <mach-o/dyld.h>
// - ------------------------------------------------------------------------------------------ - //
#elif defined(USES_BLACKBERRY)
// - ------------------------------------------------------------------------------------------ - //
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
// - ------------------------------------------------------------------------------------------ - //
#elif defined(USES_UNIX)
// - ------------------------------------------------------------------------------------------ - //
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
// - ------------------------------------------------------------------------------------------ - //
#endif // USES //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include <Core/GelString_Core.h>
#include "Path.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void gelGetContentPath( char* AppBaseDir, const size_t AppBaseDir_Size ) {
#if defined(USES_WEBOS)
//	Log( "+ WebOS Path\n" );
	WebOS_PDL_GetCallingPath( AppBaseDir, AppBaseDir_Size );
	//PDL_GetCallingPath( AppBaseDir, AppBaseDir_Size );
#elif defined(USES_BLACKBERRY)
	char cwd[PATH_MAX];
	getcwd( cwd, PATH_MAX );

	snprintf( AppBaseDir, AppBaseDir_Size, "%s/app/native/", cwd );
#elif defined(USES_WINDOWS)
//	Log( "+ Windows Path\n" );
	GetModuleFileNameA( NULL, AppBaseDir, AppBaseDir_Size );
#elif defined(USES_MACOSX)
	// NOTE: Mac function "RealPath()" can eliminate ../../'s //
	uint32_t Size = AppBaseDir_Size;
	_NSGetExecutablePath( AppBaseDir, &Size );
#elif defined(USES_UNIX)
//	Log( "+ Unix Path\n" );
	readlink( "/proc/self/exe", AppBaseDir, AppBaseDir_Size );
#else // USES_??? //
//	Log( "+ No Path!\n" );
	AppBaseDir[0] = 0;
#endif // USES_??? //

//	Log( "+ Executable: %s\n", AppBaseDir );

	int Len = length_String( AppBaseDir );
	for( ; Len--; ) {
		if (AppBaseDir[Len] == '\\') {
			AppBaseDir[Len+1] = 0;	
			break;
		}
		else if (AppBaseDir[Len] == '/') {
			AppBaseDir[Len+1] = 0;	
			break;
		}
	}

#if defined(USES_MACOSX)
	const char* Res = "../Resources/";
	copy_String( Res, &AppBaseDir[strlen(AppBaseDir)] );
//#elif defined(USES_AIRPLAY_SYMBIAN)
//	copy_String( "ram://", AppBaseDir );
#elif defined(USES_AIRPLAY)
//	copy_String( "rom://", AppBaseDir );
	copy_String( "/", AppBaseDir );
#endif // USES //
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void gelGetStoragePath( char* SaveDir, const size_t SaveDir_Size ) {
#if defined(USES_WEBOS)
	WebOS_PDL_GetDataFilePath( "", SaveDir, SaveDir_Size );
#elif defined(USES_BLACKBERRY)
	char cwd[PATH_MAX];
	getcwd( cwd, PATH_MAX );

	snprintf( SaveDir, SaveDir_Size, "%s/data/", cwd );
#elif defined(USES_BADA)
	sprintf( SaveDir, "/Home/" );
#elif defined(USES_WINDOWS)
	char Path[_MAX_PATH+1];

	// SHGFP_TYPE_DEFAULT = 1
	SHGetFolderPathA( NULL, CSIDL_APPDATA, NULL, 1, Path );
		
	sprintf( SaveDir, "%s\\Sykhronics\\", &Path[0] );
	CreateDirectoryA( SaveDir, NULL );		
#elif defined(USES_MACOSX)
	sprintf( SaveDir, "%s/Library/Application Support/", getenv("HOME") );
	mkdir( SaveDir, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH );
#elif defined(USES_UNIX)
	sprintf( SaveDir, "%s/.sykhronics/", getenv("HOME") );
	mkdir( SaveDir, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH );
#elif defined(USES_AIRPLAY)
	copy_String( "ram://", SaveDir );
#else // USES_??? //
	SaveDir[0] = 0;
#endif // USES_??? //
}
// - ------------------------------------------------------------------------------------------ - //
