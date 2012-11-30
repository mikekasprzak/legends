// - ------------------------------------------------------------------------------------------ - //
// A set of macros that combine the concept of testing and returning //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_UTIL_RETURN_IF_H__
#define __GEL_UTIL_RETURN_IF_H__
// - ------------------------------------------------------------------------------------------ - //
//typedef const int __return_if_error_type;	// Assuming the standard error type is a signed integer //
// - ------------------------------------------------------------------------------------------ - //
// Conditional Return //
#define return_if( __TEST ) { if ( auto __Error ## __COUNTER__ = (__TEST) ) { return __Error ## __COUNTER__; } }
#define return_if_void( __TEST ) { if ( __TEST ) { return; } }
#define return_if_value( __RETCODE, __TEST ) { if ( __TEST ) { return __RETCODE; } }
//#define return_if_error( __TEST ) { if ( __return_if_error_type __Error ## __COUNTER__ = (__return_if_error_type)(__TEST) ) { return __Error ## __COUNTER__; } }
	
// Undconditionally Return (included for syntactical completeness) //
//#define return( __TEST ) { return (__TEST); } // DUH, this already exists in the C language! //
#define return_void( __TEST ) { (__TEST); return; }
#define return_value( __RETCODE, __TEST ) { (__TEST); return __RETCODE; }
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_UTIL_RETURN_IF_H__ //
// - ------------------------------------------------------------------------------------------ - //
