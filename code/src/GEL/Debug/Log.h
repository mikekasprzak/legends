// - ------------------------------------------------------------------------------------------ - //
// Logging //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_DEBUG_Log_H__
#define __GEL_DEBUG_Log_H__
// - ------------------------------------------------------------------------------------------ - //
#include <stdarg.h>	// For va_list
#include <stdlib.h>	// For exit(1);
#include <Util/return_if.h>
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
// * wLogAlways, wDLog, wVLog, wELog are the w_char versions of Log.
// * _LogAlways, _DLog, _VLog *DON'T* append a newline (\n) and *DON'T* flush.
// - ------------------------------------------------------------------------------------------ - //
// Use LOG_LEVEL to force a current and maximum log level (i.e. removes other calls) //
extern int LogLevel;
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#ifdef _MSC_VER
	#define __PRETTY_FUNCTION__ __FUNCTION__
#endif // _MSC_VER //
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
void LogInit( const char* TargetFile = 0 );
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

// Get access to the Data stored in the Memory Log //
extern const char* GetMLogData();

// Disabled (for now). Will need to call fwide(+1) before and fwide(-1) after each call. Also <wchar.h> //
//   These calls can afford to be wasteful, since they're mainly for logging wchar data. I will never //
//   ever actually localize the logging, so in practice wchar's are not needed by my logging code. //
#define wLogAlways( ... ) ;
#define _wLogAlways( ... ) ;
#define vwLogAlways( ... ) ;
#define _vwLogAlways( ... ) ;
// Post underscore version means no wchar (fwide) state changes //
#define LogWide( ... ) ; // true = fwide(+1), false = fwide(-1)
#define wLogAlways_( ... ) ;
#define _wLogAlways_( ... ) ;
#define vwLogAlways_( ... ) ;
#define _vwLogAlways_( ... ) ;
// - ------------------------------------------------------------------------------------------ - //
#else // NO_LOGGING //
// - ------------------------------------------------------------------------------------------ - //
#define LogInit( ... ) ;
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
// Log family of calls - Should probably be a singe macro *shrug* - EDIT: Can't be. No nested Macros. //
// - ------------------------------------------------------------------------------------------ - //
#if (LOG_LEVEL >= 1) || !defined(LOG_LEVEL)
	#define Log( ... ) { if ( LogLevel >= 1 ) LogAlways( __VA_ARGS__ ); }
	#define _Log( ... ) { if ( LogLevel >= 1 ) _LogAlways( __VA_ARGS__ ); }
	#define if_Log( __TEST, ... ) { if ( __TEST ) { Log( __VA_ARGS__ ); } }
	#define return_Log( __RETCODE, ... ) { Log( __VA_ARGS__ ); return __RETCODE; }
	#define return_void_Log( ... ) { Log( __VA_ARGS__ ); return; }
	#define return_value_Log( __RETCODE, ... ) { Log( __VA_ARGS__ ); return __RETCODE; }
	#define return_if_Log( __TEST, ... ) { if( auto __Error ## __COUNTER__ = (__TEST) ) { Log( __VA_ARGS__ ); return __Error ## __COUNTER__; } }
	#define return_if_void_Log( __TEST, ... ) { if( __TEST ) { Log( __VA_ARGS__ ); return; } }
	#define return_if_value_Log( __RETCODE, __TEST, ... ) { if( __TEST ) { Log( __VA_ARGS__ ); return __RETCODE; } }
	#define wLog( ... ) { if ( LogLevel >= 1 ) wLogAlways( __VA_ARGS__ ); }
	#define _wLog( ... ) { if ( LogLevel >= 1 ) _wLogAlways( __VA_ARGS__ ); }
	#define if_wLog( __TEST, ... ) { if ( __TEST ) { Log( __VA_ARGS__ ); } }
	#define return_wLog( __RETCODE, ... ) { wLog( __VA_ARGS__ ); return __RETCODE; }
	#define return_void_wLog( ... ) { wLog( __VA_ARGS__ ); return; }
	#define return_value_wLog( __RETCODE, ... ) { wLog( __VA_ARGS__ ); return __RETCODE; }
	#define return_if_wLog( __TEST, ... ) { if( auto __Error ## __COUNTER__ = (__TEST) ) { wLog( __VA_ARGS__ ); return __Error ## __COUNTER__; } }
	#define return_if_void_wLog( __TEST, ... ) { if( __TEST ) { wLog( __VA_ARGS__ ); return; } }
	#define return_if_value_wLog( __RETCODE, __TEST, ... ) { if( __TEST ) { wLog( __VA_ARGS__ ); return __RETCODE; } }
