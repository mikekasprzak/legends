// - ------------------------------------------------------------------------------------------ - //
#include <Debug/Log.h>
#include <Core/DataBlock.h>
// - ------------------------------------------------------------------------------------------ - //
#include "Game.h"
// - ------------------------------------------------------------------------------------------ - //
#include <squirrel.h>

#include <sqstdio.h>
#include <sqstdblob.h>
#include <sqstdmath.h>	
#include <sqstdsystem.h>
#include <sqstdstring.h>
#include <sqstdaux.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#ifdef SQUNICODE
	#define scfprintf fwprintf
	#define scfopen	_wfopen
	#define scvprintf vfwprintf
#else
	#define scfprintf fprintf
	#define scfopen	fopen
	#define scvprintf vfprintf
#endif
// - ------------------------------------------------------------------------------------------ - //
void cGame::vm_PrintFunc( HSQUIRRELVM v, const SQChar *s, ... )
{
	va_list vl;
	va_start(vl, s);
	// these two are the same thing, and this works fine //
	scvprintf(stdout, s, vl);
//	printf(s, vl);
	va_end(vl);
}
// - ------------------------------------------------------------------------------------------ - //
void cGame::vm_ErrorFunc( HSQUIRRELVM v, const SQChar *s, ... )
{
	va_list vl;
	va_start(vl, s);
	// these two aren't //
	scvprintf(stderr, s, vl);
//	printf(s, vl);
	va_end(vl);
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cGame::vm_Init() {
	const int VM_STACK_SIZE = 1024;
	vm = sq_open( VM_STACK_SIZE );
	Log( "+ Squirrel VM created (%i level stack)\n", VM_STACK_SIZE ); 

	// Setup //
	sq_setprintfunc( vm, vm_PrintFunc, vm_ErrorFunc );
	
	Log( "* Loading Standard Libraries...\n" );
	
	// Push the root table, to be sure the libraries get added to it //
	sq_pushroottable( vm );

	sqstd_register_iolib( vm );
	sqstd_register_bloblib( vm );
	sqstd_register_mathlib( vm );
	sqstd_register_systemlib( vm );
	sqstd_register_stringlib( vm );

	//aux library
	//sets error handlers
	sqstd_seterrorhandlers( vm );
	Log( "- Squirrel VM setup complete.\n" );
}
// - ------------------------------------------------------------------------------------------ - //
void cGame::vm_Exit() {
	Log( "+ Shutting down Squirrel VM...\n" );
	sq_close( vm );
	Log( "- Done Squirrel VM shutdown.\n" );
	Log( "\n" );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// NOTE: FileName is for better Errors only //
SQRESULT cGame::vm_CompileAndRun( DataBlock* InFile, const char* FileName ) {
	Log( "+ Compiling \"%s\"...\n", FileName );
	SQRESULT Error = sq_compilebuffer( vm, InFile->Data, InFile->Size, FileName, true );

	if ( Error ) {
		ELog( "- Squirrel Compile Error! %i\n", Error );
	}
	else {
		Log( "- Compiled Successfully!\n" );
		Log( "+ Executing \"%s\"...\n", FileName );

		int StackTop = sq_gettop( vm );
		VVLog( "* Stack Top: %i\n", StackTop );

		unsigned int Params = 0;
		unsigned int FreeVars = 0;
		
		sq_getclosureinfo( vm, -1, (SQUnsignedInteger*)&Params, (SQUnsignedInteger*)&FreeVars );
		VLog( "* Function Info: Params: %i  FreeVars: %i\n", Params, FreeVars );
		
		sq_pushroottable( vm );
		Error = sq_call( vm, 1, false, true );
		
		sq_settop( vm, StackTop );
		Log( "- Finished running \"%s\"\n", FileName );
	}
	
	return Error;
}
// - ------------------------------------------------------------------------------------------ - //
