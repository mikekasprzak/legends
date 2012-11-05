// - ------------------------------------------------------------------------------------------ - //
#ifndef __SATBODY_MODULE_H__
#define __SATBODY_MODULE_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Core/GelArray.h>
#include "SatComponent_Base.h"
#include "SatComponent_Planar.h"
#include "SatComponent_Mesh.h"
// - ------------------------------------------------------------------------------------------ - //
union uSatComponent {
	//cSatComponent_Base	Base;
	struct {	// cSatComponent_Base inlined as part of the union //
		int		Type;
		void*	Data;
	};
	cSatComponent_Planar	Planar;
	cSatComponent_Mesh		Mesh;
};
// - ------------------------------------------------------------------------------------------ - //
class cSatModule {
public:
	GelArray<uSatComponent>* Component;
	
public:
	cSatModule() :
		Component( 0 )
	{
	}
	
	~cSatModule() {
		if ( Component ) {
			// Clean Up Modules //
			//Component
			
			// Delete the Component //
			delete_GelArray<uSatComponent>( Component );
		}
	}
	
	void Add( const int Type ) {
		// Create or Resize Component //
		pushback_GelArray<uSatComponent>( &Component );
		uSatComponent* Back = back_GelArray<uSatComponent>( Component );
		
		// Set the type and clear the data //
		Back->Type = Type;
		Back->Data = 0;
	}

public:
	inline const size_t Size() const {
		if ( Component )
			return Component->Size;
		else
			return 0;
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __SATBODY_MODULE_H__ //
// - ------------------------------------------------------------------------------------------ - //
