// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_Graphics_BMFont_H__
#define __GEL_Graphics_BMFont_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Core/GelConstants.h>
#include <Core/GelTypes.h>

#include <Core/Data.h>
#include <Core/DataBlock.h>
#include <Core/DataArray.h>
#include <Core/GelString.h>

#include <Debug/GelDebug.h>

#include <Util/StreamReader/StreamReader.h>
// - ------------------------------------------------------------------------------------------ - //
enum {
	//BMFONT_INFO_SIZE	= ??,		// Not a constant size //
	BMFONT_COMMON_SIZE	= 14,
	//BMFONT_PAGES_SIZE	= ??,		// Not a constant size //
	BMFONT_CHARS_SIZE	= 20,
	BMFONT_KERNING_SIZE	= 10,
	
	BMFONT_INFO_SIZE_STATIC = 14,	// The part that isn't the FontName string //

	BMFONT_SECTION_INFO		= 1,
	BMFONT_SECTION_COMMON	= 2,
	BMFONT_SECTION_PAGES	= 3,
	BMFONT_SECTION_CHARS	= 4,
	BMFONT_SECTION_KERNING	= 5,
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
struct BMFont_Info {
	int FontSize;
	union {
		struct {
			int Smooth:1;
			int Unicode:1;
			int Italic:1;
			int Bold:1;
			int FixedHeight:1;
			int BitField_Reserved:3;
		};
		int BitField;
	};
	int CharSet;
	int StretchH;
	int AA; // Antialiasing //
	int PaddingUp;
	int PaddingRight;
	int PaddingDown;
	int PaddingLeft;
	int PaddingHoriz;
	int PaddingVert;
	int Outline;
	char FontName[0];	
};
// - ------------------------------------------------------------------------------------------ - //
struct BMFont_Common {
	int LineHeight;
	int Base;
	int ScaleW;
	int ScaleH;
	int Pages;
	union {
		struct {
			int BitFields_Reserved:7;
			int Packed:1;
		};
		int BitFields;
	};
	int AlphaChannel;
	int RedChannel;
	int GreenChannel;
	int BlueChannel;
};
// - ------------------------------------------------------------------------------------------ - //
struct BMFont_Chars {
	int Id;
	int x;
	int y;
	int Width;
	int Height;
	int OffsetX;
	int OffsetY;
	int AdvanceX;
	int Page;
	int Channel;
};
// - ------------------------------------------------------------------------------------------ - //
struct BMFont_Kerning {
	int First;
	int Second;
	int Amount;
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
struct BMFont {
	union {
		struct {
			unsigned int Magic:24;
			unsigned int Version:8;
		};
		unsigned int MagicNumber;
	};
	
	BMFont_Info* Info;
	BMFont_Common* Common;
	DataArray<char*>* PageName;
	DataBlock* PageNameData;

