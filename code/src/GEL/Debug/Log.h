// - ------------------------------------------------------------------------------------------ - //
// Logging //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_DEBUG_Log_H__
#define __GEL_DEBUG_Log_H__
// - ------------------------------------------------------------------------------------------ - //
#include <stdarg.h>
// - ------------------------------------------------------------------------------------------ - //
#ifdef NO_LOGGING
	#define NO_FLOGGING				// FILE/STDIO Logging (either but not both) //
	#define NO_MLOGGING				// Memory Logging - In Game Console //
	#define LOG_LEVEL 0				// Disable Log Functions (Log=1, VLog=2, VVLog=3, VVVLog=4) //
	#define DEFAULT_LOG_LEVEL 0		// Initial Log Level is 0 (Lets you seperately say Level and Init Level //
	#define NO_LOG_COLORS			// Disable Color Codes in all Logs //
#endif // NO_LOGGING //
// - ------------------------------------------------------------------------------------------ - //
#ifdef _MSC_VER
	#define NO_FLOG_COLORS			// Disable Color Codes in FLogs //
#endif // _MSC_VER //
// - ------------------------------------------------------------------------------------------ - //
#ifdef NO_LOG_COLORS
	#define NO_FLOG_COLORS			// Disable Color Codes in FLogs //
	#define NO_MLOG_COLORS			// Disable Color Codes in MLogs //
#endif // NO_LOG_COLORS
// - ------------------------------------------------------------------------------------------ - //
// * LogAlways *always* writes to the log. - Never Use!
// * Log are only written when the Logging level is 1 or higher (default). - Macro level and Startup
// * VLog are only written when the Logging level is 2 or higher. - Verbose details about Macro/Startup
// * VVLog are only written when the Logging level is 3 or higher. - Fine grain details, overly verbose (loops)
// * VVVLog are only written when the Logging level is 4 or higher. - Ultimate detail, overkill debugging
// * DLog writes only in the debug build.
// * ELog does Error Logging - Print some extended debuging information.
// * wLogAlways, wDLog, wVLog, wELog are the w_char versions of Log.
// * _LogAlways, _DLog, _VLog *DON'T* append a newline (\n) and *DON'T* flush.
// - ------------------------------------------------------------------------------------------ - //
// Use LOG_LEVEL to force a current and maximum log level (i.e. removes other calls) //
extern int LogLevel;
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Enumeration of Color Codes //
// - ------------------------------------------------------------------------------------------ - //
enum {
	LOG_NORMAL				= -1,
	
	LOG_BLACK 				= 0,
	LOG_RED 				= 1,
	LOG_GREEN 				= 2,
	LOG_BROWN 				= 3,
	LOG_BLUE 				= 4,
	LOG_MAGENTA 			= 5,
	LOG_CYAN 				= 6,
	LOG_LIGHT_GRAY			= 7,
	LOG_DARK_GRAY 			= 8,
	LOG_LIGHT_RED 			= 9,
	LOG_LIGHT_GREEN			= 10,
	LOG_YELLOW 				= 11,
	LOG_LIGHT_BLUE 			= 12,
	LOG_LIGHT_MAGENTA 		= 13,
	LOG_LIGHT_CYAN 			= 14,
	LOG_WHITE 				= 15,

	LOG_INV_BLACK 			= 16+0,
	LOG_INV_RED 			= 16+1,
	LOG_INV_GREEN 			= 16+2,
	LOG_INV_BROWN 			= 16+3,
	LOG_INV_BLUE 			= 16+4,
	LOG_INV_MAGENTA 		= 16+5,
	LOG_INV_CYAN 			= 16+6,
	LOG_INV_LIGHT_GRAY		= 16+7,
	LOG_INV_DARK_GRAY 		= 16+8,
	LOG_INV_LIGHT_RED 		= 16+9,
	LOG_INV_LIGHT_GREEN		= 16+10,
	LOG_INV_YELLOW 			= 16+11,
	LOG_INV_LIGHT_BLUE 		= 16+12,
	LOG_INV_LIGHT_MAGENTA 	= 16+13,
	LOG_INV_LIGHT_CYAN 		= 16+14,
	LOG_INV_WHITE 			= 16+15,

