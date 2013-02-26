#ifndef SPINE_REGIONATTACHMENT_H_
#define SPINE_REGIONATTACHMENT_H_

#include <spine/BaseRegionAttachment.h>
#include <Style/Style.h>
#include <Math/Vector.h>
#include <Texture/Texture.h>
#include <Graphics/GelColor.h>
#include <Render/UV.h>

namespace spine {

class Bone;
class AtlasRegion;

struct SpineVertex {
	Vector2D position;
	ABSet<Render::UVType> texCoords;
	GelColor color;
};

class RegionAttachment: public BaseRegionAttachment {
public:
	SpineVertex vertices[4];
	Texture::TextureHandle *texture;

	RegionAttachment (AtlasRegion *region);

	virtual void updateWorldVertices (Bone *bone);
	virtual void draw (Slot *slot);
};

} /* namespace spine */
#endif /* SPINE_REGIONATTACHMENT_H_ */
