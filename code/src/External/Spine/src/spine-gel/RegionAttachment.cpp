#include <iostream>
#include <Math/Vector.h>
#include <spine-gel/RegionAttachment.h>
#include <spine-gel/Atlas.h>
#include <spine-gel/Skeleton.h>
#include <spine/Bone.h>
#include <spine/Slot.h>

namespace spine {

RegionAttachment::RegionAttachment (AtlasRegion *region) {
	texture = region->page->texture; // BOZO - Resolve attachment as late as possible?
	int u = region->x;
	int u2 = u + region->width;
	int v = region->y;
	int v2 = v + region->height;
	
	u *= UV_ONE;
	v *= UV_ONE;
	u2 *= UV_ONE;
	v2 *= UV_ONE;
	
	u /= 256;
	v /= 256;
	u2 /= 256;
	v2 /= 256;
	
	if (region->rotate) {
		vertices[1].texCoords.x = u;
		vertices[1].texCoords.y = v2;
		vertices[2].texCoords.x = u;
		vertices[2].texCoords.y = v;
		vertices[3].texCoords.x = u2;
		vertices[3].texCoords.y = v;
		vertices[0].texCoords.x = u2;
		vertices[0].texCoords.y = v2;
	} else {
		vertices[0].texCoords.x = u;
		vertices[0].texCoords.y = v2;
		vertices[1].texCoords.x = u;
		vertices[1].texCoords.y = v;
		vertices[2].texCoords.x = u2;
		vertices[2].texCoords.y = v;
		vertices[3].texCoords.x = u2;
		vertices[3].texCoords.y = v2;
	}
}

void RegionAttachment::draw (Slot *slot) {
	Skeleton* skeleton = (Skeleton*)slot->skeleton;

	int r = skeleton->r * slot->r * 255;
	int g = skeleton->g * slot->g * 255;
	int b = skeleton->b * slot->b * 255;
	int a = skeleton->a * slot->a * 255;
	
//	if ( r > 255 )
//		r = 255;
//	else if ( r < 0 )
//		r = 0;
//
//	if ( g > 255 )
//		g = 255;
//	else if ( g < 0 )
//		g = 0;
//
//	if ( b > 255 )
//		b = 255;
//	else if ( b < 0 )
//		b = 0;
//
//	if ( a > 255 )
//		a = 255;
//	else if ( a < 0 )
//		a = 0;
	
	vertices[0].color = GEL_RGBA(r,g,b,a);
	vertices[1].color = GEL_RGBA(r,g,b,a);
	vertices[2].color = GEL_RGBA(r,g,b,a);
	vertices[3].color = GEL_RGBA(r,g,b,a);

	updateOffset(); // BOZO - Move to resolve()?
	updateWorldVertices(slot->bone);

	skeleton->texture = texture;
	skeleton->vertexArray.Add(vertices[0]);
	skeleton->vertexArray.Add(vertices[1]);
	skeleton->vertexArray.Add(vertices[2]);
	
	skeleton->vertexArray.Add(vertices[2]);
	skeleton->vertexArray.Add(vertices[3]);
	skeleton->vertexArray.Add(vertices[0]);
}

void RegionAttachment::updateWorldVertices (spine::Bone *bone) {
	float x = bone->worldX;
	float y = bone->worldY;
	float m00 = bone->m00;
	float m01 = bone->m01;
	float m10 = bone->m10;
	float m11 = bone->m11;
	vertices[0].position.x = offset[0] * m00 + offset[1] * m01 + x;
	vertices[0].position.y = offset[0] * m10 + offset[1] * m11 + y;
	vertices[1].position.x = offset[2] * m00 + offset[3] * m01 + x;
	vertices[1].position.y = offset[2] * m10 + offset[3] * m11 + y;
	vertices[2].position.x = offset[4] * m00 + offset[5] * m01 + x;
	vertices[2].position.y = offset[4] * m10 + offset[5] * m11 + y;
	vertices[3].position.x = offset[6] * m00 + offset[7] * m01 + x;
	vertices[3].position.y = offset[6] * m10 + offset[7] * m11 + y;
}

} /* namespace spine */