	LOG_BOLD				= 8,		// Brighter Colors (ANSI style) //
	LOG_INV					= 16,		// Invered Color Scheme (BG is the color, FG is black) //
};	
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#ifndef NO_LOGGING
// - ------------------------------------------------------------------------------------------ - //
// Log Setup //
void LogInit();
void LogExit(); // Called in atexit, but included anyway. No need to call! //

void LogColor( const int Color ); // Set Color (where supported, ignored elsewhere) //
// - ------------------------------------------------------------------------------------------ - //
// Flush the log. Done automatically inside LogAlways - Do not use! //
void LogFlush();

// The "Forcefully Always Log" version - Do not use! // 
void LogAlways( const char* s, ... );
void _LogAlways( const char* s, ... );

// vprintf style, so new printf style functions can be built off these. - Do not use! //
void vLogAlways( const char* s, va_list vargs );
void _vLogAlways( const char* s, va_list vargs );

// Disabled (for now). Will need to call fwide(+1) before and fwide(-1) after each call. Also <wchar.h> //
//   These calls can afford to be wasteful, since they're mainly for logging wchar data. I will never //
//   ever actually localize the logging, so in practice wchar's are not needed by my logging code. //
#define wLogAlways( ... ) ;
#define _wLogAlways( ... ) ;
#define vwLogAlways( ... ) ;
#define _vwLogAlways( ... ) ;
// Post underscore version means no wchar (fwide) state changes //
#define LogWide( ... ) ;
#define wLogAlways_( ... ) ;
#define _wLogAlways_( ... ) ;
#define vwLogAlways_( ... ) ;
#define _vwLogAlways_( ... ) ;
// - ------------------------------------------------------------------------------------------ - //
#else // NO_LOGGING //
// - ------------------------------------------------------------------------------------------ - //
#define LogInit() ;
#define LogExit() ;
#define LogColor( ... ) ;

#define LogAlways( ... ) ;
#define _LogAlways( ... ) ;
#define vLogAlways( ... ) ;
#define _vLogAlways( ... ) ;

#define wLogAlways( ... ) ;
#define _wLogAlways( ... ) ;
#define vwLogAlways( ... ) ;
#define _vwLogAlways( ... ) ;

#define LogWide( ... ) ;
#define wLogAlways_( ... ) ;
#define _wLogAlways_( ... ) ;
#define vwLogAlways_( ... ) ;
#define _vwLogAlways_( ... ) ;

#define LogFlush() ;
// - ------------------------------------------------------------------------------------------ - //
#endif // NO_LOGGING //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Log family of calls - Should probably be a singe macro *shrug* //
// - ------------------------------------------------------------------------------------------ - //
#if (LOG_LEVEL >= 1) || !defined(LOG_LEVEL)
	#define Log( ... ) { if ( LogLevel >= 1 ) LogAlways( __VA_ARGS__ ); }
	#define _Log( ... ) { if ( LogLevel >= 1 ) _LogAlways( __VA_ARGS__ ); }
	#define return_Log( ... ) { Log( __VA_ARGS__ ); return; }
	#define return_value_Log( ___VAL, ... ) { Log( __VA_ARGS__ ); return ___VAL; }
	#define wLog( ... ) { if ( LogLevel >= 1 ) wLogAlways( __VA_ARGS__ ); }
	#define _wLog( ... ) { if ( LogLevel >= 1 ) _wLogAlways( __VA_ARGS__ ); }
	#define return_wLog( ... ) { wLog( __VA_ARGS__ ); return; }
	#define return_value_wLog( ___VAL, ... ) { wLog( __VA_ARGS__ ); return ___VAL; }
