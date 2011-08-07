// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_GraphicsDraw_Text_H__
#define __GEL_GraphicsDraw_Text_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Graphics/GelFont/GelFont.h>
#include <Graphics/GelFont/BMFont.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#ifdef _MSC_VER
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#define gelPrintf(p,c,_Format, ...) \
	gelPrintfLeft(p,c,_Format, ## __VA_ARGS__)
// - ------------------------------------------------------------------------------------------ - //
#define gelPrintfLeft(p,c,_Format, ...) \
{ \
	char StrBuff[1024]; \
	sprintf( StrBuff, _Format, ## __VA_ARGS__ ); \
	gelPrint(p,c,StrBuff); \
}
// - ------------------------------------------------------------------------------------------ - //
#define gelPrintfCenter(p,c,_Format, ...) \
{ \
	char StrBuff[1024]; \
	sprintf( StrBuff, _Format, ## __VA_ARGS__ ); \
	Vector2D Offset( gelTextWidth(StrBuff) * 0.5, 0 ); \
	gelPrint((p)-Offset,c,StrBuff); \
}
// - ------------------------------------------------------------------------------------------ - //
#define gelPrintfRight(p,c,_Format, ...) \
{ \
	char StrBuff[1024]; \
	sprintf( StrBuff, _Format, ## __VA_ARGS__ ); \
	Vector2D Offset( gelTextWidth(StrBuff), 0 ); \
	gelPrint((p)-Offset,c,StrBuff); \
}
// - ------------------------------------------------------------------------------------------ - //
#define gelPrintfLeftCenter(p,c,_Format, ...) \
{ \
	char StrBuff[1024]; \
	sprintf( StrBuff, _Format, ## __VA_ARGS__ ); \
	Vector2D Offset( 0, gelTextHeight(StrBuff) * 0.5 ); \
	gelPrint((p)-Offset,c,StrBuff); \
}
// - ------------------------------------------------------------------------------------------ - //
#define gelPrintfCenterCenter(p,c,_Format, ...) \
{ \
	char StrBuff[1024]; \
	sprintf( StrBuff, _Format, ## __VA_ARGS__ ); \
	Vector2D Offset( gelTextWidth(StrBuff) * 0.5, gelTextHeight(StrBuff) * 0.5 ); \
	gelPrint((p)-Offset,c,StrBuff); \
}
// - ------------------------------------------------------------------------------------------ - //
#define gelPrintfRightCenter(p,c,_Format, ...) \
{ \
	char StrBuff[1024]; \
	sprintf( StrBuff, _Format, ## __VA_ARGS__ ); \
	Vector2D Offset( gelTextWidth(StrBuff), gelTextHeight(StrBuff) * 0.5 ); \
	gelPrint((p)-Offset,c,StrBuff); \
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#define gelXPrintf(p,c,s,_Format, ...) \
	gelXPrintfLeft(p,c,s,_Format, ## __VA_ARGS__)
// - ------------------------------------------------------------------------------------------ - //
#define gelXPrintfLeft(p,c,s,_Format, ...) \
{ \
	char StrBuff[1024]; \
	sprintf( StrBuff, _Format, ## __VA_ARGS__ ); \
	gelPrint(p,c,StrBuff,s); \
}
// - ------------------------------------------------------------------------------------------ - //
#define gelXPrintfCenter(p,c,s,_Format, ...) \
{ \
	char StrBuff[1024]; \
	sprintf( StrBuff, _Format, ## __VA_ARGS__ ); \
	Vector2D Offset( gelTextWidth(StrBuff,s) * 0.5, 0 ); \
	gelPrint((p)-Offset,c,StrBuff,s); \
}
// - ------------------------------------------------------------------------------------------ - //
#define gelXPrintfRight(p,c,s,_Format, ...) \
{ \
	char StrBuff[1024]; \
	sprintf( StrBuff, _Format, ## __VA_ARGS__ ); \
	Vector2D Offset( gelTextWidth(StrBuff,s), 0 ); \
	gelPrint((p)-Offset,c,StrBuff,s); \
}
// - ------------------------------------------------------------------------------------------ - //
#define gelXPrintfLeftCenter(p,c,s,_Format, ...) \
{ \
	char StrBuff[1024]; \
	sprintf( StrBuff, _Format, ## __VA_ARGS__); \
	Vector2D Offset( 0, gelTextHeight(StrBuff,s) * 0.5 ); \
	gelPrint((p)-Offset,c,StrBuff,s); \
}
// - ------------------------------------------------------------------------------------------ - //
#define gelXPrintfCenterCenter(p,c,s,_Format, ...) \
{ \
	char StrBuff[1024]; \
	sprintf( StrBuff, _Format, ## __VA_ARGS__); \
	Vector2D Offset( gelTextWidth(StrBuff,s) * 0.5, gelTextHeight(StrBuff,s) * 0.5 ); \
	gelPrint((p)-Offset,c,StrBuff,s); \
}
// - ------------------------------------------------------------------------------------------ - //
#define gelXPrintfRightCenter(p,c,s,_Format, ...) \
{ \
	char StrBuff[1024]; \
	sprintf( StrBuff, _Format, ## __VA_ARGS__ ); \
	Vector2D Offset( gelTextWidth(StrBuff,s), gelTextHeight(StrBuff,s) * 0.5 ); \
	gelPrint((p)-Offset,c,StrBuff,s); \
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#else // _MSC_VER //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#define gelPrintf(p,c,_Format,_Args...) \
	gelPrintfLeft(p,c,_Format, ## _Args)
// - ------------------------------------------------------------------------------------------ - //
#define gelPrintfLeft(p,c,_Format,_Args...) \
{ \
	char StrBuff[1024]; \
	sprintf( StrBuff, _Format, ## _Args ); \
	gelPrint(p,c,StrBuff); \
}
// - ------------------------------------------------------------------------------------------ - //
#define gelPrintfCenter(p,c,_Format,_Args...) \
{ \
	char StrBuff[1024]; \
	sprintf( StrBuff, _Format, ## _Args ); \
	Vector2D Offset( gelTextWidth(StrBuff) * 0.5, 0 ); \
	gelPrint((p)-Offset,c,StrBuff); \
}
// - ------------------------------------------------------------------------------------------ - //
#define gelPrintfRight(p,c,_Format,_Args...) \
{ \
	char StrBuff[1024]; \
	sprintf( StrBuff, _Format, ## _Args ); \
	Vector2D Offset( gelTextWidth(StrBuff), 0 ); \
	gelPrint((p)-Offset,c,StrBuff); \
}
// - ------------------------------------------------------------------------------------------ - //
#define gelPrintfLeftCenter(p,c,_Format,_Args...) \
{ \
	char StrBuff[1024]; \
	sprintf( StrBuff, _Format, ## _Args ); \
	Vector2D Offset( 0, gelTextHeight(StrBuff) * 0.5 ); \
	gelPrint((p)-Offset,c,StrBuff); \
}
// - ------------------------------------------------------------------------------------------ - //
#define gelPrintfCenterCenter(p,c,_Format,_Args...) \
{ \
	char StrBuff[1024]; \
	sprintf( StrBuff, _Format, ## _Args ); \
	Vector2D Offset( gelTextWidth(StrBuff) * 0.5, gelTextHeight(StrBuff) * 0.5 ); \
	gelPrint((p)-Offset,c,StrBuff); \
}
// - ------------------------------------------------------------------------------------------ - //
#define gelPrintfRightCenter(p,c,_Format,_Args...) \
{ \
	char StrBuff[1024]; \
	sprintf( StrBuff, _Format, ## _Args ); \
	Vector2D Offset( gelTextWidth(StrBuff), gelTextHeight(StrBuff) * 0.5 ); \
	gelPrint((p)-Offset,c,StrBuff); \
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#define gelXPrintf(p,c,s,_Format,_Args...) \
	gelXPrintfLeft(p,c,s,_Format, ## _Args)
// - ------------------------------------------------------------------------------------------ - //
#define gelXPrintfLeft(p,c,s,_Format,_Args...) \
{ \
	char StrBuff[1024]; \
	sprintf( StrBuff, _Format, ## _Args ); \
	gelPrint(p,c,StrBuff,s); \
}
// - ------------------------------------------------------------------------------------------ - //
#define gelXPrintfCenter(p,c,s,_Format,_Args...) \
{ \
	char StrBuff[1024]; \
	sprintf( StrBuff, _Format, ## _Args ); \
	Vector2D Offset( gelTextWidth(StrBuff,s) * 0.5, 0 ); \
	gelPrint((p)-Offset,c,StrBuff,s); \
}
// - ------------------------------------------------------------------------------------------ - //
#define gelXPrintfRight(p,c,s,_Format,_Args...) \
{ \
	char StrBuff[1024]; \
	sprintf( StrBuff, _Format, ## _Args ); \
	Vector2D Offset( gelTextWidth(StrBuff,s), 0 ); \
	gelPrint((p)-Offset,c,StrBuff,s); \
}
// - ------------------------------------------------------------------------------------------ - //
#define gelXPrintfLeftCenter(p,c,s,_Format,_Args...) \
{ \
	char StrBuff[1024]; \
	sprintf( StrBuff, _Format, ## _Args ); \
	Vector2D Offset( 0, gelTextHeight(StrBuff,s) * 0.5 ); \
	gelPrint((p)-Offset,c,StrBuff,s); \
}
// - ------------------------------------------------------------------------------------------ - //
#define gelXPrintfCenterCenter(p,c,s,_Format,_Args...) \
{ \
	char StrBuff[1024]; \
	sprintf( StrBuff, _Format, ## _Args ); \
	Vector2D Offset( gelTextWidth(StrBuff,s) * 0.5, gelTextHeight(StrBuff,s) * 0.5 ); \
	gelPrint((p)-Offset,c,StrBuff,s); \
}
// - ------------------------------------------------------------------------------------------ - //
#define gelXPrintfRightCenter(p,c,s,_Format,_Args...) \
{ \
	char StrBuff[1024]; \
	sprintf( StrBuff, _Format, ## _Args ); \
	Vector2D Offset( gelTextWidth(StrBuff,s), gelTextHeight(StrBuff,s) * 0.5 ); \
	gelPrint((p)-Offset,c,StrBuff,s); \
}
// - ------------------------------------------------------------------------------------------ - //
#endif // _MSC_VER //
// - ------------------------------------------------------------------------------------------ - //

#include <Graphics/Allocator/Allocator.h>
#include <Graphics/Allocator/Vector2DAllocator.h>
#include <Graphics/Allocator/UVAllocator.h>

// - ------------------------------------------------------------------------------------------ - //
inline void gelSetFont( const GelFont& FontName ) {
	Current::Font = &FontName;
}
// - ------------------------------------------------------------------------------------------ - //
inline const float gelTextWidth( const char* Msg, const float Scale = 1.0f ) {
	float Pos = 0;
	
	// For every Character in the string //
	for ( int CurrentChar = 0; Msg[CurrentChar] != 0; CurrentChar++ ) {
		char ch = Msg[CurrentChar]-' ';
		Pos += Current::Font->PixelWidth[(int)ch];
	}

	return Pos * Scale;
}
// - ------------------------------------------------------------------------------------------ - //
inline const float gelTextHeight( const char*, const float Scale = 1.0f ) {
	return *(Current::Font->PixelHeight) * Scale;
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelPrint( const Vector2D& _Pos, const GelColor Color, const char* Msg ) {
	//const int _Length = strlen( Msg );
	const int Length = 128;
	
	Vector2DAllocator Vert( Length * 4 );
	UVAllocator UV( Length * 4 );
	Allocator< unsigned short > Indexes( Length * 6 );
	
	int PolygonIndex = 0;
	
	Vector2D Pos = _Pos;
	
	// For every Character in the string //
	for ( int CurrentChar = 0; Msg[CurrentChar] != 0; CurrentChar++ ) {
		char ch = Msg[CurrentChar]-' ';
		
		if ( ch != 0 ) {
			Vert.AddQuad4( Current::Font->TriStripTable[ Current::Font->BlockWidth[(int)ch] - 1 ], Pos );
			UV.AddQuad4( &Current::Font->UVStrip[8*((int)ch)] );
			
			int StartIndex = Indexes.AddMany( 6 );
			// TODO: Optimize this in to a single write operation per pair //
			Indexes[StartIndex+0] = (PolygonIndex)+0;
			Indexes[StartIndex+1] = (PolygonIndex)+1;
			Indexes[StartIndex+2] = (PolygonIndex)+2;
			Indexes[StartIndex+3] = (PolygonIndex)+2;
			Indexes[StartIndex+4] = (PolygonIndex)+1;
			Indexes[StartIndex+5] = (PolygonIndex)+3;
			
			PolygonIndex += 4;
		}
		Pos += Vector2D( Current::Font->PixelWidth[(int)ch], 0 );
		
	}
	
	//GelColor BackupColor = Current::Color;
	//gelSetColor( Color );
	
	// Draw the string //
	//gelDrawTexturedIndexedPolygons(
	gelDrawIndexedTrianglesTextured(
		(Vector2D*)Vert.Data,
		(GelUV*)UV.Data,
		//Vert.Size(),
		Indexes.Data,
		Indexes.Size(),
		Color
		);
	
	//gelSetColor( BackupColor );
} 
// - ------------------------------------------------------------------------------------------ - //
inline void gelPrint( const Vector2D& _Pos, const GelColor Color, const char* Msg, Real Scale ) {
	//const int _Length = strlen( Msg );
	const int Length = 128;
	
	Vector2DAllocator Vert( Length * 4 );
	UVAllocator UV( Length * 4 );
	Allocator< unsigned short > Indexes( Length * 6 );
	
	int PolygonIndex = 0;
	
	Vector2D Pos = _Pos;
	
	// For every Character in the string //
	for ( int CurrentChar = 0; Msg[CurrentChar] != 0; CurrentChar++ ) {
		char ch = Msg[CurrentChar]-' ';
		
		if ( ch != 0 ) {
			Vert.AddQuad4( Current::Font->TriStripTable[ Current::Font->BlockWidth[(int)ch] - 1 ], Pos, Scale );
			UV.AddQuad4( &Current::Font->UVStrip[8*((int)ch)] );
			
			int StartIndex = Indexes.AddMany( 6 );
			// TODO: Optimize this in to a single write operation per pair //
			Indexes[StartIndex+0] = (PolygonIndex)+0;
			Indexes[StartIndex+1] = (PolygonIndex)+1;
			Indexes[StartIndex+2] = (PolygonIndex)+2;
			Indexes[StartIndex+3] = (PolygonIndex)+2;
			Indexes[StartIndex+4] = (PolygonIndex)+1;
			Indexes[StartIndex+5] = (PolygonIndex)+3;
			
			PolygonIndex += 4;
		}
		Pos += Vector2D( Current::Font->PixelWidth[(int)ch], 0 ) * Scale;
		
	}
	
//	GelColor BackupColor = Current::Color;
//	gelSetColor( Color );
	
	// Draw the string //
//	gelDrawTexturedIndexedPolygons(
	gelDrawIndexedTrianglesTextured(
		(Vector2D*)Vert.Data,
		(GelUV*)UV.Data,
		//Vert.Size(),
		Indexes.Data,
		Indexes.Size(),
		Color
		);
	
//	gelSetColor( BackupColor );
} 
// - ------------------------------------------------------------------------------------------ - //
inline void gelPrint( const Vector2D& _Pos, const GelColor Color, const char* Msg, const Vector2D& Scale ) {
	//const int _Length = strlen( Msg );
	const int Length = 128;
	
	Vector2DAllocator Vert( Length * 4 );
	UVAllocator UV( Length * 4 );
	Allocator< unsigned short > Indexes( Length * 6 );
	
	int PolygonIndex = 0;
	
	Vector2D Pos = _Pos;
	
	// For every Character in the string //
	for ( int CurrentChar = 0; Msg[CurrentChar] != 0; CurrentChar++ ) {
		char ch = Msg[CurrentChar]-' ';
		
		if ( ch != 0 ) {
			Vert.AddQuad4( Current::Font->TriStripTable[ Current::Font->BlockWidth[(int)ch] - 1 ], Pos, Scale );
			UV.AddQuad4( &Current::Font->UVStrip[8*((int)ch)] );
			
			int StartIndex = Indexes.AddMany( 6 );
			// TODO: Optimize this in to a single write operation per pair //
			Indexes[StartIndex+0] = (PolygonIndex)+0;
			Indexes[StartIndex+1] = (PolygonIndex)+1;
			Indexes[StartIndex+2] = (PolygonIndex)+2;
			Indexes[StartIndex+3] = (PolygonIndex)+2;
			Indexes[StartIndex+4] = (PolygonIndex)+1;
			Indexes[StartIndex+5] = (PolygonIndex)+3;
			
			PolygonIndex += 4;
		}
		Pos += Vector2D( Current::Font->PixelWidth[(int)ch], 0 );
		
	}
	
//	GelColor BackupColor = Current::Color;
//	gelSetColor( Color );
	
	// Draw the string //
//	gelDrawTexturedIndexedPolygons(
	gelDrawIndexedTrianglesTextured(
		(Vector2D*)Vert.Data,
		(GelUV*)UV.Data,
		//Vert.Size(),
		Indexes.Data,
		Indexes.Size(),
		Color
		);
	
//	gelSetColor( BackupColor );
} 
// - ------------------------------------------------------------------------------------------ - //
inline void gelPrint( const Vector2D& _Pos, const GelColor Color, const char* Msg, const Matrix2x2& Transform ) {
	//const int _Length = strlen( Msg );
	const int Length = 128;
	
	Vector2DAllocator Vert( Length * 4 );
	UVAllocator UV( Length * 4 );
	Allocator< unsigned short > Indexes( Length * 6 );
	
	int PolygonIndex = 0;
	
	Vector2D Pos = _Pos;
	
	// For every Character in the string //
	for ( int CurrentChar = 0; Msg[CurrentChar] != 0; CurrentChar++ ) {
		char ch = Msg[CurrentChar]-' ';
		
		if ( ch != 0 ) {
			Vert.AddQuad4( Current::Font->TriStripTable[ Current::Font->BlockWidth[(int)ch] - 1 ], Pos, Transform );
			UV.AddQuad4( &Current::Font->UVStrip[8*((int)ch)] );
			
			int StartIndex = Indexes.AddMany( 6 );
			// TODO: Optimize this in to a single write operation per pair //
			Indexes[StartIndex+0] = (PolygonIndex)+0;
			Indexes[StartIndex+1] = (PolygonIndex)+1;
			Indexes[StartIndex+2] = (PolygonIndex)+2;
			Indexes[StartIndex+3] = (PolygonIndex)+2;
			Indexes[StartIndex+4] = (PolygonIndex)+1;
			Indexes[StartIndex+5] = (PolygonIndex)+3;
			
			PolygonIndex += 4;
		}
		Pos += Vector2D( Current::Font->PixelWidth[(int)ch], 0 );
		
	}
	
//	GelColor BackupColor = Current::Color;
//	gelSetColor( Color );
	
	// Draw the string //
//	gelDrawTexturedIndexedPolygons(
	gelDrawIndexedTrianglesTextured(
		(float*)Vert.Data,
		(GelUV*)UV.Data,
		//Vert.Size(),
		Indexes.Data,
		Indexes.Size(),
		Color
		);
	
//	gelSetColor( BackupColor );
} 
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_GraphicsDraw_Text_H__ //
// - ------------------------------------------------------------------------------------------ - //
