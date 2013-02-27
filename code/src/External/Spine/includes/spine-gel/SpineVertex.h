#ifndef SPINE_SPINEVERTEX_H
#define SPINE_SPINEVERTEX_H

#include <Math/Vector.h>
#include <Graphics/GelColor.h>
#include <Render/UV.h>

namespace spine {

struct SpineVertex {
	Vector2D position;
	XYSet<Render::UVType> texCoords;
	GelColor color;
};

} // namespace spine //

#endif // SPINE_SPINEVERTEX_H //
