// - ------------------------------------------------------------------------------------------ - //
#ifndef __UIHost_H__
#define __UIHost_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Debug/Log.h>
#include <Math/Vector.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Core/DataBlock.h>
#include <Core/DataArray.h>
#include <Util/Chunk/ChunkReader.h>
#include "PairView.h"
// - ------------------------------------------------------------------------------------------ - //
#include <vector>
// - ------------------------------------------------------------------------------------------ - //
#include <Graphics/Graphics.h>
#include <Graphics/GraphicsDraw.h>

#include <Graphics/Allocator/StaticVector2DAllocator.h>
#include <Graphics/Allocator/StaticUVAllocator.h>
// - ------------------------------------------------------------------------------------------ - //
#include "UIElement.h"
// - ------------------------------------------------------------------------------------------ - //

extern int View_Dummy[];

// - ------------------------------------------------------------------------------------------ - //
class cUIElementInstance {
public:
	cUIElement* Element;
	
	int* Variable;
	
	int Value;
	Real Scale;
	Vector2D Pos;

public:
	cUIElementInstance( cUIElement* _Element ) :
		Element( _Element ),
		Variable( 0 ),
		Value( _Element->Value ),
		Scale( 1 ),
		Pos( _Element->x, _Element->y )
	{
	}
	
	void Reset() {
		Variable = 0;
		Value = _Value();
		Scale = _Scale();
		Pos = Vector2D( _x(), _y() );
	}
	
public:
	inline short Type() const {
		return Element->Type;
	}
	
	inline short Alignment() const {
		return Element->Flags & UIA_MASK;
	}

	inline short Flags() const {
		return Element->Flags;
	}

	inline short Min() const {
		return Element->Min;
	}
	inline short Max() const {
		return Element->Max;
	}
	
	inline int DataIndex() const {
		return Element->DataIndex;
	}

public:
	// Original Settings //
	inline int _x() const {
		return Element->x;
	}
	inline int _y() const {
		return Element->y;
	}
	inline Vector2D _Pos() const {
		return Vector2D( Element->x, Element->y );
	}
	inline float _Scale() const {
		return Element->Scale;
	}
	inline short _Value() const {
		return Element->Value;
	}

};
// - ------------------------------------------------------------------------------------------ - //
class cUIGraphic {
public:
	// 4 Bytes //
	int StringOffset;
	// 4 Bytes (Image Dimesnions) //
	short Width;
	short Height;
	// 8 Bytes //
	short x, y;
	short w, h; // Rectangle Dimensions //
	
public:
	inline bool Test( const cUIGraphic& Vs ) const {
		if ( x == Vs.x )
			if ( y == Vs.y )
				if ( w == Vs.w )
					return h == Vs.h;
		return false;
	}
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
class cUIHost {
	char* Data;

public:
	std::vector< cUIElementInstance > Element;
		
	char* GraphicStrings;
	char* TextStrings;
	
	size_t GraphicElementCount;
	cUIGraphic* GraphicElement;
	int* TextElement;
	
	int* GraphicBase;
	int* TextBase;
	
	std::vector< GelTextureID > Texture;
	
	PairView* View;
	int* ElementView;
	
	int* Meta;

public:
	cUIHost() :
		Data(0)
	{	
	}
	
	inline bool IsEmpty() {
		return Data == 0;
	}

	inline void Clear() {
		Reset();
		Data = 0;
	}

public:
	void Reset() {
		Element.clear();
		Texture.clear();
		
		GraphicStrings = 0;
		TextStrings = 0;
		GraphicElementCount = 0;
		GraphicElement = 0;
		TextElement = 0;
		GraphicBase = 0;
		TextBase = 0;
		View = 0;
		ElementView = 0;
		Meta = 0;
	}

	void Load( char* _Data ) {
		Data = _Data;
		Reset();
		Load();
		LoadTextures();
	}
	
//	void Load( const char* FileName ) {
//		Log( "Loading Screen: \"%s\"...\n", FileName );
//		Load( new_DataBlock( FileName ) );
//	}

	void Load( DataBlock* _Data ) {
		Data = _Data->Data;
		Reset();
		Load();
		LoadTextures();
	}

