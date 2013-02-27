#ifndef SPINE_SKELETON_H_
#define SPINE_SKELETON_H_

#include <spine/BaseSkeleton.h>
//#include <SFML/Graphics/VertexArray.hpp>
#include <Graphics/Allocator/Allocator.h>
#include <Math/Matrix.h>
#include <Texture/Texture.h>
#include <spine-gel/SpineVertex.h>

namespace spine {

class Skeleton: public BaseSkeleton {
public:
	Allocator<SpineVertex> vertexArray;
	Texture::TextureHandle texture; // BOZO - This is ugly. Support multiple textures?

	Skeleton (SkeletonData *skeletonData);

	virtual void draw ( const Matrix4x4& Matrix ) const;
//	virtual void draw (sf::RenderTarget& target, sf::RenderStates states) const; // MK
};

} /* namespace spine */
#endif /* SPINE_SKELETON_H_ */
