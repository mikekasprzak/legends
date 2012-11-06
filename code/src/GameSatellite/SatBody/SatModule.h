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
		Component( new_GelArray<uSatComponent>(0) )
	{
	}
	
	~cSatModule() {
		if ( Component ) {
			// Clean Up Modules //
			for ( size_t idx = 0; idx < Component->Size; idx++ ) {
				if ( Component->Data[idx].Type == SatComponent::PLANAR ) {
					Component->Data[idx].Planar.Delete();
				}
				else if ( Component->Data[idx].Type == SatComponent::MESH ) {
					Component->Data[idx].Mesh.Delete();
				}
				else {
					// !!! //	
				}
			}
			
			// Delete the Component //
			delete_GelArray<uSatComponent>( Component );
		}
	}

public:
	inline const size_t Size() const {
		if ( Component )
			return Component->Size;
		else
			return 0;
	}
	
	inline uSatComponent* Back() { 
		return back_GelArray<uSatComponent>( Component );
	}
	
	void Add( const int Type ) {
		pushback_GelArray<uSatComponent>( &Component );
		
		// Set the type and clear the data //
		Back()->Type = Type;
		Back()->Data = 0;
	}

	void AddPlanar( const size_t PlaneCount ) {
		Add( SatComponent::PLANAR );
		Back()->Planar.New( PlaneCount );
	}
	
	void AddMesh( const size_t VertCount, const size_t IndexCount ) {	
		Add( SatComponent::MESH );
		Back()->Mesh.New( VertCount, IndexCount );
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __SATBODY_MODULE_H__ //
// - ------------------------------------------------------------------------------------------ - //