	void Load() {
		cChunkReader Chunk( Data );
		
		// Process the file //
		while ( !Chunk.Is( "END " ) ) {
			{
				char Name[4+1];
				int* NamePtr = (int*)Name;
				*NamePtr = Chunk.Name();
				Name[4] = 0;
				//Log( "%s - Size=%i\n", Name, Chunk.Size() );
			}

			if ( Chunk.Is( "SCRN" ) ) {
				// Yep, we're a screen File... I don't really care //
			}
			else if ( Chunk.Is( "ELEM" ) ) {
				DataArray<cUIElement>* Elements = Chunk.Data< DataArray<cUIElement> >();
				for ( size_t idx = 0; idx < Elements->Size; idx++ ) {
					Element.push_back( cUIElementInstance( &Elements->Data[idx] ) );
				}
				//Log( "Loaded %i Elements...\n", Element.size() );
			}

			else if ( Chunk.Is( "GR_S" ) ) {
				GraphicStrings = Chunk.Data<char>();
			}
			else if ( Chunk.Is( "TX_S" ) ) {
				TextStrings = Chunk.Data<char>();
			}

			else if ( Chunk.Is( "GR_E" ) ) {
				GraphicElementCount = Chunk.Size() / sizeof(cUIGraphic);
				GraphicElement = Chunk.Data<cUIGraphic>();
				//Log( "%i Graphic Elements\n", GraphicElementCount );
			}
			else if ( Chunk.Is( "TX_E" ) ) {
				TextElement = Chunk.Data<int>();
			}

			else if ( Chunk.Is( "GRCH" ) ) {
				GraphicBase = Chunk.Data<int>();
			}
			else if ( Chunk.Is( "TXCH" ) ) {
				TextBase = Chunk.Data<int>();
			}

			else if ( Chunk.Is( "VIEW" ) ) {
				View = Chunk.Data<PairView>();
			}
			else if ( Chunk.Is( "VIEL" ) ) {
				ElementView = Chunk.Data<int>();
			}
			else if ( Chunk.Is( "META" ) ) {
				Meta = Chunk.Data<int>();
			}
			else {
				char Name[4+1];
				int* NamePtr = (int*)Name;
				*NamePtr = Chunk.Name();
				Name[4] = 0;
				Log( "Warning: Unknown Chunk \"%s\"\n", Name );
			}
			
			Chunk.Next();
		};
	}
	
	void LoadTextures() {
		for ( size_t idx = 0; idx < GraphicElementCount; idx++ ) {
			char* FileName = &GraphicStrings[ GraphicElement[ idx ].StringOffset ];
			GelTextureID Tx = gelLoadTexture( FileName );
			Texture.push_back( Tx );
		}
	}

	// Returns the Index of the item that matches the mentioned Meta Data. -1 on Failure //
	inline int GetMetaIndex( const int Value ) {
		if ( Meta ) {
			for ( int idx = 0; idx < View->Count; idx++ ) {
				if ( Meta[idx] == Value )
					return idx;
			}
		}
		return -1;
	}
	
	inline bool Test( const cUIHost& Vs, size_t Index ) const {
		if ( Element[Index].Type() == Vs.Element[Index].Type() ) {
			if ( Element[Index].Type() == UI_DUMMY )
				return true;
				
			// If the same texture file //
			if ( Texture[ GraphicBase[ Element[Index].DataIndex() ] ] == Vs.Texture[ Vs.GraphicBase[ Vs.Element[Index].DataIndex() ] ] ) {
				if ( Element[Index].Value == Vs.Element[Index].Value ) {
					// If the same dimensions //
					return GraphicElement[ GraphicBase[ Element[Index].DataIndex() ] ].Test( Vs.GraphicElement[ Vs.GraphicBase[ Vs.Element[Index].DataIndex() ] ] );
				}
			}
		}
		return false;
	}

public:
	void Step() {
	}
	
	void DrawGraphic( int Index, int Alignment, Vector2D Pos, Real Scale = Real::One ) {
		cUIGraphic* Graphic = &GraphicElement[ Index ];
		
		StaticVector2DAllocator<3*2> Vert;
		StaticUVAllocator<3*2> UV;

		Vector2D P1 = Pos;
		Vector2D P2 = Pos;
		
		// X Axis Alignment //
		if ( (Alignment & UIA_HMASK) == UIA_HLEFT ) {
			P2.x += Real( Graphic->w ) * Scale;
		}
		else if ( (Alignment & UIA_HMASK) == UIA_HRIGHT ) {
			P1.x -= Real( Graphic->w ) * Scale;
		}
		else {
			Real Half = Real( Graphic->w >> 1 ) * Scale;
			P1.x -= Half;
			P2.x += Half;
		}
		
		// Y Axis Alignment //
		if ( (Alignment & UIA_VMASK) == UIA_VTOP ) {
			P2.y += Real( Graphic->h ) * Scale;
		}
		else if ( (Alignment & UIA_VMASK) == UIA_VBOTTOM ) {
			P1.y -= Real( Graphic->h ) * Scale;
		}
		else {
			Real Half = Real( Graphic->h >> 1 ) * Scale;
			P1.y -= Half;
			P2.y += Half;
		}
		
		// Add Vertices //
		Vert.AddRect6( P1, P2 );
			
		// Add UV's //
		// TODO: Division here can be optimized in to a shift //
		UV.AddRect6( 
			(Graphic->x * GEL_UV_ONE / Graphic->Width),
			(Graphic->y * GEL_UV_ONE / Graphic->Height),
			((Graphic->x + Graphic->w) * GEL_UV_ONE / Graphic->Width),
			((Graphic->y + Graphic->h) * GEL_UV_ONE / Graphic->Height)
			);

		gelSetTexture( Texture[ Index ] );
		//gelSetSmoothTexturesMipMapped();
					
//		gelDrawTexturedPolygons(
		gelDrawTrianglesTextured(
			(Vector2D*)Vert.Data,
			(GelUV*)UV.Data,
			Vert.Size()
			);
	}

