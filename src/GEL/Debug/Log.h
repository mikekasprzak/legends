// - ------------------------------------------------------------------------------------------ - //
// Log //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_DEBUG_Log_H__
#define __GEL_DEBUG_Log_H__
// - ------------------------------------------------------------------------------------------ - //
// Logging Code. //
// * Log and wLog always write to the console (except on game consoles).
// * DLog and wDLong write only in the debug build.
// * VLog and wVLog are only written when the Logging mode is 2 or higher.
// * VVLog and wVVLog are only written when the Logging mode is 3 or higher.
// * VVVLog and wVVVLog are only written when the Logging mode is 4 or higher.
// * ELog and wELog do Error Logging - Print some extended debuging information.
// * wLog, wDLog, wVLog, wELog are the w_char versions of Log.
// * LogFlush() makes sure the log file is written to before continuing (in case of bluescreens)
// - ------------------------------------------------------------------------------------------ - //
#ifndef NOLOGGING
// - ------------------------------------------------------------------------------------------ - //
extern int LogLevel;
// - ------------------------------------------------------------------------------------------ - //
/*
// - ------------------------------------------------------------------------------------------ - //
// Compiler Specific //
// - ------------------------------------------------------------------------------------------ - //
#ifdef _MSC_VER
// - ------------------------------------------------------------------------------------------ - //
	#define Log( ... ) \
		if ( LogLevel >= 1 ) \
			printf( __VA_ARGS__ )
	#define wLog( ... ) \
		if ( LogLevel >= 1 ) \
			wprintf( __VA_ARGS__ )
	// - ------------------------------------------------------------------------------------------ - //
	#define VLog( ... ) \
		if ( LogLevel >= 2 ) \
			Log( __VA_ARGS__ )
	#define wVLog( ... ) \
		if ( LogLevel >= 2 ) \
			wLog( __VA_ARGS__ )
	// - ------------------------------------------------------------------------------------------ - //
	#define VVLog( ... ) \
		if ( LogLevel >= 3 ) \
			Log( __VA_ARGS__ )
	#define wVVLog( ... ) \
		if ( LogLevel >= 3 ) \
			wLog( __VA_ARGS__ )
	// - ------------------------------------------------------------------------------------------ - //
	#define VVVLog( ... ) \
		if ( LogLevel >= 4 ) \
			Log( __VA_ARGS__ )
	#define wVVVLog( ... ) \
		if ( LogLevel >= 4 ) \
			wLog( __VA_ARGS__ )
	// - ------------------------------------------------------------------------------------------ - //
	#define ELog( ___ARGS... ) \
		Log( "** C++ ERROR ** LINE %i ** %s ** %s ** ", __LINE__, __FUNCTION__, __FILE__ ); \
		Log( ___ARGS )
	#define wELog( ___ARGS... ) \
		wLog( "** C++ ERROR ** LINE %i ** %s ** %s ** ", __LINE__, __FUNCTION__, __FILE__ ); \
		wLog( ___ARGS )
	// - ------------------------------------------------------------------------------------------ - //
	#ifndef NDEBUG
		#define DLog( ... ) \
			Log( __VA_ARGS__ )
		#define wDLog( ... ) \
			wLog( __VA_ARGS__ )
	#else // NDEBUG //
		#define DLog( ... ) ;
		#define wDLog( ... ) ;
	#endif // NDEBUG //
// - ------------------------------------------------------------------------------------------ - //
#else // Default Logging Via Printf //
// - ------------------------------------------------------------------------------------------ - //
	#define _Log( ___ARGS... ) \
		printf( ___ARGS )
	// - ------------------------------------------------------------------------------------------ - //
	#define Log( ___ARGS... ) \
		_Log( ___ARGS )
//		{ if ( LogLevel >= 1 ) Log( ___ARGS ); }
	#define wLog( ___ARGS... ) \
		if ( LogLevel >= 1 ) \
			wprintf( ___ARGS )
	// - ------------------------------------------------------------------------------------------ - //
	#define VLog( ___ARGS... ) \
		_Log( ___ARGS )
//		{ if ( LogLevel >= 2 ) Log( ___ARGS ); }
	#define wVLog( ___ARGS... ) \
		if ( LogLevel >= 2 ) \
			wLog( ___ARGS )
	// - ------------------------------------------------------------------------------------------ - //
	#define VVLog( ___ARGS... ) \
		if ( LogLevel >= 2 ) \
			_Log( ___ARGS )
	#define wVVLog( ___ARGS... ) \
		if ( LogLevel >= 3 ) \
			wLog( ___ARGS )
	// - ------------------------------------------------------------------------------------------ - //
	#define VVVLog( ___ARGS... ) \
		if ( LogLevel >= 4 ) \
			_Log( ___ARGS )
	#define wVVVLog( ___ARGS... ) \
		if ( LogLevel >= 4 ) \
			wLog( ___ARGS )
	// - ------------------------------------------------------------------------------------------ - //
	#define ELog( ___ARGS... ) \
		_Log( "** C++ ERROR ** LINE %i ** %s ** %s ** ", __LINE__, __PRETTY_FUNCTION__, __FILE__ ); \
		_Log( ___ARGS )
	#define wELog( ___ARGS... ) \
		wLog( "** C++ ERROR ** LINE %i ** %s ** %s ** ", __LINE__, __PRETTY_FUNCTION__, __FILE__ ); \
		wLog( ___ARGS )
	// - ------------------------------------------------------------------------------------------ - //
	#ifndef NDEBUG
		#define DLog( ___ARGS... ) \
			_Log( ___ARGS )
		#define wDLog( ___ARGS... ) \
			wLog( ___ARGS )
	#else // NDEBUG //
		#define DLog( ... ) ;
		#define wDLog( ... ) ;
	#endif // NDEBUG //
	// - ------------------------------------------------------------------------------------------ - //
// - ------------------------------------------------------------------------------------------ - //
#endif // _MSC_VER //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Shared Logging Features //
// - ------------------------------------------------------------------------------------------ - //
#define LogFlush() \
	fflush(0)
// - ------------------------------------------------------------------------------------------ - //
#ifndef NDEBUG
	#define DLogFlush() \
		LogFlush()
#else // NDEBUG //
	#define DLogFlush() ;
#endif // NDEBUG //
// - ------------------------------------------------------------------------------------------ - //
*/

