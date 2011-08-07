// - ------------------------------------------------------------------------------------------ - //
#ifndef __GraphicsDraw_TexturedRectangles2D_H__
#define __GraphicsDraw_TexturedRectangles2D_H__
// - ------------------------------------------------------------------------------------------ - //
#include "UV.h"
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawRectFillTextured( const Vector2D& P1, const Vector2D& P2, const GelColor Color = Current::Color ) {
    glEnable(GL_TEXTURE_2D);
	gelSetColor( Color );
    gelTextureShaded();
//    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    float Verts[] = {
		(float)P1.x+0.5f, (float)P1.y+0.5f,
		(float)P1.x+0.5f, (float)P2.y+0.5f,
		(float)P2.x+0.5f, (float)P1.y+0.5f,
		(float)P2.x+0.5f, (float)P2.y+0.5f,
    };

	GelUV UV[] = {
		GEL_UV_ZERO,GEL_UV_ZERO,
		GEL_UV_ZERO,GEL_UV_ONE,
		GEL_UV_ONE, GEL_UV_ZERO,
		GEL_UV_ONE, GEL_UV_ONE,
    };
    
    gelVertexPointer( 2, GL_FLOAT, 0, Verts );
	gelTexCoordPointer(2, GL_UVType, 0, UV);
    glDrawArrays( GL_TRIANGLE_STRIP, 0, 4 );

//	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	gelRestoreColor( Color );
    glDisable(GL_TEXTURE_2D);
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawRectFillTextured( const Real P1x, const Real P1y, const Real P2x, const Real P2y, const GelColor Color = Current::Color ) {
    glEnable(GL_TEXTURE_2D);
	gelSetColor( Color );
    gelTextureShaded();
//    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    float Verts[] = {
		(float)P1x+0.5f, (float)P1y+0.5f,
		(float)P1x+0.5f, (float)P2y+0.5f,
		(float)P2x+0.5f, (float)P1y+0.5f,
		(float)P2x+0.5f, (float)P2y+0.5f,
	};

	GelUV UV[] = {
		GEL_UV_ZERO,GEL_UV_ZERO,
		GEL_UV_ZERO,GEL_UV_ONE,
		GEL_UV_ONE, GEL_UV_ZERO,
		GEL_UV_ONE, GEL_UV_ONE,
    };
        
    gelVertexPointer( 2, GL_FLOAT, 0, Verts );
	gelTexCoordPointer(2, GL_UVType, 0, UV);
    glDrawArrays( GL_TRIANGLE_STRIP, 0, 4 );

//	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	gelRestoreColor( Color );
    glDisable(GL_TEXTURE_2D);
}
// - ------------------------------------------------------------------------------------------ - //
#endif // __GraphicsDraw_TexturedRectangles2D_H__ //
// - ------------------------------------------------------------------------------------------ - //
