// - ------------------------------------------------------------------------------------------ - //
// Endian - Endian manipulation functions //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_GELCore_Endian_H__
#define __Library_GELCore_Endian_H__
// - ------------------------------------------------------------------------------------------ - //
// USAGE: use the "swaple( ... )" family of functions to wrap any data that should be in LE format //
// - ------------------------------------------------------------------------------------------ - //
// Core Swapping Functions (the same no matter the endian) //
#include "Endian_Core.h"
// Depending on the current configuration, change the effect of the swaple and swapbe functions //
#ifdef BIG_ENDIAN
	#include "Endian_Big.h"
#else
	#include "Endian_Little.h"
#endif // BIG_ENDIAN //
// Macro function swaple and swapbe (the prior step is the swaple2, swaple3, swaple4, etc) //
#include "Endian_Accessory.h"
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_Endian_H__ //
// - ------------------------------------------------------------------------------------------ - //
