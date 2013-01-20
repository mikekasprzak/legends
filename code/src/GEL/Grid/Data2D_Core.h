// - ------------------------------------------------------------------------------------------ - //
#ifndef __Grid_Grid2D_Core_H__
#define __Grid_Grid2D_Core_H__
// - ------------------------------------------------------------------------------------------ - //
#include <limits.h>
#include <Core/GelLimits.h>
#include <Core/Data.h>
// - ------------------------------------------------------------------------------------------ - //
template< class tType = int >
struct Grid2D {
	size_t w, h;
	tType Data[];

public:
	inline const size_t Width() const {
		return w;
	}
	
	inline const size_t Height() const {
		return h;
	}

	inline const size_t Size() const {
		return w * h;
	}

	inline const size_t SizeInBytes() const {
		return w * h * sizeof( tType );
	}

	inline const tType& Index( const size_t _w, const size_t _h ) const {
		return Data[(h*_w) + _w];
	}

	inline tType& Index( const size_t _w, const size_t _h ) {
		return Data[(_h*w) + _w];
	}

public:
	inline static const size_t SizeInBytes( const size_t _w, const size_t _h ) {
		return _w * _h * sizeof( tType );
	}
};
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
template< class tType >
inline Grid2D<tType>* new_Grid2D( const size_t _Width, const size_t _Height ) {
	const size_t Size = Grid2D<tType>::SizeInBytes( _Width, _Height );
	
	Grid2D<tType>* p = reinterpret_cast<Grid2D<tType>*>(new_Data( Size + sizeof(Grid2D<tType>) ));
	if ( p ) {
		p->w = _Width;
		p->h = _Height;
		return p;
	}
	return 0;
}
// - ------------------------------------------------------------------------------------------ - //
template< class tType >
inline void delete_Grid2D( Grid2D<tType>* p ) {
	delete_Data( reinterpret_cast<char*>(p) );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Grid_Grid2D_Core_H__ //
// - ------------------------------------------------------------------------------------------ - //
