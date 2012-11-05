// - ------------------------------------------------------------------------------------------ - //
#ifndef __BODY_MODULE_H__
#define __BODY_MODULE_H__
// - ------------------------------------------------------------------------------------------ - //
#include "Component_Base.h"
#include "Component_Planar.h"
#include "Component_Mesh.h"

#include <vector>
// - ------------------------------------------------------------------------------------------ - //
union uComponent {
	//cComponent_Base	Base;
	struct {	// cComponent_Base inlined as part of the union //
		int		Type;
		st32 	Size;
		char	Data[0];
	};
	cComponent_Planar	Planar;
	cComponent_Mesh		Mesh;
};
// - ------------------------------------------------------------------------------------------ - //
class cModule {
public:
	// Some Container Type of Components //
	std::vector< uComponent > Component;
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __BODY_MODULE_H__ //
// - ------------------------------------------------------------------------------------------ - //
