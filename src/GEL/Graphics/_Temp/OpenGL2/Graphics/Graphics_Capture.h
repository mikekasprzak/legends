// - ------------------------------------------------------------------------------------------ - //
#ifndef __Graphics_Capture_H__
#define __Graphics_Capture_H__
// - ------------------------------------------------------------------------------------------ - //
extern unsigned int GLCapture;
// - ------------------------------------------------------------------------------------------ - //
inline void gelInitCapture() {
/*
	glGenTextures( 1, &GLCapture );
*/
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelCapture() {
/*
	// ** TODO ** FIX THIS to scale to screen size //
	glBindTexture( GL_TEXTURE_2D, GLCapture );
	//glCopyTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, 0, 0, 512 * RefScreen::Scalar, 512 * RefScreen::Scalar, 0);
	glCopyTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, 0, 0, ActualScreen::Width, ActualScreen::Height, 0);
*/
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelSetCapture() {
/*
	glBindTexture( GL_TEXTURE_2D, GLCapture );
	gelSetSmoothTextures();
*/
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawCapture() {
/*
	gelSetCapture();
	glEnable(GL_TEXTURE_2D);

	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	
	{
#if defined(IPHONE_BUILD) || defined(USES_OPENGLES)
//	    float Verts[] = {
//			-160,-240,
//			-160,240,
//			160,-240,
//			160,240,
//		};
		
//		int Height = ((480 * RefScreen::Scalar) * GEL_UV_ONE) / (512 * RefScreen::Scalar);
//		int Width = ((320 * RefScreen::Scalar) * GEL_UV_ONE) / (512 * RefScreen::Scalar);


	    float Verts[] = {
			-160,-240,
			-160,240,
			160,-240,
			160,240,
		};

		int Height = GEL_UV_ONE;//((480 * RefScreen::Scalar) * GEL_UV_ONE) / (512 * RefScreen::Scalar);
		int Width = GEL_UV_ONE;//((320 * RefScreen::Scalar) * GEL_UV_ONE) / (512 * RefScreen::Scalar);
		
		GelUV UVs[] = {
			GEL_UV_ZERO, Height,
			GEL_UV_ZERO, GEL_UV_ZERO,
			Width, Height,
			Width, GEL_UV_ZERO,
		};
		glPushMatrix();
		glRotatef(-90,0,0,1);
		glVertexPointer(2, GL_FLOAT, 0, Verts);
		glTexCoordPointer(2, GL_UVType, 0, UVs);
	    glDrawArrays( GL_TRIANGLE_STRIP, 0, 4 );
		glPopMatrix();
#else
	    float Verts[] = {
			-240,-160,
			-240,160,
			240,-160,
			240,160,
		};
		
		int Width = (int)((480.0f * RefScreen::Scalar) * (float)GEL_UV_ONE) / (512.0f * RefScreen::Scalar);
		int Height = (int)((320.0f * RefScreen::Scalar) * (float)GEL_UV_ONE) / (512.0f * RefScreen::Scalar);
		
		GelUV UVs[] = {
			GEL_UV_ZERO, Height,
			GEL_UV_ZERO, GEL_UV_ZERO,
			Width, Height,
			Width, GEL_UV_ZERO,
		};
		
		glVertexPointer(2, GL_FLOAT, 0, Verts);
		glTexCoordPointer(2, GL_UVType, 0, UVs);
	    glDrawArrays( GL_TRIANGLE_STRIP, 0, 4 );
#endif // IPHONE_BUILD //
	}	

	glDisable(GL_TEXTURE_2D);
*/
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelFreeCapture() {
/*
	glDeleteTextures( 1, &GLCapture );
	GLCapture = 0;
*/
}
// - ------------------------------------------------------------------------------------------ - //
#endif // __Graphics_Capture_H__ //
// - ------------------------------------------------------------------------------------------ - //