#else // LOG_LEVEL //
	#define Log( ... ) ;
	#define _Log( ... ) ;
	#define if_Log( ... ) ;
	#define return_Log( __RETCODE, ... ) { return __RETCODE; }
	#define return_void_Log( ... ) { return; }
	#define return_value_Log( __RETCODE, ... ) { return __RETCODE; }
	#define return_if_Log( __TEST, ... ) { if ( auto __Error ## __COUNTER__ = (__TEST) ) { return __Error ## __COUNTER__; } }
	#define return_if_void_Log( __TEST, ... ) { if ( __TEST ) { return; } }
	#define return_if_value_Log( __RETCODE, __TEST, ... ) { if ( __TEST ) { return __RETCODE; } }
	#define wLog( ... ) ;
	#define _wLog( ... ) ;
	#define if_wLog( ... ) ;
	#define return_wLog( __RETCODE, ... ) { return __RETCODE; }
	#define return_void_wLog( ... ) { return; }
	#define return_value_wLog( __RETCODE, ... ) { return __RETCODE; }
	#define return_if_wLog( __TEST, ... ) { if ( auto __Error ## __COUNTER__ = (__TEST) ) { return __Error ## __COUNTER__; } }
	#define return_if_void_wLog( __TEST, ... ) { if ( __TEST ) { return; } }
	#define return_if_value_wLog( __RETCODE, __TEST, ... ) { if ( __TEST ) { return __RETCODE; } }
#endif // LOG_LEVEL //
// - ------------------------------------------------------------------------------------------ - //
#if (LOG_LEVEL >= 2) || !defined(LOG_LEVEL)
	#define VLog( ... ) { if ( LogLevel >= 2 ) LogAlways( __VA_ARGS__ ); }
	#define _VLog( ... ) { if ( LogLevel >= 2 ) _LogAlways( __VA_ARGS__ ); }
	#define if_VLog( __TEST, ... ) { if ( __TEST ) { VLog( __VA_ARGS__ ); } }
	#define return_VLog( __RETCODE, ... ) { VLog( __VA_ARGS__ ); return __RETCODE; }
	#define return_void_VLog( ... ) { VLog( __VA_ARGS__ ); return; }
	#define return_value_VLog( __RETCODE, ... ) { VLog( __VA_ARGS__ ); return __RETCODE; }
	#define return_if_VLog( __TEST, ... ) { if( auto __Error ## __COUNTER__ = (__TEST) ) { VLog( __VA_ARGS__ ); return __Error ## __COUNTER__; } }
	#define return_if_void_VLog( __TEST, ... ) { if( __TEST ) { VLog( __VA_ARGS__ ); return; } }
	#define return_if_value_VLog( __RETCODE, __TEST, ... ) { if( __TEST ) { VLog( __VA_ARGS__ ); return __RETCODE; } }
	#define wVLog( ... ) { if ( LogLevel >= 2 ) wLogAlways( __VA_ARGS__ ); }
	#define _wVLog( ... ) { if ( LogLevel >= 2 ) _wLogAlways( __VA_ARGS__ ); }
	#define if_wVLog( __TEST, ... ) { if ( __TEST ) { VLog( __VA_ARGS__ ); } }
	#define return_wVLog( __RETCODE, ... ) { wVLog( __VA_ARGS__ ); return __RETCODE; }
	#define return_void_wVLog( ... ) { wVLog( __VA_ARGS__ ); return; }
	#define return_value_wVLog( __RETCODE, ... ) { wVLog( __VA_ARGS__ ); return __RETCODE; }
	#define return_if_wVLog( __TEST, ... ) { if( auto __Error ## __COUNTER__ = (__TEST) ) { wVLog( __VA_ARGS__ ); return __Error ## __COUNTER__; } }
	#define return_if_void_wVLog( __TEST, ... ) { if( __TEST ) { wVLog( __VA_ARGS__ ); return; } }
	#define return_if_value_wVLog( __RETCODE, __TEST, ... ) { if( __TEST ) { wVLog( __VA_ARGS__ ); return __RETCODE; } }
