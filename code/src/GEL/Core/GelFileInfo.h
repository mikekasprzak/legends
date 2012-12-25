// - ------------------------------------------------------------------------------------------ - //
// GelFileInfo - Information about a file on disk //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_Core_GelFileInfo_H__
#define __GEL_Core_GelFileInfo_H__
// -------------------------------------------------------------------------- //
#include <sys/types.h>
#include <sys/stat.h>

#include <Core/Data.h>
// -------------------------------------------------------------------------- //
struct GelFileInfo {
	int Err;				// Error code returned by stat //
	
	// NOTE: struct keyword because STUPID C library has both a function and a type called stat //
	struct stat Status;

public:
	inline GelFileInfo() :
		Err( -1 )
	{
		//Clear();
	}
	
	inline GelFileInfo( const char* InFile ) {
		Err = stat( InFile, &Status );
	}

public:
	inline const bool Exists() const {
		return Err == 0;// Status.st_mode != 0;
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