	BMFont_Chars* DummyChar;					// Only created if no error char was included in the font //
	BMFont_Chars* ErrorChar;
	DataArray<BMFont_Chars>* Chars;				// Packed table of Glyphs //
	DataArray<BMFont_Chars*>* Glyph;			// Full linear table of Glyphs (Chars*'s) //
	DataArray<BMFont_Kerning>* Kerning;
	DataArray<BMFont_Kerning*>* FirstKerning;	// Full linear table of per Glyph Kerning Pointers // 
	DataArray<BMFont_Kerning*>* LastKerning;	// Full linear table of per Glyph Kerning Pointers // 
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline BMFont* delete_BMFont( BMFont* MyFont ) {
	if ( MyFont->Info != 0 )
		delete_Data( MyFont->Info );
	if ( MyFont->Common != 0 )
		delete MyFont->Common;
	if ( MyFont->PageName != 0 )
		delete_DataArray<char*>( MyFont->PageName );
	if ( MyFont->PageNameData != 0 )
		delete_DataBlock( MyFont->PageNameData );
	if ( MyFont->DummyChar != 0 )
		delete MyFont->DummyChar;
	// NOTE: Do not delete the Error Char, as it's just an extra pointer to data //
	if ( MyFont->Chars != 0 )
		delete_DataArray<BMFont_Chars>( MyFont->Chars );
	if ( MyFont->Glyph != 0 )
		delete_DataArray<BMFont_Chars*>( MyFont->Glyph );
	if ( MyFont->Kerning != 0 )
		delete_DataArray<BMFont_Kerning>( MyFont->Kerning );
	if ( MyFont->FirstKerning != 0 )
		delete_DataArray<BMFont_Kerning*>( MyFont->FirstKerning );
	if ( MyFont->LastKerning != 0 )
		delete_DataArray<BMFont_Kerning*>( MyFont->LastKerning );
	
	delete MyFont;
}
// - ------------------------------------------------------------------------------------------ - //
inline BMFont* new_read_BMFont( const DataBlock* InFile ) {
	cStreamReader Read( InFile->Data, InFile->Size );
	
	BMFont* MyFont = new BMFont;
	MyFont->Info = 0;
	MyFont->Common = 0;
	MyFont->PageName = 0;
	MyFont->PageNameData = 0;
	MyFont->DummyChar = 0;
	MyFont->ErrorChar = 0;
	MyFont->Chars = 0;
	MyFont->Glyph = 0;
	MyFont->Kerning = 0;
	MyFont->FirstKerning = 0;
	MyFont->LastKerning = 0;
	
	MyFont->MagicNumber = Read.GetInt();
	
	while ( !Read.IsAtEnd() ) {
		int Section = Read.GetInt(1);
		int DataSize = Read.GetInt();

		Log("* Section %i", Section );
		
		if ( Section == BMFONT_SECTION_INFO ) {
			int StringSize = (DataSize-BMFONT_INFO_SIZE_STATIC);
			MyFont->Info = (BMFont_Info*)new_Data( sizeof(BMFont_Info) + StringSize );
			
			MyFont->Info->FontSize = Read.GetInt(2);
			MyFont->Info->BitField = Read.GetInt(1);
			MyFont->Info->CharSet = Read.GetInt(1);
			MyFont->Info->StretchH = Read.GetInt(2);
			MyFont->Info->AA = Read.GetInt(1);
			MyFont->Info->PaddingUp = Read.GetInt(1);
			MyFont->Info->PaddingRight = Read.GetInt(1);
			MyFont->Info->PaddingDown = Read.GetInt(1);
			MyFont->Info->PaddingLeft = Read.GetInt(1);
			MyFont->Info->PaddingHoriz = Read.GetInt(1);
			MyFont->Info->PaddingVert = Read.GetInt(1);
			MyFont->Info->Outline = Read.GetInt(1);
			
			copy_Data( Read.GetString(StringSize), &MyFont->Info->FontName, StringSize );
			
			Log( "** Source Font Name: %s", MyFont->Info->FontName );
		}
		else if ( Section == BMFONT_SECTION_COMMON ) {
			MyFont->Common = new BMFont_Common;
			
			MyFont->Common->LineHeight = Read.GetInt(2);
			MyFont->Common->Base = Read.GetInt(2);
			MyFont->Common->ScaleW = Read.GetInt(2);
			MyFont->Common->ScaleH = Read.GetInt(2);
			MyFont->Common->Pages = Read.GetInt(2);
			MyFont->Common->BitFields = Read.GetInt(1);
			MyFont->Common->AlphaChannel = Read.GetInt(1);
			MyFont->Common->RedChannel = Read.GetInt(1);
			MyFont->Common->GreenChannel = Read.GetInt(1);
			MyFont->Common->BlueChannel = Read.GetInt(1);
		}
		else if ( Section == BMFONT_SECTION_PAGES ) {
			int PageNameLength = (int)length_String(Read.GetString(0)) + 1;
			int PageCount = DataSize / PageNameLength;
			
			Log( "** Texture Pages: %i  Page Name Length: %i (%i)", PageCount, PageNameLength, DataSize );
			
			MyFont->PageNameData = new_DataBlock( DataSize );
			copy_Data( Read.GetString(DataSize), MyFont->PageNameData->Data, DataSize );
			
			MyFont->PageName = new_DataArray<char*>( PageCount );
			
			char* PageOffset = MyFont->PageNameData->Data;
			for ( int idx = 0; idx < PageCount; idx++ ) {
				MyFont->PageName->Data[idx] = PageOffset;
				PageOffset += PageNameLength;
				Log( "*** %i - %s", idx, MyFont->PageName->Data[idx] );
			}
		}
		else if ( Section == BMFONT_SECTION_CHARS ) {
			int CharCount = DataSize / BMFONT_CHARS_SIZE;
			
			Log( "** %i characters found", CharCount );
			
			MyFont->Chars = new_DataArray<BMFont_Chars>( CharCount );
			
			for ( int idx = 0; idx < CharCount; idx ++ ) {
				MyFont->Chars->Data[idx].Id = Read.GetInt(4);
				MyFont->Chars->Data[idx].x = Read.GetInt(2);
				MyFont->Chars->Data[idx].y = Read.GetInt(2);
				MyFont->Chars->Data[idx].Width = Read.GetInt(2);
				MyFont->Chars->Data[idx].Height = Read.GetInt(2);
				MyFont->Chars->Data[idx].OffsetX = Read.GetInt(2);
				MyFont->Chars->Data[idx].OffsetY = Read.GetInt(2);
				MyFont->Chars->Data[idx].AdvanceX = Read.GetInt(2);
				MyFont->Chars->Data[idx].Page = Read.GetInt(1);
				MyFont->Chars->Data[idx].Channel = Read.GetInt(1);
				
				if ( MyFont->Chars->Data[idx].Id == -1 ) {
					MyFont->ErrorChar = &MyFont->Chars->Data[idx];
				}
			}
			
			// Create a dummy character for errors (in case one wasn't included) //
			if ( MyFont->ErrorChar == 0 ) {
				MyFont->DummyChar = new BMFont_Chars;
				MyFont->ErrorChar = MyFont->DummyChar;
				
				MyFont->DummyChar->Id = 0;
				MyFont->DummyChar->x = 0;
				MyFont->DummyChar->y = 0;
				MyFont->DummyChar->Width = 0;
				MyFont->DummyChar->Height = 0;
				MyFont->DummyChar->OffsetX = 0;
				MyFont->DummyChar->OffsetY = 0;
				MyFont->DummyChar->AdvanceX = 0;
				MyFont->DummyChar->Page = 0;
				MyFont->DummyChar->Channel = 0;
			}
			
			// ** Populate Glyphs List ** //
			// Create //
			int GlyphCount = 256;
			MyFont->Glyph = new_DataArray<BMFont_Chars*>( GlyphCount );
			
			// Empty list (ErrorChar, as it will be the included or a dummy) //
			for ( int idx = 0; idx < GlyphCount; idx ++ ) {
				MyFont->Glyph->Data[idx] = MyFont->ErrorChar;
			}
			
			// Process Chars List //
			for ( int idx = 0; idx < CharCount; idx ++ ) {
				BMFont_Chars* Data = &MyFont->Chars->Data[idx];
				int Id = MyFont->Chars->Data[idx].Id;
				if ( Id >= 0 ) {
					MyFont->Glyph->Data[ Id ] = Data;
				}
			}
		}
		else if ( Section == BMFONT_SECTION_KERNING ) {
			int KerningCount = DataSize / BMFONT_KERNING_SIZE;
			
			Log( "* %i kerning instances found", KerningCount );
			
			MyFont->Kerning = new_DataArray<BMFont_Kerning>( KerningCount );
			
			for ( int idx = 0; idx < KerningCount; idx ++ ) {
				MyFont->Kerning->Data[idx].First = Read.GetInt(4);
				MyFont->Kerning->Data[idx].Second = Read.GetInt(4);
				MyFont->Kerning->Data[idx].Amount = Read.GetInt(2);
			}
			
			// ** Populate First Kernings List ** //
			// (In theory, all kernings per character will be sorted linearly by "First") //
			// (Therefor, one just has to search linearly all kerning entries to check if a pair) //

			int GlyphCount = 256;
			MyFont->FirstKerning = new_DataArray<BMFont_Kerning*>( GlyphCount );
			MyFont->LastKerning = new_DataArray<BMFont_Kerning*>( GlyphCount );
			
			// Empty list //
			for ( int idx = 0; idx < GlyphCount; idx ++ ) {
				MyFont->FirstKerning->Data[idx] = 0;
				MyFont->LastKerning->Data[idx] = 0;
			}

			// Process Kerning List //
			for ( int idx = 0; idx < KerningCount; idx ++ ) {
				BMFont_Kerning* Data = &MyFont->Kerning->Data[idx];
				int First = MyFont->Kerning->Data[idx].First;
				if ( First >= 0 ) {
					// Only set First if it hasn't been set //
					if ( MyFont->FirstKerning->Data[ First ] == 0 ) {
						MyFont->FirstKerning->Data[ First ] = Data;
					}
					// Always set last //
					MyFont->LastKerning->Data[ First ] = Data;
				}
			}			
		}
		else {
			Log( "! Unknown BMFont Section %i", Section );
			delete_BMFont( MyFont );
			return 0;
		}
	};
	
	return MyFont;
}
// - ------------------------------------------------------------------------------------------ - //
inline BMFont* new_read_BMFont( const char* InFile ) {
	Log( "+ Reading BMFont File \"%s\"", InFile );
	DataBlock* Data = new_read_DataBlock( InFile );
	if ( Data == 0 ) {
		Log( "! BMFont File Not Found!" );
		return 0;
	}
	
	BMFont* FontData = new_read_BMFont( Data );
	delete_DataBlock( Data );

	Log( "- Done Reading BMFont File \"%s\"", InFile );

	return FontData;
}
// - ------------------------------------------------------------------------------------------ - //
inline BMFont_Common* common_BMFont( BMFont* FontData ) {
	return FontData->Common;	
}
// - ------------------------------------------------------------------------------------------ - //
inline int height_BMFont( BMFont* FontData, const char* = "", const size_t = 0 ) {
	return FontData->Common->LineHeight;	
}
// - ------------------------------------------------------------------------------------------ - //
inline int width_BMFont( BMFont* FontData, const char* Text, const size_t Length ) {
	int Width = 0;
	for ( size_t idx = 0; idx < Length; idx++ ) {
		Width += FontData->Glyph->Data[Text[idx]]->AdvanceX;
	}
	return Width;
}
// - ------------------------------------------------------------------------------------------ - //
// Return a pointer you can index like an array to access Glyph data //
inline BMFont_Chars** glyph_BMFont( BMFont* FontData ) {
	return FontData->Glyph->Data;
}
// - ------------------------------------------------------------------------------------------ - //
// Return a pointer you can index like an array to access Kerning data //
inline BMFont_Kerning** kerning_BMFont( BMFont* FontData ) {
	if ( FontData->FirstKerning )
		return FontData->FirstKerning->Data;
	else
		return 0;
}
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_Graphics_BMFont_H__ //
// - ------------------------------------------------------------------------------------------ - //
