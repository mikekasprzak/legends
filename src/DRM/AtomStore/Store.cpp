// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_ATOMSTORE
// - ------------------------------------------------------------------------------------------ - //
//#ifdef _MSC_VER
#include <AtomStore/AtomStore/adpcore.h>
//#else // _MSC_VER //
//#include <adpcore/adpcore.h>
//#endif // _MSC_VER //
// - ------------------------------------------------------------------------------------------ - //
#include <Debug/GelDebug.h>
#include <Project.h>
#include "Store.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
extern const ADP_APPLICATIONID myApplicationID;
// - ------------------------------------------------------------------------------------------ - //
#ifdef PRODUCT_FINAL
#define APPID myApplicationID
#else // PRODUCT_FINAL //
#define APPID ADP_DEBUG_APPLICATIONID
#endif // PRODUCT_FINAL //
// - ------------------------------------------------------------------------------------------ - //

#ifdef USES_WINDOWS
#include <windows.h>

#define Notice(_msg) \
	Log(_msg); \
    MessageBox( \
        NULL, \
        TEXT( _msg ), \
        TEXT("Smiles - Error"), \
        MB_OK | MB_ICONINFORMATION | MB_SETFOREGROUND \
        );
#elif defined(USES_UNIX)
#define Notice(_msg) \
	printf(_msg);
#else // !USES_WINDOWS //
#define Notice(_msg) \
	Log(_msg);
#endif // USES_WINDOWS //

// - ------------------------------------------------------------------------------------------ - //
bool gelStoreAuthorize() {
	ADP_RET_CODE ret_code;
	bool Authorized = false;

#ifdef _MSC_VER
	wLog( L"- Initializing ADP (Intel Atom Store) API -- Version: %s (API Level: %i)...\n", ADP_API_VERSION, ADP_API_LEVEL );
#else // _MSC_VER //
	Log( "- Initializing ADP (Intel Atom Store) API -- Version: %s (API Level: %i)...\n", ADP_API_VERSION, ADP_API_LEVEL );
#endif // _MSC_VER //

	switch ( ret_code = ADP_Initialize() ) {
		case ADP_NOT_AVAILABLE: {
			Notice( "* ERROR: Failed to Initialize ADP.  Client Agent service is not running.\n" );
			break;
		}
		case ADP_INCOMPATIBLE_VERSION: {
			Notice( "* ERROR: Failed to Initialize ADP.  Incompatible Version Detected.\n" );
			break;
		}
		case ADP_FAILURE: {
			Notice( "* ERROR: Failed to Initialize ADP.  Unknown Error.\n" );
			break;
		}
//		case ADP_TIMEOUT: {
//			Notice( "* ERROR: Failed to Initialize ADP.  Timeout.\n" );
//			break;
//		}
		case ADP_SUCCESS: {
			Log( "+ SUCCESS: ADP Initialized\n" );
			Log( "- Attempting to Authorize (ADP)...\n" );
			if ( (ret_code = ADP_IsAuthorized( APPID )) != ADP_AUTHORIZED ) {
				Notice( "* ERROR: ADP Authorization Failed!\n" );
				switch ( ret_code ) {
					case ADP_NOT_AUTHORIZED:
						Notice( "* REASON: ADP_NOT_AUTHORIZED\n" );
					break;
					case ADP_AUTHORIZATION_EXPIRED:
						Notice( "* REASON: ADP_AUTHORIZATION_EXPIRED\n" );
					break;
					case ADP_NOT_AVAILABLE:
						Notice( "* REASON: ADP_NOT_AVAILABLE\n" );
					break;
					case ADP_NOT_INITIALIZED:
						Notice( "* REASON: ADP_NOT_INITIALIZED\n" );
					break;
					case ADP_FAILURE:
						Notice( "* REASON: ADP_FAILURE\n" );
					break;
					case ADP_AUTHORIZED:
						Notice( "* REASON: ADP_AUTHORIZED (What!?)\n" );
					break;
//					case ADP_TIMEOUT:
//						Notice( "* REASON: ADP_TIMEOUT\n" );
//					break;
					default:
						Notice( "* REASON: Unknown Response\n" );
					break;
				};
			}
			else {
				Log( "+ SUCCESS: ADP Authorization Successful\n" );
				Authorized = true;
			}
			break;
		}
		default: {
			Notice( "* ERROR: Unknown Response\n" );
			break;
		}
	};
	Log("\n");
	
	return Authorized;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void gelStoreExit() {
	ADP_RET_CODE ret_code;

	Log( "- Shutting down ADP...\n" );
	if ( (ret_code = ADP_Close()) == ADP_SUCCESS ) {
		Log( "+ SUCCESS: ADP Shutdown Successfully\n" );
	}
	else {
		Log( "* ERROR: Failed to shut down ADP!\n" );
	}
	Log( "\n" );
}
// - ------------------------------------------------------------------------------------------ - //
int gelStoreGetExitCode() {
	return 0;
}
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_ATOMSTORE //
// - ------------------------------------------------------------------------------------------ - //