#else // VLog_LEVEL //
	#define VLog( ... ) ;
	#define _VLog( ... ) ;
	#define if_VLog( ... ) ;
	#define return_VLog( __RETCODE, ... ) { return __RETCODE; }
	#define return_void_VLog( ... ) { return; }
	#define return_value_VLog( __RETCODE, ... ) { return __RETCODE; }
	#define return_if_VLog( __TEST, ... ) { if ( auto __Error ## __COUNTER__ = (__TEST) ) { return __Error ## __COUNTER__; } }
	#define return_if_void_VLog( __TEST, ... ) { if ( __TEST ) { return; } }
	#define return_if_value_VLog( __RETCODE, __TEST, ... ) { if ( __TEST ) { return __RETCODE; } }
	#define wVLog( ... ) ;
	#define _wVLog( ... ) ;
	#define if_wVLog( ... ) ;
	#define return_wVLog( __RETCODE, ... ) { return __RETCODE; }
	#define return_void_wVLog( ... ) { return; }
	#define return_value_wVLog( __RETCODE, ... ) { return __RETCODE; }
	#define return_if_wVLog( __TEST, ... ) { if ( auto __Error ## __COUNTER__ = (__TEST) ) { return __Error ## __COUNTER__; } }
	#define return_if_void_wVLog( __TEST, ... ) { if ( __TEST ) { return; } }
	#define return_if_value_wVLog( __RETCODE, __TEST, ... ) { if ( __TEST ) { return __RETCODE; } }
#endif // LOG_LEVEL //
// - ------------------------------------------------------------------------------------------ - //
#if (LOG_LEVEL >= 3) || !defined(LOG_LEVEL)
	#define VVLog( ... ) { if ( LogLevel >= 3 ) LogAlways( __VA_ARGS__ ); }
	#define _VVLog( ... ) { if ( LogLevel >= 3 ) _LogAlways( __VA_ARGS__ ); }
	#define if_VVLog( __TEST, ... ) { if ( __TEST ) { VVLog( __VA_ARGS__ ); } }
	#define return_VVLog( __RETCODE, ... ) { VVLog( __VA_ARGS__ ); return __RETCODE; }
	#define return_void_VVLog( ... ) { VVLog( __VA_ARGS__ ); return; }
	#define return_value_VVLog( __RETCODE, ... ) { VVLog( __VA_ARGS__ ); return __RETCODE; }
	#define return_if_VVLog( __TEST, ... ) { if( auto __Error ## __COUNTER__ = (__TEST) ) { VVLog( __VA_ARGS__ ); return __Error ## __COUNTER__; } }
	#define return_if_void_VVLog( __TEST, ... ) { if( __TEST ) { VVLog( __VA_ARGS__ ); return; } }
	#define return_if_value_VVLog( __RETCODE, __TEST, ... ) { if( __TEST ) { VVLog( __VA_ARGS__ ); return __RETCODE; } }
	#define wVVLog( ... ) { if ( LogLevel >= 3 ) wLogAlways( __VA_ARGS__ ); }
	#define _wVVLog( ... ) { if ( LogLevel >= 3 ) _wLogAlways( __VA_ARGS__ ); }
	#define if_wVVLog( __TEST, ... ) { if ( __TEST ) { VVLog( __VA_ARGS__ ); } }
	#define return_wVVLog( __RETCODE, ... ) { wVVLog( __VA_ARGS__ ); return __RETCODE; }
	#define return_void_wVVLog( ... ) { wVVLog( __VA_ARGS__ ); return; }
	#define return_value_wVVLog( __RETCODE, ... ) { wVVLog( __VA_ARGS__ ); return __RETCODE; }
	#define return_if_wVVLog( __TEST, ... ) { if( auto __Error ## __COUNTER__ = (__TEST) ) { wVVLog( __VA_ARGS__ ); return __Error ## __COUNTER__; } }
	#define return_if_void_wVVLog( __TEST, ... ) { if( __TEST ) { wVVLog( __VA_ARGS__ ); return; } }
	#define return_if_value_wVVLog( __RETCODE, __TEST, ... ) { if( __TEST ) { wVVLog( __VA_ARGS__ ); return __RETCODE; } }
