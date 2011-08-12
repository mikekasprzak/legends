// - ------------------------------------------------------------------------------------------ - //
// GelFileInfo - Information about a file on disk //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_Core_GelFileInfo_H__
#define __GEL_Core_GelFileInfo_H__
// -------------------------------------------------------------------------- //
#if defined(USES_GEL) && !defined(NO_PLATFORM_H)
#include "../Platform.h"
#endif // USES_GEL && NO_PLATFORM_H //
// - ------------------------------------------------------------------------------------------ - //

// Cheating, just using a stat structure //
#include <sys/types.h>
#include <sys/stat.h>

struct GelFileInfo {
	// NOTE: struct first because STUPID C library has a function and a type called stat //
	struct stat Status;
	
	inline void Test( const char* InFile ) {
		stat( InFile, &Status );
	}
	
	inline const bool IsDirectory() const {
		return S_ISDIR( Status.st_mode ) != 0;
	}
	inline const bool IsFile() const {
		return S_ISREG( Status.st_mode ) != 0;
	}
	
	inline const bool HasChanged( const GelFileInfo& Vs ) const {
		return Status.st_mtime != Vs.Status.st_mtime;	
	}
	
	inline void Clear() {
		set_Data( 0, this, sizeof( GelFileInfo ) );
	}
};

// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_Core_GelFileInfo_H__ //
// - ------------------------------------------------------------------------------------------ - //
