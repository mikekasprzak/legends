// - ------------------------------------------------------------------------------------------ - //
#ifndef __Grid_Grid2D_Image_H__
#define __Grid_Grid2D_Image_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Style/Style.h>
#include "Grid2D_Core.h"
#include <External/STB/stb_image.h>
// - ------------------------------------------------------------------------------------------ - //
template< class tType >
inline Grid2D<tType>* load_Grid2D( const char* FileName ) {
	int w, h, Info;
//	unsigned char* Data = stbi_load( FileName, &w, &h, &Info, sizeof(tType) );
	unsigned char* Data = stbi_load( FileName, &w, &h, &Info, 0 );
	Log( "%i %i %i\n", w, h, Info );
	
	if ( Data == 0 )
		return 0;
	
	Grid2D<tType>* GridData = new_Grid2D<tType>(w,h);
//	copy_Data(Data, GridData->Data, w*h*Info);
	copyPadded_Data(Data, GridData->Data, w*h*Info, Info, sizeof(tType)-Info,255);
	
	stbi_image_free( Data );
	
	return GridData;
}
// - ------------------------------------------------------------------------------------------ - //
template< class tType >
inline void save_BMP_Grid2D( Grid2D<tType>* Data, const char* FileName ) {
	stbi_write_bmp( FileName, Data->w, Data->h, sizeof(tType), Data->Data );
}
// - ------------------------------------------------------------------------------------------ - //
template< class tType >
inline void save_TGA_Grid2D( Grid2D<tType>* Data, const char* FileName ) {
	stbi_write_tga( FileName, Data->w, Data->h, sizeof(tType), Data->Data );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Grid_Grid2D_Image_H__ //
// - ------------------------------------------------------------------------------------------ - //