#else // VVLog_LEVEL //
	#define VVLog( ... ) ;
	#define _VVLog( ... ) ;
	#define if_VVLog( ... ) ;
	#define return_VVLog( __RETCODE, ... ) { return __RETCODE; }
	#define return_void_VVLog( ... ) { return; }
	#define return_value_VVLog( __RETCODE, ... ) { return __RETCODE; }
	#define return_if_VVLog( __TEST, ... ) { if ( auto __Error ## __COUNTER__ = (__TEST) ) { return __Error ## __COUNTER__; } }
	#define return_if_void_VVLog( __TEST, ... ) { if ( __TEST ) { return; } }
	#define return_if_value_VVLog( __RETCODE, __TEST, ... ) { if ( __TEST ) { return __RETCODE; } }
	#define wVVLog( ... ) ;
	#define _wVVLog( ... ) ;
	#define if_wVVLog( ... ) ;
	#define return_wVVLog( __RETCODE, ... ) { return __RETCODE; }
	#define return_void_wVVLog( ... ) { return; }
	#define return_value_wVVLog( __RETCODE, ... ) { return __RETCODE; }
	#define return_if_wVVLog( __TEST, ... ) { if ( auto __Error ## __COUNTER__ = (__TEST) ) { return __Error ## __COUNTER__; } }
	#define return_if_void_wVVLog( __TEST, ... ) { if ( __TEST ) { return; } }
	#define return_if_value_wVVLog( __RETCODE, __TEST, ... ) { if ( __TEST ) { return __RETCODE; } }
#endif // LOG_LEVEL //
// - ------------------------------------------------------------------------------------------ - //
#if (LOG_LEVEL >= 4) || !defined(LOG_LEVEL)
	#define VVVLog( ... ) { if ( LogLevel >= 4 ) LogAlways( __VA_ARGS__ ); }
	#define _VVVLog( ... ) { if ( LogLevel >= 4 ) _LogAlways( __VA_ARGS__ ); }
	#define if_VVVLog( __TEST, ... ) { if ( __TEST ) { VVVLog( __VA_ARGS__ ); } }
	#define return_VVVLog( __RETCODE, ... ) { VVVLog( __VA_ARGS__ ); return __RETCODE; }
	#define return_void_VVVLog( ... ) { VVVLog( __VA_ARGS__ ); return; }
	#define return_value_VVVLog( __RETCODE, ... ) { VVVLog( __VA_ARGS__ ); return __RETCODE; }
	#define return_if_VVVLog( __TEST, ... ) { if( auto __Error ## __COUNTER__ = (__TEST) ) { VVVLog( __VA_ARGS__ ); return __Error ## __COUNTER__; } }
	#define return_if_void_VVVLog( __TEST, ... ) { if( __TEST ) { VVVLog( __VA_ARGS__ ); return; } }
	#define return_if_value_VVVLog( __RETCODE, __TEST, ... ) { if( __TEST ) { VVVLog( __VA_ARGS__ ); return __RETCODE; } }
	#define wVVVLog( ... ) { if ( LogLevel >= 4 ) wLogAlways( __VA_ARGS__ ); }
	#define _wVVVLog( ... ) { if ( LogLevel >= 4 ) _wLogAlways( __VA_ARGS__ ); }
	#define if_wVVVLog( __TEST, ... ) { if ( __TEST ) { VVVLog( __VA_ARGS__ ); } }
	#define return_wVVVLog( __RETCODE, ... ) { wVVVLog( __VA_ARGS__ ); return __RETCODE; }
	#define return_void_wVVVLog( ... ) { wVVVLog( __VA_ARGS__ ); return; }
	#define return_value_wVVVLog( __RETCODE, ... ) { wVVVLog( __VA_ARGS__ ); return __RETCODE; }
	#define return_if_wVVVLog( __TEST, ... ) { if( auto __Error ## __COUNTER__ = (__TEST) ) { wVVVLog( __VA_ARGS__ ); return __Error ## __COUNTER__; } }
	#define return_if_void_wVVVLog( __TEST, ... ) { if( __TEST ) { wVVVLog( __VA_ARGS__ ); return; } }
	#define return_if_value_wVVVLog( __RETCODE, __TEST, ... ) { if( __TEST ) { wVVVLog( __VA_ARGS__ ); return __RETCODE; } }
