// - ------------------------------------------------------------------------------------------ - //
#ifndef __GraphicsDraw_TexturedRectangles2D_H__
#define __GraphicsDraw_TexturedRectangles2D_H__
// - ------------------------------------------------------------------------------------------ - //
#include "UV.h"
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawRectFillTextured( const Vector2D& P1, const Vector2D& P2, const GelColor Color = Current::Color ) {
/*
    glEnable(GL_TEXTURE_2D);
	gelSetColor( Color );
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    float Verts[] = {
		(float)P1.x+0.5f, (float)P1.y+0.5f,
		(float)P1.x+0.5f, (float)P2.y+0.5f,
		(float)P2.x+0.5f, (float)P1.y+0.5f,
		(float)P2.x+0.5f, (float)P2.y+0.5f,
    };

	GelUV UV[] = {
		UV_ZERO,UV_ZERO,
		UV_ZERO,UV_ONE,
		UV_ONE, UV_ZERO,
		UV_ONE, UV_ONE,
    };
    
    glVertexPointer( 2, GL_FLOAT, 0, Verts );
	glTexCoordPointer(2, GL_UVType, 0, UV);
    glDrawArrays( GL_TRIANGLE_STRIP, 0, 4 );

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	gelRestoreColor( Color );
    glDisable(GL_TEXTURE_2D);
*/
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawRectFillTextured( const Real P1x, const Real P1y, const Real P2x, const Real P2y, const GelColor Color = Current::Color ) {
/*
    glEnable(GL_TEXTURE_2D);
	gelSetColor( Color );
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    float Verts[] = {
		(float)P1x+0.5f, (float)P1y+0.5f,
		(float)P1x+0.5f, (float)P2y+0.5f,
		(float)P2x+0.5f, (float)P1y+0.5f,
		(float)P2x+0.5f, (float)P2y+0.5f,
	};

	GelUV UV[] = {
		UV_ZERO,UV_ZERO,
		UV_ZERO,UV_ONE,
		UV_ONE, UV_ZERO,
		UV_ONE, UV_ONE,
    };
        
    glVertexPointer( 2, GL_FLOAT, 0, Verts );
	glTexCoordPointer(2, GL_UVType, 0, UV);
    glDrawArrays( GL_TRIANGLE_STRIP, 0, 4 );

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	gelRestoreColor( Color );
    glDisable(GL_TEXTURE_2D);
*/
}
// - ------------------------------------------------------------------------------------------ - //
#endif // __GraphicsDraw_TexturedRectangles2D_H__ //
// - ------------------------------------------------------------------------------------------ - //