#else // LOG_LEVEL //
	#define Log( ... ) ;
	#define _Log( ... ) ;
	#define return_Log( ... ) {return;}
	#define return_value_Log( __VAL, ... ) {return __VAL;}
	#define wLog( ... ) ;
	#define _wLog( ... ) ;
	#define return_wLog( ... ) {return;}
	#define return_value_wLog( __VAL, ... ) {return __VAL;}
#endif // LOG_LEVEL //
// - ------------------------------------------------------------------------------------------ - //
#if (LOG_LEVEL >= 2) || !defined(LOG_LEVEL)
	#define VLog( ... ) { if ( LogLevel >= 2 ) LogAlways( __VA_ARGS__ ); }
	#define _VLog( ... ) { if ( LogLevel >= 2 ) _LogAlways( __VA_ARGS__ ); }
	#define return_VLog( ... ) { VLog( __VA_ARGS__ ); return; }
	#define return_value_VLog( ___VAL, ... ) { VLog( __VA_ARGS__ ); return ___VAL; }
	#define wVLog( ... ) { if ( LogLevel >= 2 ) wLogAlways( __VA_ARGS__ ); }
	#define _wVLog( ... ) { if ( LogLevel >= 2 ) _wLogAlways( __VA_ARGS__ ); }
	#define return_wVLog( ... ) { wVLog( __VA_ARGS__ ); return; }
	#define return_value_wVLog( ___VAL, ... ) { wVLog( __VA_ARGS__ ); return ___VAL; }
#else // LOG_LEVEL //
	#define VLog( ... ) ;
	#define _VLog( ... ) ;
	#define return_VLog( ... ) {return;}
	#define return_value_VLog( __VAL, ... ) {return __VAL;}
	#define wVLog( ... ) ;
	#define _wVLog( ... ) ;
	#define return_wVLog( ... ) {return;}
	#define return_value_wVLog( __VAL, ... ) {return __VAL;}
#endif // LOG_LEVEL //
// - ------------------------------------------------------------------------------------------ - //
#if (LOG_LEVEL >= 3) || !defined(LOG_LEVEL)
	#define VVLog( ... ) { if ( LogLevel >= 3 ) LogAlways( __VA_ARGS__ ); }
	#define _VVLog( ... ) { if ( LogLevel >= 3 ) _LogAlways( __VA_ARGS__ ); }
	#define return_VVLog( ... ) { VVLog( __VA_ARGS__ ); return; }
	#define return_value_VVLog( ___VAL, ... ) { VVLog( __VA_ARGS__ ); return ___VAL; }
	#define wVVLog( ... ) { if ( LogLevel >= 3 ) wLogAlways( __VA_ARGS__ ); }
	#define _wVVLog( ... ) { if ( LogLevel >= 3 ) _wLogAlways( __VA_ARGS__ ); }
	#define return_wVVLog( ... ) { wVVLog( __VA_ARGS__ ); return; }
	#define return_value_wVVLog( ___VAL, ... ) { wVVLog( __VA_ARGS__ ); return ___VAL; }
#else // LOG_LEVEL //
	#define VVLog( ... ) ;
	#define _VVLog( ... ) ;
	#define return_VVLog( ... ) {return;}
	#define return_value_VVLog( __VAL, ... ) {return __VAL;}
	#define wVVLog( ... ) ;
	#define _wVVLog( ... ) ;
	#define return_wVVLog( ... ) {return;}
	#define return_value_wVVLog( __VAL, ... ) {return __VAL;}
#endif // LOG_LEVEL //
// - ------------------------------------------------------------------------------------------ - //
#if (LOG_LEVEL >= 4) || !defined(LOG_LEVEL)
	#define VVVLog( ... ) { if ( LogLevel >= 4 ) LogAlways( __VA_ARGS__ ); }
	#define _VVVLog( ... ) { if ( LogLevel >= 4 ) _LogAlways( __VA_ARGS__ ); }
	#define return_VVVLog( ... ) { VVVLog( __VA_ARGS__ ); return; }
	#define return_value_VVVLog( ___VAL, ... ) { VVVLog( __VA_ARGS__ ); return ___VAL; }
	#define wVVVLog( ... ) { if ( LogLevel >= 4 ) wLogAlways( __VA_ARGS__ ); }
	#define _wVVVLog( ... ) { if ( LogLevel >= 4 ) _wLogAlways( __VA_ARGS__ ); }
	#define return_wVVVLog( ... ) { wVVVLog( __VA_ARGS__ ); return; }
	#define return_value_wVVVLog( ___VAL, ... ) { wVVVLog( __VA_ARGS__ ); return ___VAL; }
