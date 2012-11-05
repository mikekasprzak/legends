// - ------------------------------------------------------------------------------------------ - //
#ifndef __SATBODY_BODY_H__
#define __SATBODY_BODY_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Core/GelArray.h>
#include "SatModule.h"
// - ------------------------------------------------------------------------------------------ - //
class cSatBody {
public:
	GelArray<cSatModule>* Module;

public:
	inline const size_t Size() const {
		if ( Module )
			return Module->Size;
		else
			return 0;
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __SATBODY_BODY_H__ //
// - ------------------------------------------------------------------------------------------ - //
