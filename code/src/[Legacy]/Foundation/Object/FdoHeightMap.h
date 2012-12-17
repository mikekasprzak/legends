// - ------------------------------------------------------------------------------------------ - //
#ifndef __FOUNDATION_OBJECT_FdoHeightMap_H__
#define __FOUNDATION_OBJECT_FdoHeightMap_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Grid/Grid2D.h>
// - ------------------------------------------------------------------------------------------ - //
class cFdoHeightMap {
public:
	typedef short GridType;
	typedef Grid2D<GridType> HeightMap;
	HeightMap* Data;

public:	
	cFdoHeightMap() :
		Data( 0 )
	{
	}
	
	cFdoHeightMap( const size_t w, const size_t h ) :
		Data( new_Grid2D<GridType>(w,h) )
	{
	}

	~cFdoHeightMap() {
		if ( Data ) {
			delete_Grid2D<GridType>( Data );
			Data = 0;
		}
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __FOUNDATION_OBJECT_FdoHeightMap_H__ //
// - ------------------------------------------------------------------------------------------ - //