	void DrawGraphic( int Index, int Alignment, Vector2D Pos, Real Scale, Real Angle ) {
		cUIGraphic* Graphic = &GraphicElement[ Index ];
		
		StaticVector2DAllocator<3*2> Vert;
		StaticUVAllocator<3*2> UV;

		Vector2D P1 = Vector2D::Zero;
		Vector2D P2 = Vector2D::Zero;
		
		// X Axis Alignment //
		if ( (Alignment & UIA_HMASK) == UIA_HLEFT ) {
			P2.x += Real( Graphic->w ) * Scale;
		}
		else if ( (Alignment & UIA_HMASK) == UIA_HRIGHT ) {
			P1.x -= Real( Graphic->w ) * Scale;
		}
		else {
			Real Half = Real( Graphic->w >> 1 ) * Scale;
			P1.x -= Half;
			P2.x += Half;
		}
		
		// Y Axis Alignment //
		if ( (Alignment & UIA_VMASK) == UIA_VTOP ) {
			P2.y += Real( Graphic->h ) * Scale;
		}
		else if ( (Alignment & UIA_VMASK) == UIA_VBOTTOM ) {
			P1.y -= Real( Graphic->h ) * Scale;
		}
		else {
			Real Half = Real( Graphic->h >> 1 ) * Scale;
			P1.y -= Half;
			P2.y += Half;
		}
		
		// Add Vertices //
		Vert.AddRect6( P1, P2, Pos, Angle );
			
		// Add UV's //
		// TODO: Division here can be optimized in to a shift //
		UV.AddRect6( 
			(Graphic->x * GEL_UV_ONE / Graphic->Width),
			(Graphic->y * GEL_UV_ONE / Graphic->Height),
			((Graphic->x + Graphic->w) * GEL_UV_ONE / Graphic->Width),
			((Graphic->y + Graphic->h) * GEL_UV_ONE / Graphic->Height)
			);

		gelSetTexture( Texture[ Index ] );
					
//		gelDrawTexturedPolygons(
		gelDrawTrianglesTextured(
			(Vector2D*)Vert.Data,
			(GelUV*)UV.Data,
			Vert.Size()
			);
	}

	void DrawElement( size_t idx ) {
		if ( Element[idx].Type() == UI_GRAPHIC ) {
			int Value = Element[idx].Value;
			
			// If Variable set, use it instead of value //
			if ( Element[idx].Flags() & UIF_VARIABLE ) {
				if ( Element[idx].Variable ) {
					Value = *Element[idx].Variable;
				}
			}
			
			int GraphicIndex = GraphicBase[ Element[idx].DataIndex() ] + Value;
			DrawGraphic( 
				GraphicIndex,
				Element[idx].Alignment(),
				Element[idx].Pos,
				Element[idx].Scale * Real( Element[idx]._Scale() )
				);
		}
		else if ( Element[idx].Type() == UI_TEXT ) {
			
		}
	}
	
	void Draw() {
		for( size_t idx = 0; idx < Element.size(); idx++ ) {
			DrawElement( idx );
		}
	}
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
class cUIHostPair {
public:
	cUIHost Current;
	cUIHost Last;
	
	std::vector< bool > ElementDone;
	bool DoneTransition;
	
	std::vector< int > DrawOrder;

public:
	cUIHostPair() {
	}
	
	void Clear() {
		Current.Clear();
		Last.Clear();
	}
	
public:
	void Load( char* _Data ) {
		Current.Load( _Data );
		
		ElementDone.clear();
		ElementDone.resize( Current.Element.size(), true );
		DoneTransition = true;
		
		DrawOrder.resize( Current.Element.size() );
		for ( size_t idx = 0; idx < DrawOrder.size(); idx++ ) {
			DrawOrder[idx] = idx;
		}
	}
	