#else // VVVLog_LEVEL //
	#define VVVLog( ... ) ;
	#define _VVVLog( ... ) ;
	#define if_VVVLog( ... ) ;
	#define return_VVVLog( __RETCODE, ... ) { return __RETCODE; }
	#define return_void_VVVLog( ... ) { return; }
	#define return_value_VVVLog( __RETCODE, ... ) { return __RETCODE; }
	#define return_if_VVVLog( __TEST, ... ) { if ( auto __Error ## __COUNTER__ = (__TEST) ) { return __Error ## __COUNTER__; } }
	#define return_if_void_VVVLog( __TEST, ... ) { if ( __TEST ) { return; } }
	#define return_if_value_VVVLog( __RETCODE, __TEST, ... ) { if ( __TEST ) { return __RETCODE; } }
	#define wVVVLog( ... ) ;
	#define _wVVVLog( ... ) ;
	#define if_wVVVLog( ... ) ;
	#define return_wVVVLog( __RETCODE, ... ) { return __RETCODE; }
	#define return_void_wVVVLog( ... ) { return; }
	#define return_value_wVVVLog( __RETCODE, ... ) { return __RETCODE; }
	#define return_if_wVVVLog( __TEST, ... ) { if ( auto __Error ## __COUNTER__ = (__TEST) ) { return __Error ## __COUNTER__; } }
	#define return_if_void_wVVVLog( __TEST, ... ) { if ( __TEST ) { return; } }
	#define return_if_value_wVVVLog( __RETCODE, __TEST, ... ) { if ( __TEST ) { return __RETCODE; } }
#endif // LOG_LEVEL //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Error Logging, like an assert for when we don't crash //
// TODO: Modify this to be MessageBox style alert, as suggested in the style guide.
// - ------------------------------------------------------------------------------------------ - //
#ifdef NO_LOGGING
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
#else // NO_LOGGING //
// - ------------------------------------------------------------------------------------------ - //
#define ELog( ... ) ;
#define wELog( ... ) ;
// - ------------------------------------------------------------------------------------------ - //
#endif // NO_LOGGING //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Debug Build Only //
// - ------------------------------------------------------------------------------------------ - //
#if !defined(NDEBUG) && !defined(NO_LOGGING)
// - ------------------------------------------------------------------------------------------ - //
#define DLog( ... ) { LogAlways( __VA_ARGS__ ); }
#define _DLog( ... ) { _LogAlways( __VA_ARGS__ ); }
#define wDLog( ... ) { wLogAlways( __VA_ARGS__ ); }
#define _wDLog( ... ) { _wLogAlways( __VA_ARGS__ ); }
// - ------------------------------------------------------------------------------------------ - //
extern bool _AssertFlush;
// - ------------------------------------------------------------------------------------------ - //
// AssertFlush -- This is what does the actual exiting //
#define AssertFlush() \
	{ \
		if ( _AssertFlush ) { \
			::exit(1); \
		} \
	}
