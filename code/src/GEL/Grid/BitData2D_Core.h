// - ------------------------------------------------------------------------------------------ - //
#ifndef __Grid_BitGrid2D_Core_H__
#define __Grid_BitGrid2D_Core_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Core/Data.h>
// - ------------------------------------------------------------------------------------------ - //
// TODO: Switch tType to 'int'... or possible an unsigned int, due to bits only.
//   Make [] and () operators read only, because you can't correctly return a sub-address of a 
//   chunk of data. Therefor, you need a Set function.
//   Have a function for getting data Signed (if it's decided default behavior in unsigned).
// NOTE: DataBlock style may not be ideal for bits.
// - ------------------------------------------------------------------------------------------ - //
template< int BPP >
struct BitGrid2D {
	size_t w, h;
	typedef char tType;
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
		size_t Size = (w * h * BPP);
		return (Size >> 3) + (((Size & 7) > 0) ? 1 : 0);
	}

public:
	inline static const size_t SizeInBytes( const size_t _w, const size_t _h ) {
		size_t Size = (_w * _h * BPP);
		return (Size >> 3) + (((Size & 7) > 0) ? 1 : 0);
	}
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
template< int BPP >
inline BitGrid2D<BPP>* new_BitGrid2D( const size_t _Width, const size_t _Height ) {
	const size_t Size = BitGrid2D<BPP>::SizeInBytes( _Width, _Height );
	
	BitGrid2D<BPP>* p = reinterpret_cast<BitGrid2D<BPP>*>(new_Data( Size + sizeof(BitGrid2D<BPP>) ));
	if ( p ) {
		p->w = _Width;
		p->h = _Height;
		return p;
	}
	return 0;
}
// - ------------------------------------------------------------------------------------------ - //
template< int BPP >
inline void delete_BitGrid2D( BitGrid2D<BPP>* p ) {
	delete_Data( reinterpret_cast<char*>(p) );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Grid_BitGrid2D_Core_H__ //
// - ------------------------------------------------------------------------------------------ - //
