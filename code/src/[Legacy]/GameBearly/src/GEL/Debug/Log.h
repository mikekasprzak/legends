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
	#define NO_ANSI_COLOR_CODES

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

#ifndef NO_ANSI_COLOR_CODES
	#define ANSI_HEADER					"\033["
//	#define ANSI(attr,fg) 				"\033[" attr ";" fg "m"

	#define ANSI_NORMAL					"\033[0m"
	#define ANSI_RESET					ANSI_NORMAL
	#define ANSI_NEGATIVE				"\033[7m"

	#define ANSI_BLACK					"\033[0;30m"
	#define ANSI_RED					"\033[0;31m"
	#define ANSI_GREEN					"\033[0;32m"
	#define ANSI_YELLOW					"\033[0;33m"
	#define ANSI_BLUE					"\033[0;34m"
	#define ANSI_MAGENTA				"\033[0;35m"
	#define ANSI_CYAN					"\033[0;36m"
	#define ANSI_WHITE					"\033[0;37m"

	#define ANSI_BG_BLACK				"\033[0;40m"
	#define ANSI_BG_RED					"\033[0;41m"
	#define ANSI_BG_GREEN				"\033[0;42m"
	#define ANSI_BG_YELLOW				"\033[0;43m"
	#define ANSI_BG_BLUE				"\033[0;44m"
	#define ANSI_BG_MAGENTA				"\033[0;45m"
	#define ANSI_BG_CYAN				"\033[0;46m"
	#define ANSI_BG_WHITE				"\033[0;47m"
#else // NO_ANSI_COLOR_CODES //
	#define ANSI_HEADER					""
	#define ANSI(attr,fg) 				""

	#define ANSI_NORMAL					""
	#define ANSI_RESET					ANSI_NORMAL
	#define ANSI_NEGATIVE				""

	#define ANSI_BLACK					""
	#define ANSI_RED					""
	#define ANSI_GREEN					""
	#define ANSI_YELLOW					""
	#define ANSI_BLUE					""
	#define ANSI_MAGENTA				""
	#define ANSI_CYAN					""
	#define ANSI_WHITE					""

	#define ANSI_BG_BLACK				""
	#define ANSI_BG_RED					""
	#define ANSI_BG_GREEN				""
	#define ANSI_BG_YELLOW				""
	#define ANSI_BG_BLUE				""
	#define ANSI_BG_MAGENTA				""
	#define ANSI_BG_CYAN				""
	#define ANSI_BG_WHITE				""
#endif // NO_ANSI_COLOR_CODES //

// Emscripten Hack //
#ifdef EMSCRIPTEN
	#define Log( ... ) printf( __VA_ARGS__ ); printf( "\n" )
	#define VLog( ... ) printf( __VA_ARGS__ ); printf( "\n" )
	#define VVLog( ... ) printf( __VA_ARGS__ ); printf( "\n" )
	#define VVVLog( ... ) printf( __VA_ARGS__ ); printf( "\n" )
#else // EMSCRIPTEN //
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

#endif // EMSCRIPTEN //

// - ------------------------------------------------------------------------------------------ - //
#ifdef _MSC_VER
// - ------------------------------------------------------------------------------------------ - //
// Log and Return //
#define return_Log( ... ) \
	{ Log( __VA_ARGS__ ); return; }
#define return_VLog( ... ) \
	{ VLog( __VA_ARGS__ ); return; }
#define return_VVLog( ... ) \
	{ VVLog( __VA_ARGS__ ); return; }
#define return_VVVLog( ... ) \
	{ VVVLog( __VA_ARGS__ ); return; }

#define return_value_Log( ___VAL, ... ) \
	{ Log( __VA_ARGS__ ); return ___VAL; }
#define return_value_VLog( ___VAL, ... ) \
	{ VLog( __VA_ARGS__ ); return ___VAL; }
#define return_value_VVLog( ___VAL, ... ) \
	{ VVLog( __VA_ARGS__ ); return ___VAL; }
#define return_value_VVVLog( ___VAL, ... ) \
	{ VVVLog( __VA_ARGS__ ); return ___VAL; }
// - ------------------------------------------------------------------------------------------ - //
#else // _MSC_VER //
// - ------------------------------------------------------------------------------------------ - //
// Log and Return //
#define return_Log( ___ARGS... ) \
	{ Log( ___ARGS ); return; }
#define return_VLog( ___ARGS... ) \
	{ VLog( ___ARGS ); return; }
#define return_VVLog( ___ARGS... ) \
	{ VVLog( ___ARGS ); return; }
#define return_VVVLog( ___ARGS... ) \
	{ VVVLog( ___ARGS ); return; }

#define return_value_Log( ___VAL, ___ARGS... ) \
	{ Log( ___ARGS ); return ___VAL; }
#define return_value_VLog( ___VAL, ___ARGS... ) \
	{ VLog( ___ARGS ); return ___VAL; }
#define return_value_VVLog( ___VAL, ___ARGS... ) \
	{ VVLog( ___ARGS ); return ___VAL; }
#define return_value_VVVLog( ___VAL, ___ARGS... ) \
	{ VVVLog( ___ARGS ); return ___VAL; }
// - ------------------------------------------------------------------------------------------ - //
#endif // _MSC_VER //
// - ------------------------------------------------------------------------------------------ - //

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