// - ------------------------------------------------------------------------------------------ - //
// Assert without Flush -- On success, tell the user the program is in terrible shape //
#define _Assert( __TEST, ... ) \
	{ \
		if ( __TEST ) { \
			LogAlways( "-========================================================-" ); \
			_LogAlways( "! Assert Error: " ); \
			LogAlways( __VA_ARGS__ ); \
			LogAlways( "   Condition: " #__TEST ); \
			LogAlways( "   Line: %i  File: %s", __LINE__, __FILE__ ); \
			LogAlways( "   Func: %s", __PRETTY_FUNCTION__ ); \
			\
			_AssertFlush = true; \
		} \
	}
// - ------------------------------------------------------------------------------------------ - //
// Assert -- On success, Tell the user the program is in terrible shape, then exit //
#define Assert( __TEST, ... ) \
	{ \
		_Assert( __TEST, __VA_ARGS__ ); \
		AssertFlush(); \
	}

// - ------------------------------------------------------------------------------------------ - //
// Just the Warning text. Do not use! //
#define __WarningText( __TEST, ... ) \
	{ \
		LogAlways( "-========================================================-" ); \
		_LogAlways( "! Warning: " ); \
		LogAlways( __VA_ARGS__ ); \
		LogAlways( "   Condition: " #__TEST ); \
		LogAlways( "   Line: %i  File: %s", __LINE__, __FILE__ ); \
		LogAlways( "   Func: %s\n", __PRETTY_FUNCTION__ ); \
	}
// - ------------------------------------------------------------------------------------------ - //
#define Warning( __TEST, ... ) { if ( __TEST ) { __WarningText( __TEST, __VA_ARGS__ ); } }
#define return_Warning( __TEST, ... ) { if ( auto __ERROR = (__TEST) ) { __WarningText( __TEST, __VA_ARGS__ ); return __ERROR; } }
#define return_void_Warning( __TEST, ... ) { if ( __TEST ) { __WarningText( __TEST, __VA_ARGS__ ); return; } }
#define return_value_Warning( __RETCODE, __TEST, ... ) { if ( __TEST ) { __WarningText( __TEST, __VA_ARGS__ ); return __RETCODE; } }

#define if_Warning( __TEST, ... ) { if ( __TEST ) { __WarningText( __TEST, __VA_ARGS__ ); } }
#define return_if_Warning( __TEST, ... ) { if ( auto __ERROR = (__TEST) ) { __WarningText( __TEST, __VA_ARGS__ ); return __ERROR; } }
#define return_if_void_Warning( __TEST, ... ) { if ( __TEST ) { __WarningText( __TEST, __VA_ARGS__ ); return; } }
#define return_if_value_Warning( __RETCODE, __TEST, ... ) { if ( __TEST ) { __WarningText( __TEST, __VA_ARGS__ ); return __RETCODE; } }
// - ------------------------------------------------------------------------------------------ - //
#else // NDEBUG //
// - ------------------------------------------------------------------------------------------ - //
#define DLog( ... ) ;
#define _DLog( ... ) ;
#define wDLog( ... ) ;
#define _wDLog( ... ) ;

#define Assert( ... ) ;
#define _Assert( ... ) ;
#define AssertFlush() ;

#define Warning( ... ) ;
#define return_Warning( __TEST, ... ) { if ( auto __ERROR = (__TEST) ) { return __ERROR; } }
#define return_void_Warning( __TEST, ... ) { if ( __TEST ) { return; } }
#define return_value_Warning( __RETCODE, __TEST, ... ) { if ( __TEST ) { return __RETCODE; } }

// For Syntax Compatibility //
#define if_Warning( ... ) ;
#define return_if_Warning( __TEST, ... ) { if ( auto __ERROR = (__TEST) ) { return __ERROR; } }
#define return_if_void_Warning( __TEST, ... ) { if ( __TEST ) { return; } }
#define return_if_value_Warning( __RETCODE, __TEST, ... ) { if ( __TEST ) { return __RETCODE; } }
// - ------------------------------------------------------------------------------------------ - //
#endif // NDEBUG //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_DEBUG_Log_H__ //
// - ------------------------------------------------------------------------------------------ - //
