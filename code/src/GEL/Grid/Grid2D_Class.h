// - ------------------------------------------------------------------------------------------ - //
#ifndef __Grid_Grid2D_Class_H__
#define __Grid_Grid2D_Class_H__
// - ------------------------------------------------------------------------------------------ - //
#include <math.h>
// - ------------------------------------------------------------------------------------------ - //
// TODO: Math Functions, Insert (creating rows and columns to fit, X/YAxis Only)
//   Rename Resize to Canvas and/or Clip. 
//   Make Resize do scaling, providing scaling algorithm choices. Pixel, Bilinear.
//   Make SetWidth make more sense (i.e. what SetW does).
//   Do Dimensions really need to be size_t's? st32's maybe. 65535x65535 is > 4 GB,
//   that said you may want a tall skinny grid, so st32 is preferable to st16.

// TODO: Rename all functions that change the data to "ActionData". 
// - ------------------------------------------------------------------------------------------ - //
template< class tType = int >
class cGrid2D {
	// - -------------------------------------------------------------------------------------- - //
	// Dimensions //
	size_t _w, _h;
	
	// Data Array //
	tType* Data;
	// - -------------------------------------------------------------------------------------- - //
public:
	// - -------------------------------------------------------------------------------------- - //
	inline cGrid2D() :
		_w( 0 ),
		_h( 0 ),
		Data( 0 )
	{
	}
	// - -------------------------------------------------------------------------------------- - //
	inline cGrid2D( const size_t w, const size_t h ) :
		_w( w ),
		_h( h ),
		Data( new tType[w*h] )
	{
	}
	// - -------------------------------------------------------------------------------------- - //
	inline cGrid2D( const size_t w, const size_t h, const tType& Type ) :
		_w( w ),
		_h( h ),
		Data( new tType[w*h] )
	{
		Fill(Type);
	}
	// - -------------------------------------------------------------------------------------- - //
	inline cGrid2D( const cGrid2D<tType>& Orig ) :
		_w( Orig._w ),
		_h( Orig._h ),
		Data( new tType[Size()] )
	{
		for ( size_t idx = Size(); idx--; ) {
			Data[ idx ] = Orig.Data[ idx ];
		}
	}
	// - -------------------------------------------------------------------------------------- - //
	inline cGrid2D<tType>& operator = (const cGrid2D<tType>& Orig) {
		if ( this != &Orig ) {
			// If we just happen to be the same total size //
			if ( Orig.Size() == Size() ) {
				_w = Orig._w;
				_h = Orig._h;

				// Copy our data and don't delete it //
				for ( size_t idx = Size(); idx--; ) {
					Data[ idx ] = Orig.Data[ idx ];
				}				
			}
			// If different size, or no size //
			else {
				// Toast our data, if we have one //
				if ( Data )
					delete [] Data;
				
				_w = Orig._w;
				_h = Orig._h;
				
				// Create and copy the data //
				Data = new tType[ Size() ];
				for ( size_t idx = Size(); idx--; ) {
					Data[ idx ] = Orig.Data[ idx ];
				}
			}
		}
		
		return *this;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline ~cGrid2D() {
		if ( Data ) {
			delete [] Data;
			Data = 0;
		}
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	inline const size_t Width() const {
		return _w;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const size_t Height() const {
		return _h;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const size_t HalfWidth() const {
		return _w >> 1;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const size_t HalfHeight() const {
		return _h >> 1;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const size_t Size() const {
		return _w * _h;
	}
	// - -------------------------------------------------------------------------------------- - //
	static inline void Fill( tType* Dest, const size_t Size, const tType& Value = tType() ) {
		for ( size_t idx = Size; idx--; ) {
			Dest[ idx ] = Value;
		}
	}
	// - -------------------------------------------------------------------------------------- - //
	inline void Fill( const tType& Value = tType() ) {
		Fill( Data, Size(), Value );
	}
	// - -------------------------------------------------------------------------------------- - //
	// Used Internally to explicitly change the Data pointer //
	inline void SetData( tType* NewData ) {
		if ( Data )
			delete [] Data;
			
		Data = NewData;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline void SetW( const size_t w ) {
		_w = w;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline void SetH( const size_t h ) {
		_h = h;
	}
	// - -------------------------------------------------------------------------------------- - //
	const tType* operator *() const {
		return Data;
	}
	// - -------------------------------------------------------------------------------------- - //
	tType* operator *() {
		return Data;
	}
	// - -------------------------------------------------------------------------------------- - //


	// - -------------------------------------------------------------------------------------- - //
	// Index Generating functions.  Return a valid index for [] operator. //
	// - -------------------------------------------------------------------------------------- - //
	inline const size_t Index( const int _x, const int _y ) const {
		// TODO: Assert out of bounds 
		return _x + (_y * Width());
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const size_t IndexWrap( int _x, int _y ) const {
		if ( _x < 0 )
			_x = -_x;
		if ( _y < 0 )
			_y = -_y;
		return (_x % Width()) + ((_y % Height()) * Width());
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const size_t IndexWrapX( int _x, const int _y ) const {
		if ( _x < 0 )
			_x = -_x;
		return (_x % Width()) + ((_y) * Height());
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const size_t IndexWrapY( const int _x, int _y ) const {
		if ( _y < 0 )
			_y = -_y;
		return (_x) + ((_y % Height()) * Width());
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const size_t IndexNextWrap( const int _x, const int _y ) const {
		return (_x + (_y * Width())) % Size();
	}
	// - -------------------------------------------------------------------------------------- - //
	// Get the position, aligning to edges //
	inline const size_t IndexClip( int _x, int _y ) const {
		if ( _x >= Width() )
			_x = Width() - 1;
		else if ( _x < 0 )
			_x = 0;
			
		if ( _y >= Height() )
			_y = Height() - 1;
		else if ( _y < 0 )
			_y = 0;
			
		return Index( _x, _y );
	}
	// - -------------------------------------------------------------------------------------- - //
	// Get the position, aligning to edges //
	inline const size_t IndexClipX( int _x, int _y ) const {
		if ( _x >= Width() )
			_x = Width() - 1;
		else if ( _x < 0 )
			_x = 0;
			
		return Index( _x, _y );
	}
	// - -------------------------------------------------------------------------------------- - //
	// Get the position, aligning to edges //
	inline const size_t IndexClipY( int _x, int _y ) const {
		if ( _y >= Height() )
			_y = Height() - 1;
		else if ( _y < 0 )
			_y = 0;
			
		return Index( _x, _y );
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	inline const size_t IndexToX( const int _Index ) const {
		// TODO: Assert out of bounds 
		return _Index % Width();
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const size_t IndexToY( const int _Index ) const {
		// TODO: Assert out of bounds 
		return _Index / Width();
	}
	// - -------------------------------------------------------------------------------------- - //

	
	// - -------------------------------------------------------------------------------------- - //
	inline tType& operator () ( const size_t _x, const size_t _y ) {
		return Data[ Index( _x, _y ) ];
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const tType& operator () ( const size_t _x, const size_t _y ) const {
		return Data[ Index( _x, _y ) ];
	}
	// - -------------------------------------------------------------------------------------- - //
	inline tType& operator [] ( const size_t _Index ) {
		// TODO: Assert out of bounds 
		return Data[ _Index ];
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const tType& operator [] ( const size_t _Index ) const {
		// TODO: Assert out of bounds 
		return Data[ _Index ];
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Get the position, with axis wrapping //
	inline tType& Wrap( const int _x, const int _y ) {
		return Data[ IndexWrap( _x, _y ) ];
	}
	inline const tType& Wrap( const int _x, const int _y ) const {
		return Data[ IndexWrap( _x, _y ) ];
	}
	// - -------------------------------------------------------------------------------------- - //
	// Get the position, with axis wrapping //
	inline tType& WrapX( const int _x, const int _y ) {
		return Data[ IndexWrapX( _x, _y ) ];
	}
	// - -------------------------------------------------------------------------------------- - //
	// Get the position, with axis wrapping //
	inline const tType& WrapX( const int _x, const int _y ) const {
		return Data[ IndexWrapX( _x, _y ) ];
	}
	// - -------------------------------------------------------------------------------------- - //
	// Get the position, with axis wrapping //
	inline tType& WrapY( const int _x, const int _y ) {
		return Data[ IndexWrapY( _x, _y ) ];
	}
	// - -------------------------------------------------------------------------------------- - //
	// Get the position, with axis wrapping //
	inline const tType& WrapY( const int _x, const int _y ) const {
		return Data[ IndexWrapY( _x, _y ) ];
	}
	// - -------------------------------------------------------------------------------------- - //
	// Get the position, with next line/first line wrapping //
	inline tType& NextWrap( const int _x, const int _y ) {
		return Data[ IndexNextWrap( _x, _y ) ];
	}
	// - -------------------------------------------------------------------------------------- - //
	// Get the position, with next line/first line wrapping //
	inline const tType& NextWrap( const int _x, const int _y ) const {
		return Data[ IndexNextWrap( _x, _y ) ];
	}
	// - -------------------------------------------------------------------------------------- - //
	// Get the position, aligning to edges //
	inline tType& Clip( const int _x, const int _y ) {
		return Data[ IndexClip( _x, _y ) ];
	}
	// - -------------------------------------------------------------------------------------- - //
	// Get the position, aligning to edges //
	inline const tType& Clip( const int _x, const int _y ) const {	
		return Data[ IndexClip( _x, _y ) ];
	}
	// - -------------------------------------------------------------------------------------- - //
	// Get the position, aligning to edges //
	inline tType& ClipX( const int _x, const int _y ) {
		return Data[ IndexClipX( _x, _y ) ];
	}
	// - -------------------------------------------------------------------------------------- - //
	// Get the position, aligning to edges //
	inline const tType& ClipX( const int _x, const int _y ) const {	
		return Data[ IndexClipX( _x, _y ) ];
	}
	// - -------------------------------------------------------------------------------------- - //
	// Get the position, aligning to edges //
	inline tType& ClipY( const int _x, const int _y ) {
		return Data[ IndexClipY( _x, _y ) ];
	}
	// - -------------------------------------------------------------------------------------- - //
	// Get the position, aligning to edges //
	inline const tType& ClipY( const int _x, const int _y ) const {	
		return Data[ IndexClipY( _x, _y ) ];
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Get the position, aligning to edges //
	inline const int ClipX( int _x ) const {
		if ( _x >= Width() )
			_x = Width() - 1;
		else if ( _x < 0 )
			_x = 0;
		
		return _x;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Get the position, aligning to edges //
	inline const int ClipY( int _y ) const {
		if ( _y >= Height() )
			_y = Height() - 1;
		else if ( _y < 0 )
			_y = 0;
			
		return _y;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const size_t WrapX( int _x ) const {
		if ( _x < 0 )
			_x = -_x;
		return (_x % Width());
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const size_t WrapY( int _y ) const {
		if ( _y < 0 )
			_y = -_y;
		return (_y % Height());
	}
	// - -------------------------------------------------------------------------------------- - //


	// - -------------------------------------------------------------------------------------- - //
	// Get the position, returning the dead value if over //
	inline const tType& DeadClip( const int _x, const int _y, const tType& DeadValue = tType() ) const {
		if ( _x >= Width() )
			return DeadValue;
		else if ( _x < 0 )
			return DeadValue;
			
		if ( _y >= Height() )
			return DeadValue;
		else if ( _y < 0 )
			return DeadValue;
			
		return Data[ Index( _x, _y ) ];
	}
	// - -------------------------------------------------------------------------------------- - //
	
private:
	// - -------------------------------------------------------------------------------------- - //
	static inline tType* CopyData(
		const cGrid2D< tType >& Src,
		const size_t NewWidth,
		const size_t NewHeight,
		const int SrcStartX,
		const int SrcStartY,
		const int DestStartX,
		const int DestStartY,
		const tType& InitValue = tType()
		)
	{
		tType* DataCopy = new tType[ NewWidth * NewHeight ];
		Fill( DataCopy, NewWidth * NewHeight, InitValue );
		
		size_t CopyWidth = 0;
		size_t CopyHeight = 0;
		
		// How much to Copy Wide //
		if ( NewWidth > Src.Width() ) {
			CopyWidth = Src.Width();
		}
		else {
			CopyWidth = NewWidth;
		}
		
		// How much to Copy Tall //
		if ( NewHeight > Src.Height() ) {
			CopyHeight = Src.Height();
		}
		else {
			CopyHeight = NewHeight;
		}
		
		// Copy Data //
		for ( size_t _y = CopyHeight; _y--; ) {
			for ( size_t _x = CopyWidth; _x--; ) {
				DataCopy[DestStartX + _x + ((DestStartY + _y) * NewWidth)] = 
					Src.Data[SrcStartX + _x + ((SrcStartY + _y) * Src.Width())];
			}
		}
		
		return DataCopy;
	}	
	// - -------------------------------------------------------------------------------------- - //
	static inline const cGrid2D< tType > Copy(
		const cGrid2D< tType >& Src,
		const size_t NewWidth,
		const size_t NewHeight,
		const int SrcStartX,
		const int SrcStartY,
		const int DestStartX,
		const int DestStartY,
		const tType& InitValue = tType()
		)
	{
		cGrid2D< tType > NewGrid;
		
		NewGrid.SetData( CopyData( Src, NewWidth, NewHeight, SrcStartX, SrcStartY, DestStartX, DestStartY, InitValue ) );
		NewGrid.w = NewWidth;
		NewGrid.h = NewHeight;
		
		return NewGrid;
	}
	// - -------------------------------------------------------------------------------------- - //
public:
	static inline const cGrid2D< tType > Merge(
		const cGrid2D< tType >& GridA,
		const cGrid2D< tType >& GridB,
		const int GridAX,
		const int GridAY,
		const int GridBX,
		const int GridBY,
		const tType& InitValue = tType()
		)
	{
		// Top corner of the grid //
		int GridX1 = GridAX;
		int GridY1 = GridAY;
		
		if ( GridX1 > GridBX )
			GridX1 = GridBX;
		if ( GridY1 > GridBY )
			GridY1 = GridBY;

			
		// Bottom corner of the grid //
		int GridX2 = GridAX + GridA.Width();
		int GridY2 = GridAY + GridA.Height();
		
		if ( GridX2 < (int)(GridBX + GridB.Width()) )
			GridX2 = GridBX + GridB.Width();
		if ( GridY2 < (int)(GridBY + GridB.Height()) )
			GridY2 = GridBY + GridB.Height();

		
		// Calculate the dimensions //
		int Width = GridX2 - GridX1;
		int Height = GridY2 - GridY1;

		
		// Calculate Start Positions //
		int AX = GridAX - GridX1;
		int AY = GridAY - GridY1;
		int BX = GridBX - GridX1;
		int BY = GridBY - GridY1;
			
		// Create a Grid to hold our copy //
		cGrid2D< tType > NewGrid( Width, Height, InitValue );

		// Copy GridA //
		for ( size_t _y = GridA.Height(); _y--; ) {
			for ( size_t _x = GridA.Width(); _x--; ) {
				NewGrid( AX + _x, AY + _y ) = GridA( _x, _y );
			}
		}

		// Copy GridB //
		for ( size_t _y = GridB.Height(); _y--; ) {
			for ( size_t _x = GridB.Width(); _x--; ) {
				NewGrid( BX + _x, BY + _y ) = GridB( _x, _y );
			}
		}
		
		// Return the grid //
		return NewGrid;
	}
	// - -------------------------------------------------------------------------------------- - //
	static inline const cGrid2D< tType > MergeBlend(
		const cGrid2D< tType >& GridA,
		const cGrid2D< tType >& GridB,
		const int GridAX,
		const int GridAY,
		const int GridBX,
		const int GridBY,
		const tType& TestValue = tType(),
		const tType& InitValue = tType()
		)
	{
		// Top corner of the grid //
		int GridX1 = GridAX;
		int GridY1 = GridAY;
		
		if ( GridX1 > GridBX )
			GridX1 = GridBX;
		if ( GridY1 > GridBY )
			GridY1 = GridBY;

			
		// Bottom corner of the grid //
		int GridX2 = GridAX + GridA.Width();
		int GridY2 = GridAY + GridA.Height();
		
		if ( GridX2 < (int)(GridBX + GridB.Width()) )
			GridX2 = GridBX + GridB.Width();
		if ( GridY2 < (int)(GridBY + GridB.Height()) )
			GridY2 = GridBY + GridB.Height();

		
		// Calculate the dimensions //
		int Width = GridX2 - GridX1;
		int Height = GridY2 - GridY1;

		
		// Calculate Start Positions //
		int AX = GridAX - GridX1;
		int AY = GridAY - GridY1;
		int BX = GridBX - GridX1;
		int BY = GridBY - GridY1;
			
		// Create a Grid to hold our copy //
		cGrid2D< tType > NewGrid( Width, Height, InitValue );

		// Copy GridA //
		for ( size_t _y = GridA.Height(); _y--; ) {
			for ( size_t _x = GridA.Width(); _x--; ) {
				if ( GridA( _x, _y ) != TestValue )
					NewGrid( AX + _x, AY + _y ) = GridA( _x, _y );
			}
		}

		// Copy GridB //
		for ( size_t _y = GridB.Height(); _y--; ) {
			for ( size_t _x = GridB.Width(); _x--; ) {
				if ( GridB( _x, _y ) != TestValue )
					NewGrid( BX + _x, BY + _y ) = GridB( _x, _y );
			}
		}
		
		// Return the grid //
		return NewGrid;
	}
	// - -------------------------------------------------------------------------------------- - //
	static inline const cGrid2D< tType > MergeBlendOnly(
		const cGrid2D< tType >& GridA,
		const cGrid2D< tType >& GridB,
		const int GridAX,
		const int GridAY,
		const int GridBX,
		const int GridBY,
		const tType& TestValue = tType(),
		const tType& InitValue = tType()
		)
	{
		// Top corner of the grid //
		int GridX1 = GridAX;
		int GridY1 = GridAY;
		
		if ( GridX1 > GridBX )
			GridX1 = GridBX;
		if ( GridY1 > GridBY )
			GridY1 = GridBY;

			
		// Bottom corner of the grid //
		int GridX2 = GridAX + GridA.Width();
		int GridY2 = GridAY + GridA.Height();
		
		if ( GridX2 < (int)(GridBX + GridB.Width()) )
			GridX2 = GridBX + GridB.Width();
		if ( GridY2 < (int)(GridBY + GridB.Height()) )
			GridY2 = GridBY + GridB.Height();

		
		// Calculate the dimensions //
		int Width = GridX2 - GridX1;
		int Height = GridY2 - GridY1;

		
		// Calculate Start Positions //
		int AX = GridAX - GridX1;
		int AY = GridAY - GridY1;
		int BX = GridBX - GridX1;
		int BY = GridBY - GridY1;
			
		// Create a Grid to hold our copy //
		cGrid2D< tType > NewGrid( Width, Height, InitValue );

		// Copy GridA //
		for ( size_t _y = GridA.Height(); _y--; ) {
			for ( size_t _x = GridA.Width(); _x--; ) {
				if ( GridA( _x, _y ) == TestValue )
					NewGrid( AX + _x, AY + _y ) = GridA( _x, _y );
			}
		}

		// Copy GridB //
		for ( size_t _y = GridB.Height(); _y--; ) {
			for ( size_t _x = GridB.Width(); _x--; ) {
				if ( GridB( _x, _y ) == TestValue )
					NewGrid( BX + _x, BY + _y ) = GridB( _x, _y );
			}
		}
		
		// Return the grid //
		return NewGrid;
	}
	// - -------------------------------------------------------------------------------------- - //
	static inline const cGrid2D< tType > MergeBlendOnlyMask(
		const cGrid2D< tType >& GridA,
		const cGrid2D< tType >& GridB,
		const int GridAX,
		const int GridAY,
		const int GridBX,
		const int GridBY,
		const tType& TestValue = tType(),
		const tType& MaskValue = tType(),
		const tType& InitValue = tType()
		)
	{
		// Top corner of the grid //
		int GridX1 = GridAX;
		int GridY1 = GridAY;
		
		if ( GridX1 > GridBX )
			GridX1 = GridBX;
		if ( GridY1 > GridBY )
			GridY1 = GridBY;

			
		// Bottom corner of the grid //
		int GridX2 = GridAX + GridA.Width();
		int GridY2 = GridAY + GridA.Height();
		
		if ( GridX2 < (int)(GridBX + GridB.Width()) )
			GridX2 = GridBX + GridB.Width();
		if ( GridY2 < (int)(GridBY + GridB.Height()) )
			GridY2 = GridBY + GridB.Height();

		
		// Calculate the dimensions //
		int Width = GridX2 - GridX1;
		int Height = GridY2 - GridY1;

		
		// Calculate Start Positions //
		int AX = GridAX - GridX1;
		int AY = GridAY - GridY1;
		int BX = GridBX - GridX1;
		int BY = GridBY - GridY1;
			
		// Create a Grid to hold our copy //
		cGrid2D< tType > NewGrid( Width, Height, InitValue );

		// Copy GridA //
		for ( size_t _y = GridA.Height(); _y--; ) {
			for ( size_t _x = GridA.Width(); _x--; ) {
				if ( GridA( _x, _y ) == TestValue )
					NewGrid( AX + _x, AY + _y ) = MaskValue;
			}
		}

		// Copy GridB //
		for ( size_t _y = GridB.Height(); _y--; ) {
			for ( size_t _x = GridB.Width(); _x--; ) {
				if ( GridB( _x, _y ) == TestValue )
					NewGrid( BX + _x, BY + _y ) = MaskValue;
			}
		}
		
		// Return the grid //
		return NewGrid;
	}
	// - -------------------------------------------------------------------------------------- - //
	static inline const cGrid2D< tType > MergeBlendMask(
		const cGrid2D< tType >& GridA,
		const cGrid2D< tType >& GridB,
		const int GridAX,
		const int GridAY,
		const int GridBX,
		const int GridBY,
		const tType& TestValue = tType(),
		const tType& MaskValue = tType(),
		const tType& InitValue = tType()
		)
	{
		// Top corner of the grid //
		int GridX1 = GridAX;
		int GridY1 = GridAY;
		
		if ( GridX1 > GridBX )
			GridX1 = GridBX;
		if ( GridY1 > GridBY )
			GridY1 = GridBY;

			
		// Bottom corner of the grid //
		int GridX2 = GridAX + GridA.Width();
		int GridY2 = GridAY + GridA.Height();
		
		if ( GridX2 < (int)(GridBX + GridB.Width()) )
			GridX2 = GridBX + GridB.Width();
		if ( GridY2 < (int)(GridBY + GridB.Height()) )
			GridY2 = GridBY + GridB.Height();

		
		// Calculate the dimensions //
		int Width = GridX2 - GridX1;
		int Height = GridY2 - GridY1;

		
		// Calculate Start Positions //
		int AX = GridAX - GridX1;
		int AY = GridAY - GridY1;
		int BX = GridBX - GridX1;
		int BY = GridBY - GridY1;
			
		// Create a Grid to hold our copy //
		cGrid2D< tType > NewGrid( Width, Height, InitValue );

		// Copy GridA //
		for ( size_t _y = GridA.Height(); _y--; ) {
			for ( size_t _x = GridA.Width(); _x--; ) {
				if ( GridA( _x, _y ) != TestValue )
					NewGrid( AX + _x, AY + _y ) = MaskValue;
			}
		}

		// Copy GridB //
		for ( size_t _y = GridB.Height(); _y--; ) {
			for ( size_t _x = GridB.Width(); _x--; ) {
				if ( GridB( _x, _y ) != TestValue )
					NewGrid( BX + _x, BY + _y ) = MaskValue;
			}
		}
		
		// Return the grid //
		return NewGrid;
	}
	// - -------------------------------------------------------------------------------------- - //
	static inline const cGrid2D< tType > RotateCW( const cGrid2D< tType >& Src ) {
		cGrid2D< tType > NewGrid( Src.Height(), Src.Width() );
		
		size_t SrcHeight = Src.Height();
		for ( size_t _y = SrcHeight; _y--; ) {
			for ( size_t _x = Src.Width(); _x--; ) {
				NewGrid( (SrcHeight-1)-_y, _x ) = Src( _x, _y );
			}
		}		
		
		return NewGrid;
	}
	// - -------------------------------------------------------------------------------------- - //
	static inline const cGrid2D< tType > RotateCCW( const cGrid2D< tType >& Src ) {
		cGrid2D< tType > NewGrid( Src.Height(), Src.Width() );
		
		size_t SrcWidth = Src.Width();
		for ( size_t _y = Src.Height(); _y--; ) {
			for ( size_t _x = SrcWidth; _x--; ) {
				NewGrid( _y, (SrcWidth-1)-_x ) = Src( _x, _y );
			}
		}		
		
		return NewGrid;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const cGrid2D< tType > RotateCW( ) {
		return RotateCW( *this );
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const cGrid2D< tType > RotateCCW( ) {
		return RotateCCW( *this );
	}
	// - -------------------------------------------------------------------------------------- - //
	static inline const cGrid2D< tType > FlipX( const cGrid2D< tType >& Src ) {
		cGrid2D< tType > NewGrid( Src.Width(), Src.Height() );
		
		size_t SrcWidth = Src.Width();
		size_t SrcHeight = Src.Height();
		for ( size_t _y = SrcHeight; _y--; ) {
			for ( size_t _x = SrcWidth; _x--; ) {
				NewGrid( (SrcWidth-1)-_x, _y ) = Src( _x, _y );
			}
		}		
		
		return NewGrid;		
	}
	// - -------------------------------------------------------------------------------------- - //
	static inline const cGrid2D< tType > FlipY( const cGrid2D< tType >& Src ) {
		cGrid2D< tType > NewGrid( Src.Width(), Src.Height() );
		
		size_t SrcWidth = Src.Width();
		size_t SrcHeight = Src.Height();
		for ( size_t _y = SrcHeight; _y--; ) {
			for ( size_t _x = SrcWidth; _x--; ) {
				NewGrid( _x, (SrcHeight-1)-_y ) = Src( _x, _y );
			}
		}		
		
		return NewGrid;		
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const cGrid2D< tType > FlipX( ) {
		return FlipX( *this );
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const cGrid2D< tType > FlipY( ) {
		return FlipY( *this );
	}
	// - -------------------------------------------------------------------------------------- - //	

	// - -------------------------------------------------------------------------------------- - //	
	inline const size_t TrimX1( const tType& Zero = tType() ) const {
		size_t x1 = 0;
		
		bool BlockFound = false;
		for ( size_t _x = 0; _x < Width(); _x++ ) {
			x1 = _x;
			// For every item in the vertical row //
			for ( size_t _y = Height(); _y--; ) {
				// Test if it's not our zero //
				if ( operator()( _x, _y ) != Zero )
					BlockFound = true;
			}
			// If a block was found, bail from this //
			if ( BlockFound )
				break;
		}
		
		return x1;
	}
	// - -------------------------------------------------------------------------------------- - //	
	inline const size_t TrimY1( const tType& Zero = tType() ) const {
		size_t y1 = 0;
		
		bool BlockFound = false;
		for ( size_t _y = 0; _y < Height(); _y++ ) {
			y1 = _y;
			// For every item in the vertical row //
			for ( size_t _x = Width(); _x--; ) {
				// Test if it's not our zero //
				if ( operator()( _x, _y ) != Zero )
					BlockFound = true;
			}
			// If a block was found, bail from this //
			if ( BlockFound )
				break;
		}
		
		return y1;
	}
	// - -------------------------------------------------------------------------------------- - //	
	inline const size_t TrimX2( const tType& Zero = tType() ) const {
		size_t x2 = 0;
		
		bool BlockFound = false;
		for ( int _x = Width() - 1; _x >= 0; _x-- ) {
			x2 = _x;
			// For every item in the vertical row //
			for ( size_t _y = Height(); _y--; ) {
				// Test if it's not our zero //
				if ( operator()( _x, _y ) != Zero )
					BlockFound = true;
			}
			// If a block was found, bail from this //
			if ( BlockFound )
				break;
		}
		
		return x2;
	}
	// - -------------------------------------------------------------------------------------- - //	
	inline const size_t TrimY2( const tType& Zero = tType() ) const {
		size_t y2 = 0;
		
		bool BlockFound = false;
		for ( int _y = Height() - 1; _y >= 0; _y-- ) {
			y2 = _y;
			// For every item in the vertical row //
			for ( int _x = Width(); _x--; ) {
				// Test if it's not our zero //
				if ( operator()( _x, _y ) != Zero )
					BlockFound = true;
			}
			// If a block was found, bail from this //
			if ( BlockFound )
				break;
		}
		
		return y2;
	}
	// - -------------------------------------------------------------------------------------- - //	
	static inline const cGrid2D< tType > Trim( const cGrid2D< tType >& Src, const tType& Zero = tType() ) {
		size_t x1 = Src.TrimX1();
		size_t y1 = Src.TrimY1();
		size_t x2 = Src.TrimX2();
		size_t y2 = Src.TrimY2();

		size_t NewWidth = x2 + 1 - x1;
		size_t NewHeight = y2 + 1 - y1;
	
		return Copy( Src, NewWidth, NewHeight, x1, y1, 0, 0 );
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const cGrid2D< tType > Trim( const tType& Zero = tType() ) {
		return Trim( *this, Zero );
	}
	// - -------------------------------------------------------------------------------------- - //	

	// - -------------------------------------------------------------------------------------- - //	
	// NOTE: This function might not be needed, but was easy enough to write after all //
	// - -------------------------------------------------------------------------------------- - //	
	static inline const cGrid2D< tType > Crop( const cGrid2D< tType >& Src, const size_t x1, const size_t y1, const size_t x2, const size_t y2 ) {
		size_t NewWidth = Src.ClipX( x2 ) + 1 - Src.ClipX( x1 );
		size_t NewHeight = Src.ClipY( y2 ) + 1 - Src.ClipY( y1 );
		
		if ( x2 < x1 )
			NewWidth = 1;
		
		if ( y2 < y1 )
			NewHeight = 1; 
	
		return Copy( Src, NewWidth, NewHeight, Src.ClipX( x1 ), Src.ClipY( y1 ), 0, 0 );
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const cGrid2D< tType > Crop( const size_t x1, const size_t y1, const size_t x2, const size_t y2 ) {	
		return Crop( *this, x1, y1, x2, y2 );
	}
	// - -------------------------------------------------------------------------------------- - //
		
public:
	// - -------------------------------------------------------------------------------------- - //
	inline void Resize( const size_t NewWidth, const size_t NewHeight, const tType& InitValue = tType() ) {
		ResizeCenter( NewWidth, NewHeight, InitValue );
	}
	// - -------------------------------------------------------------------------------------- - //
	inline void ResizeCenter( const size_t NewWidth, const size_t NewHeight, const tType& InitValue = tType() ) {
		int SrcStartX;
		int DestStartX;

		// Center the X //
		if ( NewWidth > Width() ) {
			SrcStartX = 0;
			DestStartX = (NewWidth - Width()) >> 1;
		}
		else {
			SrcStartX = (Width() - NewWidth) >> 1;
			DestStartX = 0;
		}
		
		
		int SrcStartY;
		int DestStartY;

		// Center the Y //
		if ( NewHeight > Height() ) {
			SrcStartY = 0;
			DestStartY = (NewHeight - Height()) >> 1;
		}
		else {
			SrcStartY = (Height() - NewHeight) >> 1;
			DestStartY = 0;
		}
		
		// Copy the data and set the new dimensions //
		SetData( CopyData( *this, NewWidth, NewHeight, SrcStartX, SrcStartY, DestStartX, DestStartY, InitValue ) );
		_w = NewWidth;
		_h = NewHeight;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline void ResizeAlign( const size_t NewWidth, const size_t NewHeight, const int XAlign, const int YAlign, const tType& InitValue = tType() ) {
		int SrcStartX;
		int DestStartX;

		// Align the X Axis //
		if ( XAlign == 0 ) {
			// Center the X //
			if ( NewWidth > Width() ) {
				SrcStartX = 0;
				DestStartX = (NewWidth - Width()) >> 1;
			}
			else {
				SrcStartX = (Width() - NewWidth) >> 1;
				DestStartX = 0;
			}
		}
		else if ( XAlign < 0 ) {
			// Left Align the Positions //
			SrcStartX = 0;
			DestStartX = 0;
		}
		else if ( XAlign > 0 ) {
			// Right Align the Positions //
			if ( NewWidth > Width() ) {
				SrcStartX = 0;
				DestStartX = (NewWidth - Width());
			}
			else {
				SrcStartX = (Width() - NewWidth);
				DestStartX = 0;
			}			
		}
		
		
		int SrcStartY;
		int DestStartY;

		// Align the Y Axis //
		if ( YAlign == 0 ) {
			// Center the Y //
			if ( NewHeight > Height() ) {
				SrcStartY = 0;
				DestStartY = (NewHeight - Height()) >> 1;
			}
			else {
				SrcStartY = (Height() - NewHeight) >> 1;
				DestStartY = 0;
			}
		}
		else if ( YAlign < 0 ) {
			// Left Align the Positions //
			SrcStartY = 0;
			DestStartY = 0;
		}
		else if ( YAlign > 0 ) {
			// Right Align the Positions //
			if ( NewHeight > Height() ) {
				SrcStartY = 0;
				DestStartY = (NewHeight - Height());
			}
			else {
				SrcStartY = (Height() - NewHeight);
				DestStartY = 0;
			}	
		}		
		
		// Copy the data and set the new dimensions //
		SetData( CopyData( *this, NewWidth, NewHeight, SrcStartX, SrcStartY, DestStartX, DestStartY, InitValue ) );
		_w = NewWidth;
		_h = NewHeight;
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	inline void SetWidth( const size_t NewWidth, const tType& InitValue = tType() ) {
		SetWidthCenter( NewWidth, InitValue );
	}
	// - -------------------------------------------------------------------------------------- - //
	inline void SetWidthCenter( const size_t NewWidth, const tType& InitValue = tType() ) {
		int SrcStart;
		int DestStart;
		
		// Center the Positions //
		if ( NewWidth > Width() ) {
			SrcStart = 0;
			DestStart = (NewWidth - Width()) >> 1;
		}
		else {
			SrcStart = (Width() - NewWidth) >> 1;
			DestStart = 0;
		}
		
		// Copy the data and set the new dimensions //
		SetData( CopyData( *this, NewWidth, Height(), SrcStart, 0, DestStart, 0, InitValue ) );
		_w = NewWidth;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline void SetWidthLeft( const size_t NewWidth, const tType& InitValue = tType() ) {
		int SrcStart;
		int DestStart;
		
		// Left Align the Positions //
		SrcStart = 0;
		DestStart = 0;

		
		// Copy the data and set the new dimensions //
		SetData( CopyData( *this, NewWidth, Height(), SrcStart, 0, DestStart, 0, InitValue ) );
		_w = NewWidth;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline void SetWidthRight( const size_t NewWidth, const tType& InitValue = tType() ) {
		int SrcStart;
		int DestStart;
		
		// Right Align the Positions //
		if ( NewWidth > Width() ) {
			SrcStart = 0;
			DestStart = (NewWidth - Width());
		}
		else {
			SrcStart = (Width() - NewWidth);
			DestStart = 0;
		}
		
		// Copy the data and set the new dimensions //
		SetData( CopyData( *this, NewWidth, Height(), SrcStart, 0, DestStart, 0, InitValue ) );
		_w = NewWidth;
	}
	// - -------------------------------------------------------------------------------------- - //
	

	// - -------------------------------------------------------------------------------------- - //
	inline void SetHeight( const size_t NewHeight, const tType& InitValue = tType() ) {
		SetHeightCenter( NewHeight, InitValue );
	}
	// - -------------------------------------------------------------------------------------- - //
	inline void SetHeightCenter( const size_t NewHeight, const tType& InitValue = tType() ) {
		int SrcStart;
		int DestStart;
		
		// Center the Positions //
		if ( NewHeight > Height() ) {
			SrcStart = 0;
			DestStart = (NewHeight - Height()) >> 1;
		}
		else {
			SrcStart = (Height() - NewHeight) >> 1;
			DestStart = 0;
		}
		
		// Copy the data and set the new dimensions //
		SetData( CopyData( *this, Width(), NewHeight, 0, SrcStart, 0, DestStart, InitValue ) );
		_h = NewHeight;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline void SetHeightTop( const size_t NewHeight, const tType& InitValue = tType() ) {
		int SrcStart;
		int DestStart;
		
		// Left Align the Positions //
		SrcStart = 0;
		DestStart = 0;

		
		// Copy the data and set the new dimensions //
		SetData( CopyData( *this, Width(), NewHeight, 0, SrcStart, 0, DestStart, InitValue ) );
		_h = NewHeight;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline void SetHeightBottom( const size_t NewHeight, const tType& InitValue = tType() ) {
		int SrcStart;
		int DestStart;
		
		// Right Align the Positions //
		if ( NewHeight > Height() ) {
			SrcStart = 0;
			DestStart = (NewHeight - Height());
		}
		else {
			SrcStart = (Height() - NewHeight);
			DestStart = 0;
		}
		
		// Copy the data and set the new dimensions //
		SetData( CopyData( *this, Width(), NewHeight, 0, SrcStart, 0, DestStart, InitValue ) );
		_h = NewHeight;
	}
	// - -------------------------------------------------------------------------------------- - //
public:
	// - -------------------------------------------------------------------------------------- - //
	// Return the number of instances of a value //
	inline const size_t Count( const tType& Value ) const {
		size_t CurrentCount = 0;

		for ( size_t _y = Height(); _y--; ) {
			for ( size_t _x = Width(); _x--; ) {
				if ( operator()( _x, _y ) == Value )
					CurrentCount++;
			}
		}	
		
		return CurrentCount;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Return the number of non instances of a value //
	inline const size_t CountNot( const tType& Value ) const {
		size_t CurrentCount = 0;

		for ( size_t _y = Height(); _y--; ) {
			for ( size_t _x = Width(); _x--; ) {
				if ( operator()( _x, _y ) != Value )
					CurrentCount++;
			}
		}	
		
		return CurrentCount;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Return the number of non instances of a value //
	inline const size_t CountGT( const tType& Value ) const {
		size_t CurrentCount = 0;

		for ( size_t _y = Height(); _y--; ) {
			for ( size_t _x = Width(); _x--; ) {
				if ( operator()( _x, _y ) > Value )
					CurrentCount++;
			}
		}	
		
		return CurrentCount;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Return the number of non instances of a value //
	inline const size_t CountLT( const tType& Value ) const {
		size_t CurrentCount = 0;

		for ( size_t _y = Height(); _y--; ) {
			for ( size_t _x = Width(); _x--; ) {
				if ( operator()( _x, _y ) < Value )
					CurrentCount++;
			}
		}	
		
		return CurrentCount;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Return the number of non instances of a value //
	inline const size_t CountGTE( const tType& Value ) const {
		size_t CurrentCount = 0;

		for ( size_t _y = Height(); _y--; ) {
			for ( size_t _x = Width(); _x--; ) {
				if ( operator()( _x, _y ) >= Value )
					CurrentCount++;
			}
		}	
		
		return CurrentCount;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Return the number of non instances of a value //
	inline const size_t CountLTE( const tType& Value ) const {
		size_t CurrentCount = 0;

		for ( size_t _y = Height(); _y--; ) {
			for ( size_t _x = Width(); _x--; ) {
				if ( operator()( _x, _y ) <= Value )
					CurrentCount++;
			}
		}	
		
		return CurrentCount;
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Count the number of instances of tiles equal to the tile we point to. //
	inline const size_t CountAdjacentX( int x, int y ) const {
		size_t CurrentCount = 1;
		x = ClipX( x );
		y = ClipY( y );
		tType Value = operator()( x, y );

		for ( int _x = x; _x-- > 0; ) {
			if ( operator()( _x, y ) == Value )
				CurrentCount++;
			else
				break;
		}

		for ( int _x = x; ++_x < Width(); ) {
			if ( operator()( _x, y ) == Value )
				CurrentCount++;
			else
				break;
		}
		
		return CurrentCount;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Count the number of instances of tiles equal to the tile we point to. //
	inline const size_t CountAdjacentY( int x, int y ) const {
		size_t CurrentCount = 1;
		x = ClipX( x );
		y = ClipY( y );
		tType Value = operator()( x, y );

		for ( int _y = y; _y-- > 0; ) {
			if ( operator()( x, _y ) == Value )
				CurrentCount++;
			else
				break;
		}

		for ( int _y = y; ++_y < Height(); ) {
			if ( operator()( x, _y ) == Value )
				CurrentCount++;
			else
				break;
		}
		
		return CurrentCount;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Count the number of instances of tiles equal to the tile we point to. //
	inline const size_t CountAdjacentX( int x, int y, const tType& Value ) const  {
		if ( Clip( x, y ) != Value )
			return 0;
		else
			return CountAdjacentX( x, y );
	}
	// - -------------------------------------------------------------------------------------- - //
	// Count the number of instances of tiles equal to the tile we point to. //
	inline const size_t CountAdjacentY( int x, int y, const tType& Value ) const {
		if ( Clip( x, y ) != Value )
			return 0;
		else
			return CountAdjacentY( x, y );
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Clear the number of instances of tiles equal to the tile we point to. //
	inline const size_t ClearAdjacentX( int x, int y ) const {
		size_t CurrentCount = 1;
		x = ClipX( x );
		y = ClipY( y );
		tType Value = operator()( x, y );
		operator()( x, y ) = 0;

		for ( int _x = x; _x-- > 0; ) {
			if ( operator()( _x, y ) == Value ) {
				operator()( _x, y ) = 0;
				CurrentCount++;
			}
			else
				break;
		}

		for ( int _x = x; ++_x < Width(); ) {
			if ( operator()( _x, y ) == Value ) {
				operator()( _x, y ) = 0;
				CurrentCount++;
			}
			else
				break;
		}
		
		return CurrentCount;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Clear the number of instances of tiles equal to the tile we point to. //
	inline const size_t ClearAdjacentY( int x, int y ) const {
		size_t CurrentCount = 1;
		x = ClipX( x );
		y = ClipY( y );
		tType Value = operator()( x, y );
		operator()( x, y ) = 0; 

		for ( int _y = y; _y-- > 0; ) {
			if ( operator()( x, _y ) == Value ) {
				operator()( x, _y ) = 0;
				CurrentCount++;
			}
			else
				break;
		}

		for ( int _y = y; ++_y < Height(); ) {
			if ( operator()( x, _y ) == Value ) {
				operator()( x, _y ) = 0;
				CurrentCount++;
			}
			else
				break;
		}
		
		return CurrentCount;
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Count the number of instances of tiles on a line //
	inline const size_t CountLineX( int y, const tType& Value ) const {
		size_t CurrentCount = 0;
		y = ClipY( y );

		for ( int _x = Width(); _x--; ) {
			if ( operator()( _x, y ) == Value )
				CurrentCount++;
		}

		return CurrentCount;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Count the number of instances of tiles on a line //
	inline const size_t CountLineY( int x, const tType& Value ) const {
		size_t CurrentCount = 0;
		x = ClipY( x );

		for ( int _y = Height(); _y--; ) {
			if ( operator()( x, _y ) == Value )
				CurrentCount++;
		}

		return CurrentCount;
	}
	// - -------------------------------------------------------------------------------------- - //


	// - -------------------------------------------------------------------------------------- - //
	// Return the "x index" of the first occurence of Value starting at point x,y //
	inline const int FirstX( int x, int y, const tType& Value ) const {
		x = ClipX( x );
		y = ClipY( y );
		for ( ; x < Width(); x++ ) {
			if ( operator()( x, y ) == Value )
				return x;
		}
		return -1;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Return the "y index" of the first occurence of Value starting at point x,y //
	inline const int FirstY( int x, int y, const tType& Value ) const {
		x = ClipX( x );
		y = ClipY( y );
		for ( ; y < Height(); y++ ) {
			if ( operator()( x, y ) == Value )
				return y;
		}
		return -1;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Return the "x index" of the last occurence of Value starting at point x,y //
	inline const int LastX( int x, int y, const tType& Value ) const {
		x = ClipX( x );
		y = ClipY( y );
		for ( ; x--; ) {
			if ( operator()( x, y ) == Value )
				return x;
		}
		return -1;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Return the "y index" of the last occurence of Value starting at point x,y //
	inline const int LastY( int x, int y, const tType& Value ) const {
		x = ClipX( x );
		y = ClipY( y );
		for ( ; y--; ) {
			if ( operator()( x, y ) == Value )
				return x;
		}
		return -1;
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// NOTE: The "Not" may be confusing, since it's Not Equality, not Not X (i.e. Y). //
	// - -------------------------------------------------------------------------------------- - //
	// Return the "x index" of the first non occurence of Value starting at point x,y //
	inline const int FirstNotX( int x, int y, const tType& Value ) const {
		x = ClipX( x );
		y = ClipY( y );
		for ( ; x < Width(); x++ ) {
			if ( operator()( x, y ) != Value )
				return x;
		}
		return -1;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Return the "y index" of the first non occurence of Value starting at point x,y //
	inline const int FirstNotY( int x, int y, const tType& Value ) const {
		x = ClipX( x );
		y = ClipY( y );
		for ( ; y < Height(); y++ ) {
			if ( operator()( x, y ) != Value )
				return y;
		}
		return -1;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Return the "x index" of the last non occurence of Value starting at point x,y //
	inline const int LastNotX( int x, int y, const tType& Value ) const {
		x = ClipX( x );
		y = ClipY( y );
		for ( ; x--; ) {
			if ( operator()( x, y ) != Value )
				return x;
		}
		return -1;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Return the "y index" of the last non occurence of Value starting at point x,y //
	inline const int LastNotY( int x, int y, const tType& Value ) const {
		x = ClipX( x );
		y = ClipY( y );
		for ( ; y--; ) {
			if ( operator()( x, y ) != Value )
				return x;
		}
		return -1;
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// NOTE: Should these be called FirstXOnLine(), etc?
	// - -------------------------------------------------------------------------------------- - //
	// Return the "x index" of the first occurence of Value on a line //
	inline const int FirstLineX( int y, const tType& Value ) const {
		return FirstX( 0, y, Value );
	}
	// - -------------------------------------------------------------------------------------- - //
	// Return the "y index" of the first occurence of Value on a line //
	inline const int FirstLineY( int x, const tType& Value ) const {
		return FirstY( x, 0, Value );
	}
	// - -------------------------------------------------------------------------------------- - //
	// Return the "x index" of the last occurence of Value on a line //
	inline const int LastLineX( int y, const tType& Value ) const {
		// NOTE: 'cause LastX does clipping, you could technically pass Width directly // 
		return LastX( Width() - 1, y, Value );
	}
	// - -------------------------------------------------------------------------------------- - //
	// Return the "y index" of the last occurence of Value on a line //
	inline const int LastLineY( int x, const tType& Value ) const {
		// NOTE: 'cause LastY does clipping, you could technically pass Height directly //
		return LastY( x, Height() - 1, Value );
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// NOTE: The "Not" may be confusing, since it's Not Equality, not Not X (i.e. Y). //
	// - -------------------------------------------------------------------------------------- - //
	// Return the "x index" of the first occurence of not Value on a line //
	inline const int FirstLineNotX( int y, const tType& Value ) const {
		return FirstNotX( 0, y, Value );
	}
	// - -------------------------------------------------------------------------------------- - //
	// Return the "y index" of the first occurence of not Value on a line //
	inline const int FirstLineNotY( int x, const tType& Value ) const {
		return FirstNotY( x, 0, Value );
	}
	// - -------------------------------------------------------------------------------------- - //
	// Return the "x index" of the last occurence of not Value on a line //
	inline const int LastLineNotX( int y, const tType& Value ) const {
		// NOTE: 'cause LastX does clipping, you could technically pass Width directly // 
		return LastNotX( Width() - 1, y, Value );
	}
	// - -------------------------------------------------------------------------------------- - //
	// Return the "y index" of the last occurence of not Value on a line //
	inline const int LastLineNotY( int x, const tType& Value ) const {
		// NOTE: 'cause LastY does clipping, you could technically pass Height directly //
		return LastNotY( x, Height() - 1, Value );
	}
	// - -------------------------------------------------------------------------------------- - //

public:
	// - -------------------------------------------------------------------------------------- - //
	// Generate a grid of values for how far away each found value is from the start //
	inline const cGrid2D<int> GenerateAdjacentXAdjacencyGrid( int x, int y, const tType& Value ) const {
		cGrid2D<int> NewGrid( Width(), Height() );
		
		x = ClipX( x );
		y = ClipY( y );
		
		if ( operator()( x, y ) != Value )
			return NewGrid;
		
		NewGrid( x, y ) = 1;
		
		{
			size_t Distance = 1;
			for ( int _x = x; _x-- > 0; ) {
				if ( operator()( _x, y ) == Value ) {
					Distance++;
					
					NewGrid( _x, y ) = Distance;
				}
				else
					break;
			}
		}

		{
			size_t Distance = 1;
			for ( int _x = x; ++_x < Width(); ) {
				if ( operator()( _x, y ) == Value ) {
					Distance++;
					
					NewGrid( _x, y ) = Distance;
				}
				else
					break;
			}
		}
		
		return NewGrid;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Generate a grid of values for how far away each found value is from the start //
	inline const cGrid2D<int> GenerateAdjacentYAdjacencyGrid( int x, int y, const tType& Value ) const {
		cGrid2D<int> NewGrid( Width(), Height() );
		
		x = ClipX( x );
		y = ClipY( y );
		
		if ( operator()( x, y ) != Value )
			return NewGrid;
		
		NewGrid( x, y ) = 1;
		
		{
			size_t Distance = 1;
			for ( int _y = y; _y-- > 0; ) {
				if ( operator()( x, _y ) == Value ) {
					Distance++;
					
					NewGrid( x, _y ) = Distance;
				}
				else
					break;
			}
		}

		{
			size_t Distance = 1;
			for ( int _y = y; ++_y < Height(); ) {
				if ( operator()( x, _y ) == Value ) {
					Distance++;
					
					NewGrid( x, _y ) = Distance;
				}
				else
					break;
			}
		}
		
		return NewGrid;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const cGrid2D<int> GenerateAdjacentXAdjacencyGrid( const int x, const int y ) const {
		return GenerateAdjacentXAdjacencyGrid( x, y, Clip( x, y ) );
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const cGrid2D<int> GenerateAdjacentYAdjacencyGrid( const int x, const int y ) const {
		return GenerateAdjacentYAdjacencyGrid( x, y, Clip( x, y ) );
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// In the case of rows and columns, an Adjacency Grid is exactly the same as a Distance Grid //
	// - -------------------------------------------------------------------------------------- - //
	inline const cGrid2D<int> GenerateAdjacentXDistanceGrid( const int x, const int y, const tType& Value ) const {
		return GenerateAdjacentXAdjacencyGrid( x, y, Value );
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const cGrid2D<int> GenerateAdjacentYDistanceGrid( const int x, const int y, const tType& Value ) const {
		return GenerateAdjacentYAdjacencyGrid( x, y, Value );
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const cGrid2D<int> GenerateAdjacentXDistanceGrid( const int x, const int y ) const {
		return GenerateAdjacentXAdjacencyGrid( x, y );
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const cGrid2D<int> GenerateAdjacentYDistanceGrid( const int x, const int y ) const {
		return GenerateAdjacentYAdjacencyGrid( x, y );
	}
	// - -------------------------------------------------------------------------------------- - //

public:
	// Drawing Code //		
	//DrawRadiusRect
	//DrawRadiusFilledRect
	
	// Add a function for generating a mask from a Grid.  I.e. all tiles that match a pattern, or //
	//   dont match a pattern.  //
	// Perhaps have a distinct MaskGrid type (cGrid2D<int>), and functions for generating either //
	//   a MaskGrid or a regular Grid copy. //
	
	// Add a function for testing "per pixel collision" style for contacts between two placed //
	//   overlapping grids.  This is needed (preferred) for a tetris move verification function. //
	
	// Add a function for shifting the contents of a grid //
	
	// Add equivalent functions for Adjacency searching (GenerateAdjacentDistanceGrid, ...) //


	inline void _DrawHLine( const int x, const int y, const int w, const tType& Value = tType() ) {
		for ( size_t idx = x; idx < x+w; idx++ ) {
			operator()(idx,y) = Value;
		}
	}
	inline void DrawHLine( int x, const int y, int w, const tType& Value = tType() ) {
		if ( y < 0 )
			return;
		else if ( y >= Height() )
			return;
			
		if ( x < 0 ) {
			w += x;
			x = 0;
		}		
		else if ( x >= Width() )
			return;
		
		if ( w < 1 )
			return;
		else if ( x+w >= Width() )
			w = Width()-x;
		
		_DrawHLine( x, y, w, Value );
	}


	inline void _DrawVLine( const int x, const int y, const int h, const tType& Value = tType() ) {
		for ( size_t idx = y; idx < y+h; idx++ ) {
			operator()(x,idx) = Value;
		}
	}
	inline void DrawVLine( const int x, int y, int h, const tType& Value = tType() ) {
		if ( x < 0 )
			return;
		else if ( x >= Width() )
			return;
			
		if ( y < 0 ) {
			h += y;
			y = 0;
		}		
		else if ( y >= Height() )
			return;

		if ( h < 1 )
			return;
		else if ( y+h >= Height() )
			h = Height()-y;
		
		_DrawVLine( x, y, h, Value );
	}

	inline void DrawRect( const int x, const int y, const int w, const int h, const tType& Value = tType() ) {
		DrawHLine( x, y, w, Value );
		DrawHLine( x, y-1+h, w, Value );

		DrawVLine( x, y+1, h-2, Value );
		DrawVLine( x-1+w, y+1, h-2, Value );
	}

	inline void DrawRectFill( int x, int y, int w, int h, const tType& Value = tType() ) {
		if ( x < 0 ) {
			w += x;
			x = 0;
		}
		else if ( x >= Width() )
			return;
			
		if ( y < 0 ) {
			h += y;
			y = 0;
		}		
		else if ( y >= Height() )
			return;

		if ( w < 1 )
			return;
		else if ( x+w >= Width() )
			w = Width()-x;
		
		if ( h < 1 )
			return;
		else if ( y+h >= Height() )
			h = Height()-y;

		for ( size_t idx = y; idx < y+h; idx++ ) {
			_DrawHLine( x, idx, w, Value );
		}
	}
	
	inline void DrawLine( int x1, int y1, int x2, int y2, const tType& Value = tType() ) {
		int xDiff = x2-x1;
		int yDiff = y2-y1;
		
		int SignX = 1;
		int SignY = 1;
		int xDiffABS = xDiff;
		int yDiffABS = yDiff;
		
		// Figure out the sign of xDiff //
		if ( xDiff < 0 ) {
			SignX = -1;
			xDiffABS = -xDiff;
		}

		// Figure out the sign of yDiff //
		if ( yDiff < 0 ) {
			SignY = -1;
			yDiffABS = -yDiff;
		}
		
		// Wider than Tall //
		if ( xDiffABS >= yDiffABS ) {
			// Swap if X is backwards //
			if ( x1 > x2 ) {
				int Temp = x2;
				x2 = x1;
				x1 = Temp;
				Temp = y2;
				y2 = y1;
				y1 = Temp;
				
				xDiff = -xDiff;
			}
			
			float Slope = 0;
			if ( xDiffABS != 0 ) {
				Slope = (float)yDiff / (float)xDiff;
				Slope *= SignX;
			}
			
			int StartX = 0;
			if ( x1 < 0 )
				StartX = -x1;
			else if ( x1 > Width() )
				return;

			int EndX = xDiff+1;
			if ( x2 < 0 )
				return;
			else if ( x2 > Width() )
				EndX = (xDiff) - (x2-Width());
			
			for ( size_t idx = StartX; idx < EndX; idx++ ) {
				operator()( x1 + idx, y1 + round(Slope*(float)(idx)) ) = Value;
			}
		}
		// Taller than Wide //
		else {
			// Swap if Y is backwards //
			if ( y1 > y2 ) {
				int Temp = x2;
				x2 = x1;
				x1 = Temp;
				Temp = y2;
				y2 = y1;
				y1 = Temp;
				
				yDiff = -yDiff;
			}

			float Slope = 0;
			if ( yDiffABS != 0 ) {
				Slope = (float)xDiff / (float)yDiff;
				Slope *= SignY;
			}
	
			int StartY = 0;
			if ( y1 < 0 )
				StartY = -y1;
			else if ( y1 > Height() )
				return;

			int EndY = yDiff+1;
			if ( y2 < 0 )
				return;
			else if ( y2 > Height() )
				EndY = (yDiff) - (y2-Height());
		
			for ( size_t idx = StartY; idx < EndY; idx++ ) {
				operator()( x1 + round(Slope*(float)(idx)), y1 + idx ) = Value;
			}			
		}
	}

public:
	//CanDrop( x, y, offx, offy, TestValue )
	//CanRockfordDrop( ... )
	
	//GenerateDropGrid( offx, offy, TestValue )
	//GenerateRockfordDropGrid( offx, offy, TestValue) // 1, 2, 3, where 2 is down and others diagonals //
	
	// NOTE: Standard dropping can move in large chunks safely, but rockford drops should move //
	//   individual tiles only. The reasoning for this is because with a single drop step, blocks //
	//   that are above can move in to place to cause the rockford drop logic to push a tile that //
	//   would by default come out the left to the right.  Otherwise, it'll fill up the left side //
	//   first, then the right side.  Lame.  //
	
	// - -------------------------------------------------------------------------------------- - //
	inline const int CanDrop( int x, int y, const int OffsetX = 0, const int OffsetY = 1, const tType& Value = tType() ) const {
		// Clip the incoming co-ordinates //
		x = ClipX( x );
		y = ClipY( y );
		
		// Bail if the tile is already empty //
		if ( operator()(x,y) == Value )
			return 0;
		
		// Generate and clip offset co-ordinate //
		int DownOffsetX = ClipX( x + OffsetX );
		int DownOffsetY = ClipY( y + OffsetY );
			
		// If the offset tile is our test value, then we can drop //
		return operator()( DownOffsetX, DownOffsetY ) == Value;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const int CanRockfordDrop( int x, int y, const int OffsetX = 0, const int OffsetY = 1, const tType& Value = tType() ) const {
		// Clip the incoming co-ordinates //
		x = ClipX( x );
		y = ClipY( y );
		
		// Bail if the tile is already empty //
		if ( operator()(x,y) == Value )
			return 0;
		
		// Generate and clip the immediate offset co-ordinate //
		int DownOffsetX = ClipX( x + OffsetX );
		int DownOffsetY = ClipY( y + OffsetY );
		
		// Bail if we happened to clip ourselves to the same position (i.e. on a limit) //
		if ( (DownOffsetX == x) && (DownOffsetY == y) )
			return 0;

		// Test below //
		if ( operator()( DownOffsetX, DownOffsetY ) == Value )
			return 2;

			
		// Test to the left //
		if ( Clip( x - OffsetY, y + OffsetX ) == Value ) {
			int DownX = ClipX( DownOffsetX - OffsetY );
			int DownY = ClipY( DownOffsetY + OffsetX );

			// Test below the left //
			if ( operator()( DownX, DownY ) == Value ) {
				return 1;
			}
		}
		
		// Test to the right //
		if ( Clip( x + OffsetY, y - OffsetX ) == Value ) {
			int DownX = ClipX( DownOffsetX + OffsetY );
			int DownY = ClipY( DownOffsetY - OffsetX );

			// Test below the right //
			if ( operator()( DownX, DownY ) == Value ) {
				return 3;
			}
		}

		// No drops available //
		return 0;
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	inline const int CalcDropDistance( int x, int y, int OffsetX = 0, int OffsetY = 1, const tType& Value = tType() ) const {
		// TODO: Assert the Offsets.  There should always be a 1 and a 0 or a -1 and a 0. //
		
		// Clip the incoming co-ordinates //
		x = ClipX( x );
		y = ClipY( y );
		
		// Bail if the tile is already empty //
//		if ( operator()(x,y) == Value )
//			return 0;
			
		int DropDistance = 0;
		
		{
			// The offsets determine our sweeping order, so these are our sweeping order control //
			int StartX, StartY;
			int EndX, EndY;
			int IncrementX, IncrementY;
			
			// X axis change //
			if ( OffsetX > 0 ) {
				StartX = x + OffsetX;
				EndX = Width();
				IncrementX = 1;
			}
			else if ( OffsetX < 0 ) {
				StartX = x + OffsetX;
				EndX = -1;
				IncrementX = -1;
			}
			else {
				StartX = x;
				EndX = x + 1;
				IncrementX = 1;
			}
			
			// Y axis change //
			if ( OffsetY > 0 ) {
				StartY = y + OffsetY;
				EndY = Height();
				IncrementY = 1;
			}
			else if ( OffsetY < 0 ) {
				StartY = y + OffsetY;
				EndY = -1;
				IncrementY = -1;
			}
			else {
				StartY = y;
				EndY = y + 1;
				IncrementY = 1;
			}

			// Step through 			
			for ( int _x = StartX; _x != EndX; _x += IncrementX ) {
				for ( int _y = StartY; _y != EndY; _y += IncrementY ) {
					// If the offset tile is our test value, then we can drop //
					if ( operator()( _x, _y ) == Value ) {
						DropDistance++;
					}
					else {
						// Rather than double break, I'm just going to return //
						return DropDistance;
					}
				}
			}	
		}
		
		// If we hit an end boundery, the drop distance is finished //
		return DropDistance;
	}
	// - -------------------------------------------------------------------------------------- - //
	
public:
	// - -------------------------------------------------------------------------------------- - //
	// Return a grid of all tiles that are allowed to drop //
	inline const cGrid2D<int> GenerateDropGrid( const int OffsetX = 0, const int OffsetY = 1, const tType& Value = tType() ) const {
		// Our drop grid //
		cGrid2D<int> DropGrid( Width(), Height() );
		
		for ( int x = 0; x < Width(); x++ ) {
			for ( int y = 0; y < Height(); y++ ) {
				DropGrid( x, y ) = CanDrop( x, y, OffsetX, OffsetY, Value );
			}
		}
		
		// Return the Drop Grid //
		return DropGrid;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Return a grid of all tiles that are allowed to rockford drop //
	inline const cGrid2D<int> GenerateRockfordDropGrid( const int OffsetX = 0, const int OffsetY = 1, const tType& Value = tType() ) const {
		// Our drop grid //
		cGrid2D<int> DropGrid( Width(), Height() );
		
		for ( int x = 0; x < Width(); x++ ) {
			for ( int y = 0; y < Height(); y++ ) {
				DropGrid( x, y ) = CanRockfordDrop( x, y, OffsetX, OffsetY, Value );
			}
		}
		
		// Return the Drop Grid //
		return DropGrid;
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Return a grid of all distances a tile can drop //
	inline const cGrid2D<int> GenerateDropDistanceGrid( const int OffsetX = 0, const int OffsetY = 1, const tType& Value = tType() ) const {
		// Our drop grid //
		cGrid2D<int> DropGrid( Width(), Height() );
		
		for ( int x = 0; x < Width(); x++ ) {
			for ( int y = 0; y < Height(); y++ ) {
				if ( operator()( x, y ) == 0 ) {
					DropGrid( x, y ) = 0;
				}
				else {
					DropGrid( x, y ) = CalcDropDistance( x, y, OffsetX, OffsetY, Value );
				}
			}
		}
		
		// Return the Drop Grid //
		return DropGrid;
	}
	// - -------------------------------------------------------------------------------------- - //

public:
	// - -------------------------------------------------------------------------------------- - //
	// Exchange the value of two tiles //
	inline void Swap( int x1, int y1, int x2, int y2 ) {
		x1 = ClipX( x1 );
		y1 = ClipY( y1 );
		
		x2 = ClipX( x2 );
		y2 = ClipY( y2 );
		
		tType Temp = operator()(x1,y1);
		operator()(x1,y1) = operator()(x2,y2);
		operator()(x2,y2) = Temp;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Exchange the passed value with the tile, returning the value of the tile //
	inline const tType Swap( int x1, int y1, const tType& Value ) {
		x1 = ClipX( x1 );
		y1 = ClipY( y1 );
			
		tType Temp = operator()(x1,y1);
		operator()(x1,y1) = Value;
		
		return Temp;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Exchange the passed value with the tile, returning the value of the tile //
	inline const tType Swap( int _Index, const tType& Value ) {
		tType Temp = operator[](_Index);
		operator[](_Index) = Value;
		
		return Temp;
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	inline void ApplyDrop( const int x, const int y, const int OffsetX = 0, const int OffsetY = 1 ) {
		Swap( x, y, x + OffsetX, y + OffsetY );
	}
	// - -------------------------------------------------------------------------------------- - //
	inline void ApplyDropDistance( const int x, const int y, const int Distance, const int OffsetX = 0, const int OffsetY = 1 ) {
		Swap( x, y, x + (OffsetX*Distance), y + (OffsetY*Distance) );	
	}
	// - -------------------------------------------------------------------------------------- - //
	inline void ApplyRockfordDrop( const int x, const int y, const int DropType, const int OffsetX = 0, const int OffsetY = 1 ) {
		// Left Drop //
		if ( DropType == 1 ) {
			int DownOffsetX = ClipX( x + OffsetX );
			int DownOffsetY = ClipY( y + OffsetY );
	
			Swap( x, y, DownOffsetX - OffsetY, DownOffsetY + OffsetX );
		}
		// Down Drop //
		else if ( DropType == 2 ) {
			Swap( x, y, x + OffsetX, y + OffsetY );
		}
		// Right Drop //
		else if ( DropType == 3 ) {
			int DownOffsetX = ClipX( x + OffsetX );
			int DownOffsetY = ClipY( y + OffsetY );
	
			Swap( x, y, DownOffsetX + OffsetY, DownOffsetY - OffsetX );			
		}
	}
	// - -------------------------------------------------------------------------------------- - //
	
	
	// - -------------------------------------------------------------------------------------- - //
	// NOTE: Applying a Drop or DropDistance Grid would be fine, but appling a RockfordDrop Grid //
	//   wouldn't work, since rockford logic allows 2 tiles to overlap once solving. //
	// - -------------------------------------------------------------------------------------- - //
	inline void Drop( const int OffsetX = 0, const int OffsetY = 1 ) {
		// TODO: Assert the Offsets.  There should always be a 1 and a 0 or a -1 and a 0. //

		// The offsets determine our sweeping order, so these are our sweeping order control //
		int StartX, StartY;
		int EndX, EndY;
		int IncrementX, IncrementY;
		
		// X axis change //
		if ( OffsetX <= 0 ) {
			StartX = 0;
			EndX = Width();
			IncrementX = 1;
		}
		else {
			StartX = Width() - 1;
			EndX = -1;
			IncrementX = -1;
		}
		
		// Y axis change //
		if ( OffsetY <= 0 ) {
			StartY = 0;
			EndY = Height();
			IncrementY = 1;
		}
		else 
		{
			StartY = Height() - 1;
			EndY = -1;
			IncrementY = -1;
		}
		
		// Depending on the offset, x or y should be the inner increment //
		if ( OffsetY == 0 ) {
			// Step through the Grid //
			for ( int x = StartX; x != EndX; x += IncrementX ) {
				for ( int y = StartY; y != EndY; y += IncrementY ) {
					if ( CanDrop( x, y, OffsetX, OffsetY ) )
						ApplyDrop( x, y, OffsetX, OffsetY );
				}
			}
		}
		else {
			// Step through the Grid //
			for ( int y = StartY; y != EndY; y += IncrementY ) {
				for ( int x = StartX; x != EndX; x += IncrementX ) {
					if ( CanDrop( x, y, OffsetX, OffsetY ) )
						ApplyDrop( x, y, OffsetX, OffsetY );
				}
			}
		}
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	inline void DoDropDistance( const int OffsetX = 0, const int OffsetY = 1 ) {
		// TODO: Assert the Offsets.  There should always be a 1 and a 0 or a -1 and a 0. //

		// The offsets determine our sweeping order, so these are our sweeping order control //
		int StartX, StartY;
		int EndX, EndY;
		int IncrementX, IncrementY;
		
		// X axis change //
		if ( OffsetX <= 0 ) {
			StartX = 0;
			EndX = Width();
			IncrementX = 1;
		}
		else {
			StartX = Width() - 1;
			EndX = -1;
			IncrementX = -1;
		}
		
		// Y axis change //
		if ( OffsetY <= 0 ) {
			StartY = 0;
			EndY = Height();
			IncrementY = 1;
		}
		else 
		{
			StartY = Height() - 1;
			EndY = -1;
			IncrementY = -1;
		}
		
		// Depending on the offset, x or y should be the inner increment //
		if ( OffsetY == 0 ) {
			// Step through the Grid //
			for ( int x = StartX; x != EndX; x += IncrementX ) {
				for ( int y = StartY; y != EndY; y += IncrementY ) {
					if ( int Distance = CalcDropDistance( x, y, OffsetX, OffsetY ) )
						ApplyDropDistance( x, y, Distance, OffsetX, OffsetY );
				}
			}
		}
		else {
			// Step through the Grid //
			for ( int y = StartY; y != EndY; y += IncrementY ) {
				for ( int x = StartX; x != EndX; x += IncrementX ) {
					if ( int Distance = CalcDropDistance( x, y, OffsetX, OffsetY ) )
						ApplyDropDistance( x, y, Distance, OffsetX, OffsetY );
				}
			}
		}
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	inline void RockfordDrop( const int OffsetX = 0, const int OffsetY = 1 ) {
		// TODO: Assert the Offsets.  There should always be a 1 and a 0 or a -1 and a 0. //

		// The offsets determine our sweeping order, so these are our sweeping order control //
		int StartX, StartY;
		int EndX, EndY;
		int IncrementX, IncrementY;
		
		// X axis change //
		if ( OffsetX <= 0 ) {
			StartX = 0;
			EndX = Width();
			IncrementX = 1;
		}
		else {
			StartX = Width() - 1;
			EndX = -1;
			IncrementX = -1;
		}
		
		// Y axis change //
		if ( OffsetY <= 0 ) {
			StartY = 0;
			EndY = Height();
			IncrementY = 1;
		}
		else 
		{
			StartY = Height() - 1;
			EndY = -1;
			IncrementY = -1;
		}
		
		// Depending on the offset, x or y should be the inner increment //
		if ( OffsetY == 0 ) {
			// Step through the Grid //
			for ( int x = StartX; x != EndX; x += IncrementX ) {
				for ( int y = StartY; y != EndY; y += IncrementY ) {
					if ( int DropType = CanRockfordDrop( x, y, OffsetX, OffsetY ) )
						ApplyRockfordDrop( x, y, DropType, OffsetX, OffsetY );
				}
			}
		}
		else
		{
			// Step through the Grid //
			for ( int y = StartY; y != EndY; y += IncrementY ) {
				for ( int x = StartX; x != EndX; x += IncrementX ) {
					if ( int DropType = CanRockfordDrop( x, y, OffsetX, OffsetY ) )
						ApplyRockfordDrop( x, y, DropType, OffsetX, OffsetY );
				}
			}
		}
	}
	// - -------------------------------------------------------------------------------------- - //


	// - -------------------------------------------------------------------------------------- - //
	inline const bool CanISet( const int x, const int y ) const {
		return Clip(x,y) == 0;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const bool CanIDrop( const int _Index, const int OffsetX, const int OffsetY ) const {
		// Place "Value" in the side described by "OffsetX" and "OffsetY", in the "Index" of that //
		//   Row/Column //

		int x, y;
		
		if ( OffsetX < 0 ) {
			x = Width() - 1;
			y = _Index;
		}
		else if ( OffsetX > 0 ) {
			x = 0;
			y = _Index;
		}
		else if ( OffsetY < 0 ) {
			x = _Index;
			y = Height() - 1;
		}
		else  if ( OffsetY > 0 ) {
			x = _Index;
			y = 0;
		}
		
		return CanISet(x,y);
	}
	// - -------------------------------------------------------------------------------------- - //
	inline tType& Edge( const int _Index, const int OffsetX, const int OffsetY ) {
		// Place "Value" in the side described by "OffsetX" and "OffsetY", in the "Index" of that //
		//   Row/Column //

		int x, y;
		
		if ( OffsetX < 0 ) {
			x = Width() - 1;
			y = _Index;
		}
		else if ( OffsetX > 0 ) {
			x = 0;
			y = _Index;
		}
		else if ( OffsetY < 0 ) {
			x = _Index;
			y = Height() - 1;
		}
		else  if ( OffsetY > 0 ) {
			x = _Index;
			y = 0;
		}
		
		return Clip(x,y);
	}
	// - -------------------------------------------------------------------------------------- - //
	inline tType& EdgeDistance( const int _Index, const int OffsetX, const int OffsetY ) {
		// Place "Value" in the side described by "OffsetX" and "OffsetY", in the "Index" of that //
		//   Row/Column //

		int x, y;
		
		if ( OffsetX < 0 ) {
			x = Width() - 1;
			y = ClipY(_Index);
		}
		else if ( OffsetX > 0 ) {
			x = 0;
			y = ClipY(_Index);
		}
		else if ( OffsetY < 0 ) {
			x = ClipX(_Index);
			y = Height() - 1;
		}
		else  if ( OffsetY > 0 ) {
			x = ClipX(_Index);
			y = 0;
		}
		
		int Distance = CalcDropDistance( x, y, OffsetX, OffsetY );
		
		return Clip(x + (OffsetX*Distance), y + (OffsetY*Distance));
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const int EdgeIndex( const int _Index, const int OffsetX, const int OffsetY ) {
		// Place "Value" in the side described by "OffsetX" and "OffsetY", in the "Index" of that //
		//   Row/Column //

		int x, y;
		
		if ( OffsetX < 0 ) {
			x = Width() - 1;
			y = _Index;
		}
		else if ( OffsetX > 0 ) {
			x = 0;
			y = _Index;
		}
		else if ( OffsetY < 0 ) {
			x = _Index;
			y = Height() - 1;
		}
		else  if ( OffsetY > 0 ) {
			x = _Index;
			y = 0;
		}
		
		return IndexClip(x,y);
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const int EdgeDistanceIndex( const int _Index, const int OffsetX, const int OffsetY ) {
		// Place "Value" in the side described by "OffsetX" and "OffsetY", in the "Index" of that //
		//   Row/Column //

		int x, y;
		
		if ( OffsetX < 0 ) {
			x = Width() - 1;
			y = ClipY(_Index);
		}
		else if ( OffsetX > 0 ) {
			x = 0;
			y = ClipY(_Index);
		}
		else if ( OffsetY < 0 ) {
			x = ClipX(_Index);
			y = Height() - 1;
		}
		else  if ( OffsetY > 0 ) {
			x = ClipX(_Index);
			y = 0;
		}
		
		int Distance = CalcDropDistance( x, y, OffsetX, OffsetY );
		
		return IndexClip(x + (OffsetX*Distance), y + (OffsetY*Distance));
	}
	// - -------------------------------------------------------------------------------------- - //
	inline bool AddDrop( const int _Index, const int OffsetX, const int OffsetY, const tType& Value ) {
		// Place "Value" in the side described by "OffsetX" and "OffsetY", in the "Index" of that //
		//   Row/Column //

		int x, y;
		
		if ( OffsetX < 0 ) {
			x = Width() - 1;
			y = _Index;
		}
		else if ( OffsetX > 0 ) {
			x = 0;
			y = _Index;
		}
		else if ( OffsetY < 0 ) {
			x = _Index;
			y = Height() - 1;
		}
		else  if ( OffsetY > 0 ) {
			x = _Index;
			y = 0;
		}
		
		if ( CanISet(x,y) ) {
			Swap( x, y, Value );
			return true;
		}

		return false;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline bool AddDropDistance( const int _Index, const int OffsetX, const int OffsetY, const tType& Value ) {
		// Place "Value" in the side described by "OffsetX" and "OffsetY", in the "Index" of that //
		//   Row/Column //

		int x, y;
		
		if ( OffsetX < 0 ) {
			x = Width() - 1;
			y = ClipY(_Index);
		}
		else if ( OffsetX > 0 ) {
			x = 0;
			y = ClipY(_Index);
		}
		else if ( OffsetY < 0 ) {
			x = ClipX(_Index);
			y = Height() - 1;
		}
		else  if ( OffsetY > 0 ) {
			x = ClipX(_Index);
			y = 0;
		}
		
		if ( CanISet( x, y ) ) {
			Swap( x, y, Value );
			if ( int Distance = CalcDropDistance( x, y, OffsetX, OffsetY ) ) {
				ApplyDropDistance( x, y, Distance, OffsetX, OffsetY );
			}
			return true;
		}

		return false;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline bool AddRockfordDrop( const int _Index, const int OffsetX, const int OffsetY, const tType& Value ) {
		// TODO: The fall part will technically pick the wrong way on the bottom and right //
		
		// Desired Tile //
		if ( !AddDrop( _Index, OffsetX, OffsetY, Value ) ) {
			// Tile to the Left //
			if ( !AddDrop( _Index-1, OffsetX, OffsetY, Value ) ) {
				// Tile to the Right //
				return AddDrop( _Index-1, OffsetX, OffsetY, Value );
			}
		}
		return true;
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	inline const tType GetLowest() const {
		tType Value;
		if ( Size() ) {
			Value = Data[0];
			for ( size_t idx = 1; idx < Size(); idx++ ) {
				if ( Data[idx] < Value ) {
					Value = Data[idx];
				}
			}
		}
		return Value;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const tType GetHighest() const {
		tType Value;
		if ( Size() ) {
			Value = Data[0];
			for ( size_t idx = 1; idx < Size(); idx++ ) {
				if ( Data[idx] > Value ) {
					Value = Data[idx];
				}
			}
		}
		return Value;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const ABSet<tType> GetRange() const {
		ABSet<tType> Value;
		if ( Size() ) {
			Value.a = Data[0];
			Value.b = Data[0];
			for ( size_t idx = 1; idx < Size(); idx++ ) {
				if ( Data[idx] < Value.a ) {
					Value.a = Data[idx];
				}
				else if ( Data[idx] > Value.b ) {
					Value.b = Data[idx];
				}
			}
		}
		return Value;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Uses Reciprocal Optimization //
	inline void _EqualizeData( const tType One = 1.0f, const tType Zero = 0.0f ) {
		ABSet<tType> Range = GetRange();
		tType Diff = Range.b - Range.a;
		if ( Diff != Zero ) {
			tType DiffR = One / Diff;
	
			for ( size_t idx = 0; idx < Size(); idx++ ) {
				Data[idx] = (Data[idx] - Range.a) * DiffR;
			}
		}
		else {
			// In the rare case there is no actual difference, make all 0.5 //
			tType Half = One / (One+One);
			
			for ( size_t idx = 0; idx < Size(); idx++ ) {
				Data[idx] = Half;
			}
		}
	}
	// - -------------------------------------------------------------------------------------- - //
	inline void EqualizeData( const tType One = 1.0f, const tType Zero = 0.0f ) {
		ABSet<tType> Range = GetRange();
		tType Diff = Range.b - Range.a;
		if ( Diff != Zero ) {	
			for ( size_t idx = 0; idx < Size(); idx++ ) {
				Data[idx] = (Data[idx] - Range.a) / Diff;
			}
		}
		else {
			// In the rare case there is no actual difference, make all 0.5 //
			tType Half = One / (One+One);
			
			for ( size_t idx = 0; idx < Size(); idx++ ) {
				Data[idx] = Half;
			}
		}
	}
	// - -------------------------------------------------------------------------------------- - //
	inline void ClipData( const tType Low = 0.0f, const tType High = 1.0f ) {
		for ( size_t idx = 0; idx < Size(); idx++ ) {
			if ( Data[idx] < Low ) {
				Data[idx] = Low;
			}
			else if ( Data[idx] > High ) {
				Data[idx] = High;
			}
		}
	}
	// - -------------------------------------------------------------------------------------- - //
	// TODO: Replace these with operators vs tTypes //
	// - -------------------------------------------------------------------------------------- - //
	inline void AddData( const tType Value ) {
		for ( size_t idx = 0; idx < Size(); idx++ ) {
			Data[idx] += Value;
		}
	}
	// - -------------------------------------------------------------------------------------- - //
	inline void SubData( const tType Value ) {
		for ( size_t idx = 0; idx < Size(); idx++ ) {
			Data[idx] -= Value;
		}
	}
	// - -------------------------------------------------------------------------------------- - //
	inline void MultData( const tType Value ) {
		for ( size_t idx = 0; idx < Size(); idx++ ) {
			Data[idx] *= Value;
		}
	}
	// - -------------------------------------------------------------------------------------- - //
	inline void DivData( const tType Value ) {
		for ( size_t idx = 0; idx < Size(); idx++ ) {
			Data[idx] /= Value;
		}
	}
	// - -------------------------------------------------------------------------------------- - //
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __Grid_cGrid2D_Class_H__ //
// - ------------------------------------------------------------------------------------------ - //