#else // LOG_LEVEL //
	#define VVVLog( ... ) ;
	#define _VVVLog( ... ) ;
	#define return_VVVLog( ... ) {return;}
	#define return_value_VVVLog( __VAL, ... ) {return __VAL;}
	#define wVVVLog( ... ) ;
	#define _wVVVLog( ... ) ;
	#define return_wVVVLog( ... ) {return;}
	#define return_value_wVVVLog( __VAL, ... ) {return __VAL;}
#endif // LOG_LEVEL //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Error Logging, like an assert for when we don't crash //
// - ------------------------------------------------------------------------------------------ - //
#ifdef NO_LOGGING
// - ------------------------------------------------------------------------------------------ - //
#ifdef _MSC_VER
// - ------------------------------------------------------------------------------------------ - //
#define ELog( ... ) \
{ _LogAlways( "** C++ ERROR ** LINE %i ** %s ** %s **\n", __LINE__, __FUNCTION__, __FILE__ ); LogAlways( __VA_ARGS__ ); }
#define wELog( ... ) \
{ \
	LogWide(true); \
	_wLogAlways_( L"** C++ ERROR ** LINE %i ** %s ** %s **\n", __LINE__, __FUNCTION__, __FILE__ ); \
	wLogAlways_( __VA_ARGS__ ); \
	LogWide(false); \
}
// - ------------------------------------------------------------------------------------------ - //
#else // _MSC_VER //
// - ------------------------------------------------------------------------------------------ - //
#define ELog( ... ) \
{ _LogAlways( "** C++ ERROR ** LINE %i ** %s ** %s **\n", __LINE__, __PRETTY_FUNCTION__, __FILE__ ); LogAlways( __VA_ARGS__ ); }
#define wELog( ... ) \
{ \
	LogWide(true); \
	_wLogAlways_( L"** C++ ERROR ** LINE %i ** %s ** %s **\n", __LINE__, __PRETTY_FUNCTION__, __FILE__ ); \
	wLogAlways_( __VA_ARGS__ ); \
	LogWide(false); \
}
// - ------------------------------------------------------------------------------------------ - //
#endif // _MSC_VER //
// - ------------------------------------------------------------------------------------------ - //
#else // NO_LOGGING //
// - ------------------------------------------------------------------------------------------ - //
#define ELog( ... ) ;
#define wELog( ... ) ;
// - ------------------------------------------------------------------------------------------ - //
#endif // NO_LOGGING //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Debug Build Only Logging //
// - ------------------------------------------------------------------------------------------ - //
#if !defined(NDEBUG) && !defined(NO_LOGGING)
// - ------------------------------------------------------------------------------------------ - //
#define DLog( ... ) { LogAlways( __VA_ARGS__ ); }
#define _DLog( ... ) { _LogAlways( __VA_ARGS__ ); }
#define wDLog( ... ) { wLogAlways( __VA_ARGS__ ); }
#define _wDLog( ... ) { _wLogAlways( __VA_ARGS__ ); }
// - ------------------------------------------------------------------------------------------ - //
#else // NDEBUG //
// - ------------------------------------------------------------------------------------------ - //
#define DLog( ... ) ;
#define _DLog( ... ) ;
#define wDLog( ... ) ;
#define _wDLog( ... ) ;
// - ------------------------------------------------------------------------------------------ - //
#endif // NDEBUG //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_DEBUG_Log_H__ //
// - ------------------------------------------------------------------------------------------ - //