// The "Forcefully Always Log" version // 
void LogAlways( const char* s, ... );
void _LogAlways( const char* s, ... );

// Standard Logging, with newline //
void Log( const char* s, ... );
void VLog( const char* s, ... );
void VVLog( const char* s, ... );
void VVVLog( const char* s, ... );

// Logging, without newline //
void _Log( const char* s, ... );
void _VLog( const char* s, ... );
void _VVLog( const char* s, ... );
void _VVVLog( const char* s, ... );

#ifndef NDEBUG
	#define DLog( ___ARGS... ) \
		LogAlways( ___ARGS )
	#define _DLog( ___ARGS... ) \
		_LogAlways( ___ARGS )
#else // NDEBUG //
	#define DLog( ... ) ;
	#define _DLog( ... ) ;
#endif // NDEBUG //

// Log and Return //
#define return_Log( ___ARGS... ) \
	{ Log( __ARGS ); return; }
#define return_VLog( ___ARGS... ) \
	{ VLog( __ARGS ); return; }
#define return_VVLog( ___ARGS... ) \
	{ VVLog( __ARGS ); return; }
#define return_VVVLog( ___ARGS... ) \
	{ VVVLog( __ARGS ); return; }

#define return_value_Log( ___VAL, ___ARGS... ) \
	{ Log( __ARGS ); return ___VAL; }
#define return_value_VLog( ___VAL, ___ARGS... ) \
	{ VLog( __ARGS ); return ___VAL; }
#define return_value_VVLog( ___VAL, ___ARGS... ) \
	{ VVLog( __ARGS ); return ___VAL; }
#define return_value_VVVLog( ___VAL, ___ARGS... ) \
	{ VVVLog( __ARGS ); return ___VAL; }

// - ------------------------------------------------------------------------------------------ - //
#else // NOLOGGING //
// - ------------------------------------------------------------------------------------------ - //

#define LogAlways( ... ) ;
#define _LogAlways( ... ) ;

#define Log( ... ) ;
#define VLog( ... ) ;
#define VVLog( ... ) ;
#define VVVLog( ... ) ;
#define DLog( ... ) ;

#define _Log( ... ) ;
#define _VLog( ... ) ;
#define _VVLog( ... ) ;
#define _VVVLog( ... ) ;
#define _DLog( ... ) ;

#define return_Log( ... ) ;
#define return_VLog( ... ) ;
#define return_VVLog( ... ) ;
#define return_VVVLog( ... ) ;
#define return_value_Log( ... ) ;
#define return_value_VLog( ... ) ;
#define return_value_VVLog( ... ) ;
#define return_value_VVVLog( ... ) ;

// - ------------------------------------------------------------------------------------------ - //
#endif // NOLOGGING //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_DEBUG_Log_H__ //
// - ------------------------------------------------------------------------------------------ - //