	void Set( char* _Data ) {
		if ( !Current.IsEmpty() ) {
			Last = Current;
			Current.Load( _Data );
			
			ElementDone.clear();
			ElementDone.resize( Last.Element.size(), false );
			if ( Current.Element.size() > ElementDone.size() ) {
				ElementDone.resize( Current.Element.size(), true );
			}
	
			for ( size_t idx = 0; idx < Current.Element.size(); idx++ ) {
				Current.Element[idx].Scale = Real::Zero;
			}
			
			// Calculate the maximum overlap //
			size_t Max = Last.Element.size();
			if ( Current.Element.size() < Max ) {
				Max = Current.Element.size();
			}
			
			// Test our two UIHost's for equality of items //
			for ( size_t idx = 0; idx < Max; idx++ ) {
				if ( Current.Test( Last, idx ) ) {
					ElementDone[idx] = true;
					//if ( Current.Element[idx].Scale <= Real::One ) 
						Current.Element[idx].Scale = Last.Element[idx].Scale;//Real::One;
					Current.Element[idx].Pos = Last.Element[idx].Pos;
				}
			}
	
			DrawOrder.resize( Current.Element.size() );
			for ( size_t idx = 0; idx < DrawOrder.size(); idx++ ) {
				DrawOrder[idx] = idx;
			}
		}
		else {
			Load( _Data );
		}
	}
	
	PairView* GetView() {
		if ( Current.View )
			return Current.View;
		else
			return (PairView*)&View_Dummy;
	}

public:
	void Light( int Index ) {
		if ( DoneTransition ) {
			int Idx = Current.ElementView[ Index ];
			
			Real Diff = Real(1.50) - Current.Element[ Idx ].Scale;
			Current.Element[ Idx ].Scale += Diff * Real( 0.15 );
		}
	}
	
	void ForceChange( int Index ) {
		DoneTransition = false;
		ElementDone[Index] = false;
		Current.Element[Index].Scale = Real::Zero;
	}

	void Skip() {
		DoneTransition = false;
		for ( size_t idx = 0; idx < Current.Element.size(); idx++ ) {
			Current.Element[idx].Scale = Real::One;
			Current.Element[idx].Pos = Current.Element[idx]._Pos();
			ElementDone[idx] = true;
		}
		Step();
	}
	
	void Step() {
		// Zooming Effects //
		if ( !DoneTransition ) {
			for( size_t idx = 0; idx < Last.Element.size(); idx++ ) {
				if ( !ElementDone[idx] ) {
					Real Diff = Real(0) - Last.Element[idx].Scale;
					Last.Element[idx].Scale += Diff * Real( 0.15 );
					
					if ( Last.Element[idx].Scale < 0.05 ) {
						ElementDone[idx] = true;
					}
				}
			}
		}
		else {
			for( size_t idx = 0; idx < Current.Element.size(); idx++ ) {
				Real Diff = Real(1) - Current.Element[idx].Scale;
				
				Current.Element[idx].Scale += Diff * Real( 0.1 );
			}

			// Interpolate Positions //
			for( size_t idx = 0; idx < Current.Element.size(); idx++ ) {
				if ( ElementDone[idx] ) {
					Vector2D Diff = Current.Element[idx]._Pos() - Current.Element[idx].Pos;
					Current.Element[idx].Pos += Diff * Real( 0.1 );
				}
			}
		}
		
		// Single Step Bubble Sort the Draw Order by the value of scale //
		if ( Current.Element.size() > 1 ) {
			for ( size_t idx = 0; idx < DrawOrder.size() - 1; idx++ ) {
				// Don't sort if one of the two items we care about has a non sort flag //
				if ( Current.Element[ DrawOrder[idx] ].Flags() & UIF_NOSORT )
					continue;
				if ( Current.Element[ DrawOrder[idx+1] ].Flags() & UIF_NOSORT )
					continue;
				
				if ( Current.Element[ DrawOrder[idx] ].Scale > Current.Element[ DrawOrder[idx+1] ].Scale ) {
					int Temp = DrawOrder[idx];
					DrawOrder[idx] = DrawOrder[idx+1];
					DrawOrder[idx+1] = Temp;
				}
			}
		}
		
		// Test if we should be drawing in merged mode or not //
		DoneTransition = false;
		unsigned int DoneCount = 0;
		for ( size_t idx = 0; idx < ElementDone.size(); idx++ ) {
			if ( ElementDone[idx] )
				DoneCount++;
		}
		if ( DoneCount == ElementDone.size() ) {
			DoneTransition = true;		
		}
	}
	
	void Draw() {
		if ( DoneTransition ) {
			for( size_t idx = 0; idx < Current.Element.size(); idx++ ) {
				Current.DrawElement( DrawOrder[ idx ] );
			}
		}
		else {
			for( size_t idx = 0; idx < Last.Element.size(); idx++ ) {
				Last.DrawElement( idx );
			}
		}
	}
};		
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __UIHost_H__ /
// - ------------------------------------------------------------------------------------------ - //
