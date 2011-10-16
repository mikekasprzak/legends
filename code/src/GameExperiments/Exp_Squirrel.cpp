
// - ------------------------------------------------------------------------------------------ - //
#include <Debug/GelDebug.h>
#include <Core/DataBlock.h>

// TODO: replace this with the var-args giving header... I dunno what that is... net is down //
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
struct sqScript {
	DataBlock* Data;
	int Pos;
	
	inline sqScript() :
		Data( 0 ),
		Pos( 0 )
	{	
	}
	
	inline sqScript( const char* InFile ) :
		Pos( 0 )
	{
		Data = new_read_DataBlock( InFile );
	}
	
	inline ~sqScript() {
		if ( Data )
			delete_DataBlock( Data );
	}
	
	inline char GetChar() {
		//assert( Data );
		if ( Pos != Data->Size )
			return Data->Data[Pos++];
		return 0;
	}
};
// - ------------------------------------------------------------------------------------------ - //
SQInteger sqScript_Read( SQUserPointer Data ) {
	return ((sqScript*)Data)->GetChar();
}
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
void printfunc(HSQUIRRELVM v,const SQChar *s,...)
{
	va_list vl;
	va_start(vl, s);
	// these two are the same thing, and this works fine //
	scvprintf(stdout, s, vl);
//	printf(s, vl);
	va_end(vl);
}
// - ------------------------------------------------------------------------------------------ - //
void errorfunc(HSQUIRRELVM v,const SQChar *s,...)
{
	va_list vl;
	va_start(vl, s);
	// these two aren't //
	scvprintf(stderr, s, vl);
//	printf(s, vl);
	va_end(vl);
}
// - ------------------------------------------------------------------------------------------ - //

extern void CallExp_Squirrel();
void CallExp_Squirrel() {
	Log("+ Now Testing Squirrel\n");
	{
		HSQUIRRELVM v;
		v = sq_open( 1024 );
		
		// Setup //
		sq_setprintfunc(v,printfunc,errorfunc);
		
		// Push the root table, to be sure the libraries get added to it //
		sq_pushroottable(v);
	
		sqstd_register_iolib(v);
		sqstd_register_bloblib(v);
		sqstd_register_mathlib(v);
		sqstd_register_systemlib(v);
		sqstd_register_stringlib(v);

		//aux library
		//sets error handlers
		sqstd_seterrorhandlers(v);
		
		// Compile and Run a script //
		char FileName[] = "Content/Misc/Things.nut";
		
//		sq_pushroottable(v);
//		sqstd_dofile( v, FileName, false, false );
//		sq_pop(v,1);

		//sqScript MrNuts( FileName );
		//SQRESULT Error = sq_compile( v, sqScript_Read, (SQUserPointer)&MrNuts, FileName, false );
		
		DataBlock* MrNuts = new_read_DataBlock( FileName );
		
		Log( "+ Compiling \"%s\"...\n", FileName );
//		sq_pushroottable(v);
		SQRESULT Error = sq_compilebuffer( v, MrNuts->Data, MrNuts->Size, FileName, true );
		
		if ( Error ) {
			Log( "* Squirrel Compile Error! %i\n", Error );
		}
		else {
			Log( "- Success! Executing...\n" );

			// If the compile was a success, the stack contains a function //			
			int StackTop = sq_gettop( v );
			Log( "* Stack Top: %i\n", StackTop );

			unsigned int Params = 0;
			unsigned int FreeVars = 0;
			sq_getclosureinfo( v, -1, (SQUnsignedInteger*)&Params, (SQUnsignedInteger*)&FreeVars );
			Log( "* Function Info: Params: %i  FreeVars: %i\n", Params, FreeVars );
			
			sq_pushroottable( v );
			sq_call( v, 1, false, true );
			
			sq_settop( v, StackTop );

////			sq_pushroottable(v);
//
//			// Found this exact configuration (push -2, call 1 arg, remove -1) inside dofile //
//			sq_push( v,-2 );
//			sq_call( v, 1, false, true );
//			sq_remove( v, -1 );
//
////			sq_pop(v,1);
		}
		
		delete_DataBlock( MrNuts );
	
		sq_close(v);
	}
	Log("- Done Testing Squirrel\n");
	Log("\n");
}
