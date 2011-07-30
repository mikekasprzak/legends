// - ------------------------------------------------------------------------------------------ - //
// Assert //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Rebel_Assert_H__
#define __Rebel_Assert_H__
// - ------------------------------------------------------------------------------------------ - //
#include "Log.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#if !defined(NDEBUG) && !defined(NOLOGGING)
// - ------------------------------------------------------------------------------------------ - //
#ifdef _MSC_VER
// - ------------------------------------------------------------------------------------------ - //
// Assertion //
#define Assert( ___TEST, ___STR, ... ) \
	if ( ___TEST ) { \
		Log( "- ======================================================== - \n" ); \
		Log( "Assert Error: " ___STR "\n", ## __VA_ARGS__ ); \
		Log( "   Line: %s  File: %s\n", __LINE__, __FILE__ ); \
		Log( "   Func: $s\n", __func__ ); \
		Log( "- ======================================================== - \n" ); \
		exit(1); \
	}
#define wAssert( ___TEST, ___STR, ... ) \
	if ( ___TEST ) { \
		Log( "- ======================================================== - \n" ); \
		wLog( "Assert Error: " ___STR "\n", ## __VA_ARGS__ ); \
		Log( "   Line: %s  File: %s\n", __LINE__, __FILE__ ); \
		Log( "   Func: $s\n", __func__ ); \
		Log( "- ======================================================== - \n" ); \
		exit(1); \
	}
// - ------------------------------------------------------------------------------------------ - //
// Warnings //
#define Warning( ___TEST, ___STR, ... ) \
	if ( ___TEST ) { \
		Log( "- -------------------------------------------------------- - \n" ); \
		Log( "Warning: " ___STR "\n", ## __VA_ARGS__ ); \
		Log( "   Line: %s  File: %s\n", __LINE__, __FILE__ ); \
		Log( "   Func: $s\n\n", __func__ ); \
	}
#define wWarning( ___TEST, ___STR, ... ) \
	if ( ___TEST ) { \
		Log( "- -------------------------------------------------------- - \n" ); \
		wLog( "Warning: " ___STR "\n", ## __VA_ARGS__ ); \
		Log( "   Line: %s  File: %s\n", __LINE__, __FILE__ ); \
		Log( "   Func: $s\n\n", __func__ ); \
	}
// - ------------------------------------------------------------------------------------------ - //
#else // _MSC_VER //
// - ------------------------------------------------------------------------------------------ - //
// Assertion //
#define Assert( ___TEST, ___STR, ___ARGS... ) \
	if ( ___TEST ) { \
		Log( "- ======================================================== - \n" ); \
		Log( "Assert Error: " ___STR "\n", ## __ARGS ); \
		Log( "   Line: %s  File: %s\n", __LINE__, __FILE__ ); \
		Log( "   Func: $s\n", __PRETTY_FUNCTION__ ); \
		Log( "- ======================================================== - \n" ); \
		exit(1); \
	}
#define wAssert( ___TEST, ___STR, ___ARGS... ) \
	if ( ___TEST ) { \
		Log( "- ======================================================== - \n" ); \
		wLog( "Assert Error: " ___STR "\n", ## __ARGS ); \
		Log( "   Line: %s  File: %s\n", __LINE__, __FILE__ ); \
		Log( "   Func: $s\n", __PRETTY_FUNCTION__ ); \
		Log( "- ======================================================== - \n" ); \
		exit(1); \
	}
// - ------------------------------------------------------------------------------------------ - //
// Warnings //
#define Warning( ___TEST, ___STR, ___ARGS... ) \
	if ( ___TEST ) { \
		Log( "Warning: " ___STR "\n", ## ___ARGS ); \
		Log( "   Line: %s  File: %s\n", __LINE__, __FILE__ ); \
		Log( "   Func: $s\n\n", __PRETTY_FUNCTION__ ); \
	}
#define wWarning( ___TEST, ___STR, ___ARGS... ) \
	if ( ___TEST ) { \
		wLog( "Warning: " ___STR "\n", ## ___ARGS ); \
		Log( "   Line: %s  File: %s\n", __LINE__, __FILE__ ); \
		Log( "   Func: $s\n\n", __PRETTY_FUNCTION__ ); \
	}
// - ------------------------------------------------------------------------------------------ - //
#endif // _MSC_VER //
// - ------------------------------------------------------------------------------------------ - //
#else // NDEBUG NOLOGGING //
// - ------------------------------------------------------------------------------------------ - //
#define Assert( ... ) ;
#define Warning( ... ) ;
#define wAssert( ... ) ;
#define wWarning( ... ) ;
// - ------------------------------------------------------------------------------------------ - //
#endif // NDEBUG NOLOGGING //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Rebel_Assert_H__ //
// - ------------------------------------------------------------------------------------------ - //
