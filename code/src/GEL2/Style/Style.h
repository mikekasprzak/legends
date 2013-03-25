// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL2_STYLE_STYLE_H__
#define __GEL2_STYLE_STYLE_H__
// - ------------------------------------------------------------------------------------------ - //
#include "GelTypes.h"		// st32, st64, u16, f32 //
#include "GelError.h"		// GelError, GEL_OK, GEL_ERROR //
#include "GelConstants.h"	// GEL_ALIGN_CENTER, etc //

#include "return_if.h"		// return_if( condition ) //
#include "threadlocal.h"	// threadlocal (__thread) //
#include "safe_sprintf.h"	// sprintf that asks for dest string size //

#include "Log.h"			// Log, VLog, and so many more //

#include "Functor.h"
#include "Signal.h"			//

#include "NSet.h"			// NSet1, NSet2, like Set but each member can have a different type //
#include <Types/Set.h>		// TODO: Move to style //
#include <Util/Binary.h>	// TODO: ^ //

#include "MinMax.h"			// Min and Max functions that take up to 7 arguments //
#include "EqLtGt.h"			// Test functions Eq,Neq,Lt,Gt,Lte,Gte that test one vs up to 7 values //
#include "AllEqLtGt.h"		// Alternative test functions that only return true if all args are same //
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL2_STYLE_STYLE_H__ //
// - ------------------------------------------------------------------------------------------ - //
