#ifndef SPINE_REGIONATTACHMENT_H_
#define SPINE_REGIONATTACHMENT_H_

#include <spine/BaseRegionAttachment.h>
#include <Style/Style.h>
#include <Texture/Texture.h>
#include <spine-gel/SpineVertex.h>

namespace spine {

class Bone;
class AtlasRegion;

class RegionAttachment: public BaseRegionAttachment {
public:
	SpineVertex vertices[4];
	Texture::TextureHandle texture;

	RegionAttachment (AtlasRegion *region);

	virtual void updateWorldVertices (Bone *bone);
	virtual void draw (Slot *slot);
};

} /* namespace spine */
#endif /* SPINE_REGIONATTACHMENT_H_ */
