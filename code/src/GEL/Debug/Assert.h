// - ------------------------------------------------------------------------------------------ - //
// Assert //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_DEBUG_Assert_H__
#define __GEL_DEBUG_Assert_H__
// - ------------------------------------------------------------------------------------------ - //
#include <stdlib.h>
#include "Log.h"
// - ------------------------------------------------------------------------------------------ - //
#ifndef NDEBUG
// - ------------------------------------------------------------------------------------------ - //
// AssertFlush -- This is what does the actual exiting //
#define AssertFlush() \
	{ \
		extern bool _AssertFlush; \
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
			LogAlways( "   Line: %i  File: %s", __LINE__, __FILE__ ); \
			LogAlways( "   Func: %s", __PRETTY_FUNCTION__ ); \
			\
			extern bool _AssertFlush; \
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
#define __WarningText( ... ) \
	{ \
		LogAlways( "-========================================================-" ); \
		_LogAlways( "! Warning: " ); \
		LogAlways( __VA_ARGS__ ); \
		LogAlways( "   Line: %i  File: %s", __LINE__, __FILE__ ); \
		LogAlways( "   Func: %s\n", __PRETTY_FUNCTION__ ); \
	}
// - ------------------------------------------------------------------------------------------ - //
#define Warning( __TEST, ... ) { if ( __TEST ) { __WarningText( __VA_ARGS__ ); } }
#define return_Warning( __TEST, ... ) { if ( auto __ERROR = (__TEST) ) { __WarningText( __VA_ARGS__ ); return __ERROR; } }
#define return_void_Warning( __TEST, ... ) { if ( __TEST ) { __WarningText( __VA_ARGS__ ); return; } }
#define return_value_Warning( __RETCODE, __TEST, ... ) { if ( __TEST ) { __WarningText( __VA_ARGS__ ); return __RETCODE; } }

#define if_Warning( __TEST, ... ) { if ( __TEST ) { __WarningText( __VA_ARGS__ ); } }
#define return_if_Warning( __TEST, ... ) { if ( auto __ERROR = (__TEST) ) { __WarningText( __VA_ARGS__ ); return __ERROR; } }
#define return_if_void_Warning( __TEST, ... ) { if ( __TEST ) { __WarningText( __VA_ARGS__ ); return; } }
#define return_if_value_Warning( __RETCODE, __TEST, ... ) { if ( __TEST ) { __WarningText( __VA_ARGS__ ); return __RETCODE; } }
// - ------------------------------------------------------------------------------------------ - //
#else // NDEBUG //
// - ------------------------------------------------------------------------------------------ - //
#define Assert( ... ) ;
#define _Assert( ... ) ;
#define AssertFlush( ... ) ;

#define Warning( ... ) ;
#define return_Warning( __TEST, ... ) { if ( auto __ERROR = (__TEST) ) { return __ERROR; } }
#define return_void_Warning( __TEST, ... ) { if ( __TEST ) { return; } }
#define return_value_Warning( __RETCODE, __TEST, ... ) { if ( __TEST ) { return __RETCODE; } }

#define if_Warning( ... ) ;
#define return_if_Warning( __TEST, ... ) { if ( auto __ERROR = (__TEST) ) { return __ERROR; } }
#define return_if_void_Warning( __TEST, ... ) { if ( __TEST ) { return; } }
#define return_if_value_Warning( __RETCODE, __TEST, ... ) { if ( __TEST ) { return __RETCODE; } }
// - ------------------------------------------------------------------------------------------ - //
#endif // NDEBUG //
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_DEBUG_Assert_H__ //
// - ------------------------------------------------------------------------------------------ - //
