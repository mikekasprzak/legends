#include <iostream>
#include <spine-gel/Skeleton.h>
#include <spine/SkeletonData.h>
#include <spine/Slot.h>
#include <spine/Attachment.h>
//#include <SFML/Graphics/RenderTarget.hpp>
//#include <SFML/Graphics/RenderStates.hpp>
#include <Texture/Texture.h>

//using sf::Quads;
//using sf::RenderTarget;
//using sf::RenderStates;

namespace spine {

Skeleton::Skeleton (SkeletonData *skeletonData) :
				BaseSkeleton(skeletonData),
				vertexArray(Quads, skeletonData->bones.size() * 4),
				texture(0) {
}

//void Skeleton::draw (RenderTarget& target, RenderStates states) const {
void Skeleton::draw ( const Matrix4x4& Matrix ) const {
	const_cast<Skeleton*>(this)->vertexArray.clear();
	for (int i = 0, n = slots.size(); i < n; i++)
		if (slots[i]->attachment) slots[i]->attachment->draw(slots[i]);
	//target.draw(vertexArray, texture);
	// DO DRAW HERE //
}

} /* namespace spine */
