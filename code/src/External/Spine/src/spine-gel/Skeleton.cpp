#include <iostream>
#include <spine-gel/Skeleton.h>
#include <spine/SkeletonData.h>
#include <spine/Slot.h>
#include <spine/Attachment.h>
//#include <SFML/Graphics/RenderTarget.hpp>
//#include <SFML/Graphics/RenderStates.hpp>
#include <Texture/Texture.h>
#include <Render/Render.h>

//using sf::Quads;
//using sf::RenderTarget;
//using sf::RenderStates;

namespace spine {

Skeleton::Skeleton (SkeletonData *skeletonData) :
				BaseSkeleton(skeletonData),
				vertexArray( skeletonData->bones.size() * 4 ),
				texture(0) {
}

//void Skeleton::draw (RenderTarget& target, RenderStates states) const {
void Skeleton::draw ( const Matrix4x4& Matrix ) const {
	const_cast<Skeleton*>(this)->vertexArray.Clear();
	for (int i = 0, n = slots.size(); i < n; i++)
		if (slots[i]->attachment) slots[i]->attachment->draw(slots[i]);
	//target.draw(vertexArray, texture);
	// DO DRAW HERE //

	Render::Default->Bind( Render::FlatShader2D_Packed );
	Render::Default->UniformMatrix4x4( 0, Matrix );
	Render::Default->UniformColor( 1, GEL_RGB_WHITE ); // GlobalColor //
	Render::Default->Uniform1i( 2, 0 );	// TexImage0 //
	Render::Default->BindUniforms();
	Texture::Bind( texture, 0 );
	Render::Default->Attrib( 0, &vertexArray[0].position );
	Render::Default->Attrib( 1, &vertexArray[0].color );
	Render::Default->Attrib( 2, &vertexArray[0].texCoords );
	Render::Default->DrawArrays( GEL_TRIANGLE_STRIP, vertexArray.Size() );
}

} /* namespace spine */
