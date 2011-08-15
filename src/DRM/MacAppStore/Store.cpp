// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_MACAPPSTORE
// - ------------------------------------------------------------------------------------------ - //
#include <Debug/GelDebug.h>
#include <Core/GelString.h>
#include <Project.h>
#include "Store.h"
// - ------------------------------------------------------------------------------------------ - //
#include <mach-o/dyld.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
bool gelStoreAuthorize() {
	bool Authorized = false;

	Log( "- Initializing Mac App Store\n" );
	
	uint32_t Size = 2048;
	char ReceiptDir[2048];
	
	_NSGetExecutablePath( ReceiptDir, &Size );

	int Len = length_String( ReceiptDir );
	for( ; Len--; ) {
		if (ReceiptDir[Len] == '\\') {
			ReceiptDir[Len+1] = 0;	
			break;
		}
		else if (ReceiptDir[Len] == '/') {
			ReceiptDir[Len+1] = 0;	
			break;
		}
	}

	ReceiptDir[Len] = 0;
	
	for( ; Len--; ) {
		if (ReceiptDir[Len] == '\\') {
			ReceiptDir[Len+1] = 0;	
			break;
		}
		else if (ReceiptDir[Len] == '/') {
			ReceiptDir[Len+1] = 0;	
			break;
		}
	}
	
	const char* Res = "_MASReceipt/Receipt";
	copy_String( Res, &ReceiptDir[length_String(ReceiptDir)] );
	
	Log( ">> %s\n", ReceiptDir );

	//Log( "- Authorizing (File Exists)...\n" );
	Authorized = exists_File( ReceiptDir );
	
	return Authorized;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void gelStoreExit() {

}
// - ------------------------------------------------------------------------------------------ - //
int gelStoreGetExitCode() {
	return 173;
}
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_MACAPPSTORE //
// - ------------------------------------------------------------------------------------------ - //
