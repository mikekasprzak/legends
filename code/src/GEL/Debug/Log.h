// - ------------------------------------------------------------------------------------------ - //
// Logging //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_DEBUG_Log_H__
#define __GEL_DEBUG_Log_H__
// - ------------------------------------------------------------------------------------------ - //
#ifndef NOLOGGING
// - ------------------------------------------------------------------------------------------ - //
// * LogAlways *always* writes to the log.
// * DLog writes only in the debug build.
// * Log are only written when the Logging level is 1 or higher (default).
// * VLog are only written when the Logging level is 2 or higher.
// * VVLog are only written when the Logging level is 3 or higher.
// * VVVLog are only written when the Logging level is 4 or higher.
// * ELog does Error Logging - Print some extended debuging information.
// * wLogAlways, wDLog, wVLog, wELog are the w_char versions of Log.
// * _LogAlways, _DLog, _VLog don't append a newline (\n) and don't flush.
// - ------------------------------------------------------------------------------------------ - //
extern int LogLevel;
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Log Setup //
void LogInit();
void LogExit();

void LogFlush();

// The "Forcefully Always Log" version // 
void LogAlways( const char* s, ... );
void _LogAlways( const char* s, ... );
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#define Log( ... ) { if ( LogLevel >= 1 ) LogAlways( __VA_ARGS__ ); }
#define _Log( ... ) { if ( LogLevel >= 1 ) _LogAlways( __VA_ARGS__ ); }
#define return_Log( ... ) { Log( __VA_ARGS__ ); return; }
#define return_value_Log( ___VAL, ... ) { Log( __VA_ARGS__ ); return ___VAL; }

#define VLog( ... ) { if ( LogLevel >= 2 ) LogAlways( __VA_ARGS__ ); }
#define _VLog( ... ) { if ( LogLevel >= 2 ) _LogAlways( __VA_ARGS__ ); }
#define return_VLog( ... ) { VLog( __VA_ARGS__ ); return; }
#define return_value_VLog( ___VAL, ... ) { VLog( __VA_ARGS__ ); return ___VAL; }

#define VVLog( ... ) { if ( LogLevel >= 3 ) LogAlways( __VA_ARGS__ ); }
#define _VVLog( ... ) { if ( LogLevel >= 3 ) _LogAlways( __VA_ARGS__ ); }
#define return_VVLog( ... ) { VVLog( __VA_ARGS__ ); return; }
#define return_value_VVLog( ___VAL, ... ) { VVLog( __VA_ARGS__ ); return ___VAL; }

#define VVVLog( ... ) { if ( LogLevel >= 4 ) LogAlways( __VA_ARGS__ ); }
#define _VVVLog( ... ) { if ( LogLevel >= 4 ) _LogAlways( __VA_ARGS__ ); }
#define return_VVVLog( ... ) { VVVLog( __VA_ARGS__ ); return; }
#define return_value_VVVLog( ___VAL, ... ) { VVVLog( __VA_ARGS__ ); return ___VAL; }
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Error Logging, like an assert for when we don't crash //
// - ------------------------------------------------------------------------------------------ - //
#ifdef _MSC_VER
// - ------------------------------------------------------------------------------------------ - //
#define NO_ANSI_COLOR_CODES

#define ELog( ... ) \
{ LogAlways( "** C++ ERROR ** LINE %i ** %s ** %s ** ", __LINE__, __FUNCTION__, __FILE__ ); LogAlways( __VA_ARGS__ ); }
//#define wELog( ... ) \
//{ LogAlways( "** C++ ERROR ** LINE %i ** %s ** %s ** ", __LINE__, __FUNCTION__, __FILE__ ); wLogAlways( __VA_ARGS__ ); }
// - ------------------------------------------------------------------------------------------ - //
#else // _MSC_VER //
// - ------------------------------------------------------------------------------------------ - //
#define ELog( ... ) \
{ LogAlways( "** C++ ERROR ** LINE %i ** %s ** %s ** ", __LINE__, __PRETTY_FUNCTION__, __FILE__ ); LogAlways( __VA_ARGS__ ); }
//#define wELog( ... ) \
//{ LogAlways( "** C++ ERROR ** LINE %i ** %s ** %s ** ", __LINE__, __PRETTY_FUNCTION__, __FILE__ ); wLogAlways( __VA_ARGS__ ); }
// - ------------------------------------------------------------------------------------------ - //
#endif // _MSC_VER //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Debug Build Only Logging //
// - ------------------------------------------------------------------------------------------ - //
#ifndef NDEBUG
// - ------------------------------------------------------------------------------------------ - //
#define DLog( ... ) { LogAlways( __VA_ARGS__ ); }
#define _DLog( ... ) { _LogAlways( __VA_ARGS__ ); }
//#define wDLog( ... ) { wLogAlways( __VA_ARGS__ ); }
//#define _wDLog( ... ) { _wLogAlways( __VA_ARGS__ ); }
// - ------------------------------------------------------------------------------------------ - //
#else // NDEBUG //
// - ------------------------------------------------------------------------------------------ - //
#define DLog( ... ) ;
#define _DLog( ... ) ;
//#define wDLog( ... ) ;
//#define _wDLog( ... ) ;
// - ------------------------------------------------------------------------------------------ - //
#endif // NDEBUG //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#ifndef NO_ANSI_COLOR_CODES
// - ------------------------------------------------------------------------------------------ - //
	#define ANSI_HEADER					"\033["

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
// - ------------------------------------------------------------------------------------------ - //
#else // NO_ANSI_COLOR_CODES //
// - ------------------------------------------------------------------------------------------ - //
	#define ANSI_HEADER					""

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
// - ------------------------------------------------------------------------------------------ - //
#endif // NO_ANSI_COLOR_CODES //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#else // NOLOGGING //
// - ------------------------------------------------------------------------------------------ - //

#define LogInit() ;
#define LogExit() ;

#define LogFlush() ;

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

#define return_Log( ... ) {return;}
#define return_VLog( ... ) {return;}
#define return_VVLog( ... ) {return;}
#define return_VVVLog( ... ) {return;}
#define return_value_Log( __VAL, ... ) {return __VAL;}
#define return_value_VLog( __VAL, ... ) {return __VAL;}
#define return_value_VVLog( __VAL, ... ) {return __VAL;}
#define return_value_VVVLog( __VAL, ... ) {return __VAL;}

// - ------------------------------------------------------------------------------------------ - //
#endif // NOLOGGING //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_DEBUG_Log_H__ //
// - ------------------------------------------------------------------------------------------ - //
