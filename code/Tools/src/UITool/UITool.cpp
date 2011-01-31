// - ------------------------------------------------------------------------------------------ - //
#include <vector>
#include <string>
#include <map>
// - ------------------------------------------------------------------------------------------ - //
#include <Core/DataBlock.h>
#include <Core/GelArray.h>
#include <Core/GelHeap.h>
#include <Core/File.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Util/WhitespaceTokenizer/WhitespaceTokenizer.h>
#include <Debug/Log.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Game/UIElement.h>
// - ------------------------------------------------------------------------------------------ - //
// -- FILE FORMAT GUIDE -- //
// .sc files are a chunked binary format.  Each chunk is a 4 byte size followed by a 4 byte //
// identifyer string.  The Size is the number of bytes above the 8 bytes used to describe a chunk.//
// At the start of the file is a dummy zero sized chunk "SCRN". //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
class cGraphic {
public:
	std::string File;
	short TextureWidth, TextureHeight;
	
	// NOTE: This can safely be shorts, since it's coordinates are *always* inside a texture //
	union {
		struct {
			short x,y;
			short w,h;
		};
		int Slice[2];
	};
};
// - ------------------------------------------------------------------------------------------ - //
class cView {
public:
	int ElementIndex;

	// These need to be int's since a view can possibly be a virtual view that requires scrolling //
	union {
		int Data[4];
		struct {	
			int x1,y1;
			int x2,y2;	
		};
	};
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
class cUIFile {
public:
	std::vector<cUIElement> Element;
	std::vector< std::vector< cGraphic > > Graphic;	
	std::vector< std::vector< std::string > > Text;
		
	std::vector< cView > View;
	std::vector< int > Meta;
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
cUIFile UIFile;

int MaxRecursion = 10;
char Spacer[11] = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 0 };
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#define NO_ELEMENTS_ERROR() \
	if ( Element == 0 ) { \
		Log( "Error:%i: %s with no Elements\n", File.CurrentLine, File.StringToken().c_str() ); \
		return -1; \
	}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
int Alignment;
int Flags;

cUIElement* Element;
int BaseX;
int BaseY;

float BaseScale;
// - ------------------------------------------------------------------------------------------ - //
int TextureWidth;
int TextureHeight;
std::string GraphicFile;
cGraphic* Graphic;
std::vector< cGraphic >* GraphicSet;
// - ------------------------------------------------------------------------------------------ - //
int Font;
std::string* Text;
std::vector< std::string >* TextSet;
// - ------------------------------------------------------------------------------------------ - //
cView* View;
int DefaultMeta;
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
int PopulateUI( const char* FileName, const int Depth = 0 ) {
	// Bail if we've recursively gone too deep //
	if ( Depth == MaxRecursion ) {
		Log( "Error: Recursion broke %i levels (%i)... \n", Depth, MaxRecursion );
		return -3;
	}
	
	cWhitespaceTokenizer File;
	
	// Only on the first depth level, set initial values //
	if ( Depth == 0 ) {
		// Default Variables (Element) //
		Alignment = UIA_DEFAULT;
		Flags = 0;
		
		Element = 0;
		BaseX = 0;
		BaseY = 0;
		
		BaseScale = 1;
	
		// Default Variables (Graphic) //
		GraphicSet = 0;
		TextureWidth = 512;
		TextureHeight = 512;
		Graphic = 0;
	
		// Default Variables (Text) //
		Font = 1;
		Text = 0;
		TextSet = 0;

		// Default Variables (View) //
		View = 0;
		
		// Per-View Default Meta Value //
		DefaultMeta = 0;
	}

	
	// If file exists //
	if ( File.Load( FileName ) ) {
		// For every line of the file //
		do {
			Log("%s%02i - %s\n", &Spacer[MaxRecursion-Depth], File.CurrentLine, File.GetLine() );
			
			// Test the first token - Recursive include --------------------------------------- - //
			if ( File.IsStringToken("Include") ) {
				File.NextToken();
				int Error = PopulateUI( File.StringToken().c_str(), Depth + 1 );
				if ( Error )
					return Error;
			}
			// Create new Elements ------------------------------------------------------------ - //
			else if ( File.IsStringToken("Element") ) {
				File.NextToken();
				// What kind of element we're starting //
				if ( File.IsStringToken("Text") ) {
					if ( TextSet == 0 ) {
						Log( "Error:%i: \"Element %s\" with no Texts\n", File.CurrentLine, File.StringToken().c_str() );
						return -1;
					}
					if ( Text == 0 ) {
						Log( "Error:%i: \"Element %s\" with no Text Strings\n", File.CurrentLine, File.StringToken().c_str() );
						return -1;
					}

					UIFile.Element.push_back( cUIElement() );
					Element = &UIFile.Element.back();

					Element->Type = UI_TEXT;
					Element->Flags = Alignment | Flags;
					Element->x = BaseX;
					Element->y = BaseY;
					Element->Scale = BaseScale;
					
					Element->DataIndex = UIFile.Text.size() - 1;
					
					Element->FontIndex = Font;
					Element->_PAD3 = 0;
					Element->_PAD4 = 0;
				}
				else if ( File.IsStringToken("Graphic") ) {
					if ( GraphicSet == 0 ) {
						Log( "Error:%i: \"Element %s\" with no Graphics\n", File.CurrentLine, File.StringToken().c_str() );
						return -1;
					}
					if ( Graphic == 0 ) {
						Log( "Error:%i: \"Element %s\" with no Graphic Shapes\n", File.CurrentLine, File.StringToken().c_str() );
						return -1;
					}
					
					UIFile.Element.push_back( cUIElement() );
					Element = &UIFile.Element.back();

					Element->Type = UI_GRAPHIC;
					Element->Flags = Alignment | Flags;
					Element->x = BaseX;
					Element->y = BaseY;
					Element->Scale = BaseScale;
					
					Element->DataIndex = UIFile.Graphic.size() - 1;
					
					Element->_PAD2 = 0;
					Element->_PAD3 = 0;
					Element->_PAD4 = 0;
				}
				else if ( File.IsStringToken("Dummy") ) {
					UIFile.Element.push_back( cUIElement() );
					Element = &UIFile.Element.back();

					Element->Type = UI_DUMMY;
					Element->Flags = Alignment | Flags;
					Element->x = BaseX;
					Element->y = BaseY;
					Element->Scale = BaseScale;
					
					Element->_PAD1 = 0;
					Element->_PAD2 = 0;
					Element->_PAD3 = 0;
					Element->_PAD4 = 0;
				}
				else {
					Log( "Error:%i: Unknown Element \"%s\"\n", File.CurrentLine, File.StringToken().c_str() );
					return -1;
				}
			}
			// Element Modifier Commands ------------------------------------------------------ - //
			else if ( File.IsStringToken("Align") ) {
				NO_ELEMENTS_ERROR();

				int NewAlignment = Element->Flags & 0xfff0;
				
				// Horizontal //
				File.NextToken();
				if ( File.IsStringToken("Center") ) {
					NewAlignment |= UIA_HCENTER;
				}
				else if ( File.IsStringToken("Left") ) {
					NewAlignment |= UIA_HLEFT;
				}
				else if ( File.IsStringToken("Right") ) {
					NewAlignment |= UIA_HRIGHT;
				}
				else if ( File.IsStringToken("Top") ) {
					NewAlignment |= UIA_VTOP;
				}
				else if ( File.IsStringToken("Bottom") ) {
					NewAlignment |= UIA_VBOTTOM;
				}
				else if ( File.IsStringToken("") ) {
					NewAlignment |= UIA_HCENTER;
				}
				else {
					Log( "Error:%i: Unknown Alignment \"%s\"\n", File.CurrentLine, File.StringToken().c_str() );
					return -1;
				}

				// Vertical //
				File.NextToken();
				if ( File.IsStringToken("Center") ) {
					NewAlignment |= UIA_VCENTER;
				}
				else if ( File.IsStringToken("Left") ) {
					NewAlignment |= UIA_HLEFT;
				}
				else if ( File.IsStringToken("Right") ) {
					NewAlignment |= UIA_HRIGHT;
				}
				else if ( File.IsStringToken("Top") ) {
					NewAlignment |= UIA_VTOP;
				}
				else if ( File.IsStringToken("Bottom") ) {
					NewAlignment |= UIA_VBOTTOM;
				}
				else if ( File.IsStringToken("") ) {
					NewAlignment |= UIA_VCENTER;
				}
				else {
					Log( "Error:%i: Unknown Alignment \"%s\"\n", File.CurrentLine, File.StringToken().c_str() );
					return -1;
				}
				
				// Set the Alignment //
				Element->Flags = NewAlignment;
			}
			else if ( File.IsStringToken("Scale") ) {
				NO_ELEMENTS_ERROR();
				
				File.NextToken();
				Element->Scale = File.FloatToken();
			}
			else if ( File.IsStringToken("Value") ) {
				NO_ELEMENTS_ERROR();
				
				File.NextToken();
				Element->Value = File.IntegerToken();
			}
			else if ( File.IsStringToken("Font") ) {
				NO_ELEMENTS_ERROR();
				
				File.NextToken();
				Element->FontIndex = File.IntegerToken();
			}
			else if ( File.IsStringToken("DataIndex") ) {
				NO_ELEMENTS_ERROR();
				
				File.NextToken();
				Element->DataIndex = File.IntegerToken();
			}
			else if ( File.IsStringToken("Range") ) {
				NO_ELEMENTS_ERROR();

				File.NextToken();
				Element->Min = File.StepIntegerToken();
				Element->Max = File.IntegerToken();
				Element->Flags |= UIF_RANGE;
			}
			else if ( File.IsStringToken("Pos") ) {
				NO_ELEMENTS_ERROR();

				File.NextToken();
				Element->x = File.StepIntegerToken();
				Element->y = File.IntegerToken();
			}
			else if ( File.IsStringToken("AddPos") ) {
				NO_ELEMENTS_ERROR();

				File.NextToken();
				Element->x += File.StepIntegerToken();
				Element->y += File.IntegerToken();
			}
			else if ( File.IsStringToken("Invisible") ) {
				NO_ELEMENTS_ERROR();
				
				File.NextToken();
				Element->Flags |= UIF_INVISIBLE;
			}
			else if ( File.IsStringToken("NoSort") ) {
				NO_ELEMENTS_ERROR();
				
				File.NextToken();
				Element->Flags |= UIF_NOSORT;
			}
			else if ( File.IsStringToken("Variable") ) {
				NO_ELEMENTS_ERROR();
				
				File.NextToken();
				Element->Flags |= UIF_VARIABLE;
			}
			
			// Commands that affect global element settings ----------------------------------- - //
			else if ( File.IsStringToken("SetPos") ) {
				File.NextToken();
				BaseX = File.StepIntegerToken();
				BaseY = File.IntegerToken();
			}
			else if ( File.IsStringToken("SetScale") ) {
				File.NextToken();
				BaseScale = File.FloatToken();
			}
			else if ( File.IsStringToken("ResetPos") ) {
				BaseX = 0;
				BaseY = 0;
			}
			else if ( File.IsStringToken("ResetScale") ) {
				BaseScale = 1;
			}
			else if ( File.IsStringToken("SetInvisible") ) {
				File.NextToken();
				Flags |= UIF_INVISIBLE;
			}
			else if ( File.IsStringToken("SetNoSort") ) {
				File.NextToken();
				Flags |= UIF_NOSORT;
			}
			else if ( File.IsStringToken("SetAlign") ) {
				int NewAlignment = 0;
				
				// Horizontal //
				File.NextToken();
				if ( File.IsStringToken("Center") ) {
					NewAlignment |= UIA_HCENTER;
				}
				else if ( File.IsStringToken("Left") ) {
					NewAlignment |= UIA_HLEFT;
				}
				else if ( File.IsStringToken("Right") ) {
					NewAlignment |= UIA_HRIGHT;
				}
				else if ( File.IsStringToken("Top") ) {
					NewAlignment |= UIA_VTOP;
				}
				else if ( File.IsStringToken("Bottom") ) {
					NewAlignment |= UIA_VBOTTOM;
				}
				else if ( File.IsStringToken("") ) {
					NewAlignment |= UIA_HCENTER;
				}
				else {
					Log( "Error:%i: Unknown Alignment \"%s\"\n", File.CurrentLine, File.StringToken().c_str() );
					return -1;
				}

				// Vertical //
				File.NextToken();
				if ( File.IsStringToken("Center") ) {
					NewAlignment |= UIA_VCENTER;
				}
				else if ( File.IsStringToken("Left") ) {
					NewAlignment |= UIA_HLEFT;
				}
				else if ( File.IsStringToken("Right") ) {
					NewAlignment |= UIA_HRIGHT;
				}
				else if ( File.IsStringToken("Top") ) {
					NewAlignment |= UIA_VTOP;
				}
				else if ( File.IsStringToken("Bottom") ) {
					NewAlignment |= UIA_VBOTTOM;
				}
				else if ( File.IsStringToken("") ) {
					NewAlignment |= UIA_VCENTER;
				}
				else {
					Log( "Error:%i: Unknown Alignment \"%s\"\n", File.CurrentLine, File.StringToken().c_str() );
					return -1;
				}
				
				// Set the Alignment //
				Alignment = NewAlignment;
			}
			
			// Create a new Graphic ----------------------------------------------------------- - //
			else if ( File.IsStringToken("Graphic") ) {
				File.NextToken();

				UIFile.Graphic.push_back( std::vector< cGraphic >() );
				GraphicSet = &UIFile.Graphic.back();
				Graphic = 0;
				
				if ( File.IsTokenAvailable() ) {
					TextureWidth = File.StepIntegerToken();
					TextureHeight = File.IntegerToken();
				}
			}
			else if ( File.IsStringToken("SetImage") ) {
				File.NextToken();
				GraphicFile = File.StepStringToken();
				
				if ( File.IsTokenAvailable() ) {
					TextureWidth = File.StepIntegerToken();
					TextureHeight = File.IntegerToken();
				}
			}
			else if ( File.IsStringToken("SetImageShape") ) {
				File.NextToken();
				TextureWidth = File.StepIntegerToken();
				TextureHeight = File.IntegerToken();
			}
			else if ( File.IsStringToken("Shape") ) {
				File.NextToken();

				GraphicSet->push_back( cGraphic() );
				Graphic = &GraphicSet->back();
				
				Graphic->File = GraphicFile;
								
				Graphic->TextureWidth = TextureWidth;
				Graphic->TextureHeight = TextureHeight;
				
				if ( File.IsTokenAvailable() ) {
					Graphic->x = File.StepIntegerToken();
					Graphic->y = File.StepIntegerToken();
					Graphic->w = File.StepIntegerToken();
					Graphic->h = File.StepIntegerToken();
				}
				else {
					Graphic->x = 0;
					Graphic->y = 0;
					Graphic->w = TextureWidth;
					Graphic->h = TextureHeight;
				}
			}

			// Create a new String Table ------------------------------------------------------ - //
			else if ( File.IsStringToken("Text") ) {
				File.NextToken();

				UIFile.Text.push_back( std::vector< std::string >() );
				TextSet = &UIFile.Text.back();
				Text = 0;
			}
			else if ( File.IsStringToken("String") ) {
				File.NextToken();

				TextSet->push_back( File.StringToken() );
				Text = &TextSet->back();
			}
			else if ( File.IsStringToken("SetFont") ) {
				File.NextToken();
				Font = File.IntegerToken();
			}
			
			// Create a new View -------------------------------------------------------------- - //
			else if ( File.IsStringToken("AddView") ) {
				if ( Element == 0 ) {
					Log( "Error:%i: %s with no Elements\n", File.CurrentLine, File.StringToken().c_str() );
					return -1;
				}

				File.NextToken();

				UIFile.View.push_back( cView() );
				View = &UIFile.View.back();
				
				View->ElementIndex = UIFile.Element.size() - 1;
				
				UIFile.Meta.push_back( DefaultMeta );
				
				int Width;
				int Height;
				
				if ( File.IsTokenAvailable() ) {
					Width = File.StepIntegerToken();
					Height = File.StepIntegerToken();
				}
				else {
					Width = (*GraphicSet)[ Element->Value ].w;
					Height = (*GraphicSet)[ Element->Value ].h;
				}
				
				int HalfWidth = Width >> 1;
				int HalfHeight = Height >> 1;
				
				// X Axis //
				if ( (Element->Flags & UIA_HMASK) == UIA_HLEFT ) {
					View->x1 = Element->x;
					View->x2 = Element->x + Width;
				}
				else if ( (Element->Flags & UIA_HMASK) == UIA_HRIGHT ) {
					View->x1 = Element->x - Width;
					View->x2 = Element->x;
				}
				else {
					View->x1 = Element->x - HalfWidth;
					View->x2 = Element->x + HalfWidth;
				}
				
				// Y Axis //
				if ( (Element->Flags & UIA_VMASK) == UIA_VTOP ) {
					View->y1 = Element->y;
					View->y2 = Element->y + Height;
				}
				else if ( (Element->Flags & UIA_VMASK) == UIA_VBOTTOM ) {
					View->y1 = Element->y - Height;
					View->y2 = Element->y;
				}
				else {
					View->y1 = Element->y - HalfHeight;
					View->y2 = Element->y + HalfHeight;
				}
			}
			else if ( File.IsStringToken("AddExplicitView") ) {
				if ( Element == 0 ) {
					Log( "Error:%i: %s with no Elements\n", File.CurrentLine, File.StringToken().c_str() );
					return -1;
				}

				File.NextToken();

				UIFile.View.push_back( cView() );
				View = &UIFile.View.back();
				
				UIFile.Meta.push_back( DefaultMeta );
				
				View->ElementIndex = UIFile.Element.size() - 1;
				View->x1 = File.StepIntegerToken();
				View->y1 = File.StepIntegerToken();
				View->x2 = View->x1 + File.StepIntegerToken();
				View->y2 = View->y2 + File.StepIntegerToken();
			}
			else if ( File.IsStringToken("Meta") ) {
				File.NextToken();
				UIFile.Meta.back() = File.IntegerToken();
			}
			else if ( File.IsStringToken("SetDefaultMeta") ) {
				File.NextToken();
				DefaultMeta = File.IntegerToken();
			}
			
			// Catch all Warning for unsupported commands ------------------------------------- - //
			else {
				Log( "Warning:%i: Unknown Command: \"%s\"\n", File.CurrentLine, File.StringToken().c_str() );
			}
		} while ( File.NextLine() );
		
		return 0;
	}
	
	Log("Error: Input File not found \"%s\"\n", FileName );
	return -2;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
int main( int argc, char* argv[] ) {
	if ( argc < 3 ) {
		Log( "UITool - Convert a .sc (screen) file to a binary screen file\n" );
		Log( "  Usage: UITool In.sc Out.sc.bin\n" );
		return -1;
	}
	
	// Read File //
	{
		int Error = PopulateUI( argv[1] );
		if ( Error )
			return Error;
	}
	
	// TEMP: Write Contents, to verify if reading works //
	{
		Log("----------------------------------------------\n");
		Log("Elements:\n");
		for ( size_t idx = 0; idx < UIFile.Element.size(); idx++ ) {
			cUIElement& Element = UIFile.Element[idx];
			Log( "%02i - Flags=%i x=%i y=%i - Value=%i (%i->%i) - Scale=%0.02f - %i %i %i\n",
				Element.Type,
				Element.Flags,
				Element.x,
				Element.y,
				Element.Value,
				Element.Min,
				Element.Max,
				Element.Scale,
				Element._PAD1,
				Element._PAD2,
				Element._PAD3
				);
		}
		Log("----------------------------------------------\n");
		Log("Graphics:\n");
		for ( size_t idx = 0; idx < UIFile.Graphic.size(); idx++ ) {
			for ( size_t idx2 = 0; idx2 < UIFile.Graphic[idx].size(); idx2++ ) {
				cGraphic& Graphic = UIFile.Graphic[idx][idx2];
				
				Log( "%02i-%02i - %s (%i, %i) - xy(%i, %i) wh(%i, %i)\n",
					idx,
					idx2,
					Graphic.File.c_str(),
					Graphic.TextureWidth,
					Graphic.TextureHeight,
					Graphic.x,
					Graphic.y,
					Graphic.w,
					Graphic.h
					);
			}
		}
		Log("----------------------------------------------\n");
		Log("Strings:\n");
		for ( size_t idx = 0; idx < UIFile.Text.size(); idx++ ) {
			for ( size_t idx2 = 0; idx2 < UIFile.Text[idx].size(); idx2++ ) {
				std::string& Text = UIFile.Text[idx][idx2];
				
				Log( "%02i-%02i - %s\n",
					idx,
					idx2,
					Text.c_str()
					);
			}
		}
		Log("----------------------------------------------\n");
		Log("Views:\n");
		for ( size_t idx = 0; idx < UIFile.View.size(); idx++ ) {
			cView& View = UIFile.View[idx];
			
			Log( "%02i - Element=%i - v1(%i, %i) v2(%i, %i)\n",
				idx,
				View.ElementIndex,
				View.x1,
				View.y1,
				View.x2,
				View.y2
				);
		}
		Log("----------------------------------------------\n");
		Log("Meta Data (One per view):\n");
		for ( size_t idx = 0; idx < UIFile.Meta.size(); idx++ ) {
			
			Log( "%02i - Meta = %i\n",
				idx,
				UIFile.Meta[idx]
				);
		}
	}
	

	Log( "----------------------------------------------\n");
	Log( "Writing: %s\n",  argv[2] );
	
	// Write File //
	{
		FILE* File = open_writeonly_File( argv[2] );
		
		// Dummy Screen File Chunk //		
		write_File<int>(File, 0 );
		write_File(File, "SCRN", 4 );
		
		
		// UI Element Chunk Header //
		write_File<int>(File, (sizeof(cUIElement) * UIFile.Element.size()) + 4 );
		write_File(File, "ELEM", 4 );
		// UI Element Chunk //
		write_File<int>(File, UIFile.Element.size() );
		write_File(File, (char*)&UIFile.Element[0], sizeof(cUIElement) * UIFile.Element.size() );


		// Build a string table of texture names //
		{
			typedef std::map<std::string, int > TableType;
			TableType Table;
			std::vector<std::string> UniqueStrings;
			int TotalLength = 0;
			int ChunkSize = 0;
			int GraphicCount = 0;

			// Build Table, and accumulate sizes //
			for ( size_t idx = 0; idx < UIFile.Graphic.size(); idx++ ) {
				for ( size_t idx2 = 0; idx2 < UIFile.Graphic[idx].size(); idx2++ ) {
					GraphicCount++;
					//Log( "%i-%i\n", idx, idx2 );
					if ( Table.find( UIFile.Graphic[idx][idx2].File ) == Table.end() ) {
						//Log( "%s\n", UIFile.Graphic[idx][idx2].File.c_str() );
						
						// Store the offset to this string //
						Table[ UIFile.Graphic[idx][idx2].File ] = TotalLength;
						UniqueStrings.push_back( UIFile.Graphic[idx][idx2].File );
						TotalLength += UIFile.Graphic[idx][idx2].File.length() + 1;
					}
				}
			}

			// Graphic String Table Chunk Header //
			int AlignedTotalLength = TotalLength & (-1 ^ 3);
			if ( TotalLength != AlignedTotalLength )
				AlignedTotalLength += 4;
			
			write_File<int>(File, AlignedTotalLength );
			write_File(File, "GR_S", 4 );
			// Graphic String Table Chunk //
			for ( std::vector<std::string>::iterator idx = UniqueStrings.begin(); idx != UniqueStrings.end(); idx++ ) {
				write_File(File, idx->c_str(), idx->length() + 1 );
			}
			// Pad the Chunk //
			if ( TotalLength != AlignedTotalLength )
				fill_File<char>(File, 0, 4 - (TotalLength & 3) );
			
			// Graphic Element Chunk Header //
			write_File<int>(File, GraphicCount * 16 );
			write_File(File, "GR_E", 4 );
			// Graphic Element Chunk //
			for ( size_t idx = 0; idx < UIFile.Graphic.size(); idx++ ) {
				for ( size_t idx2 = 0; idx2 < UIFile.Graphic[idx].size(); idx2++ ) {
					// Write the Offset In to the String Table //
					write_File<int>(File, Table[ UIFile.Graphic[idx][idx2].File ] );
					// Write the Texture Dimensions //
					write_File<short>(File, UIFile.Graphic[idx][idx2].TextureWidth );
					write_File<short>(File, UIFile.Graphic[idx][idx2].TextureHeight );
					// Write the Slice //
					write_File(File, (char*)&UIFile.Graphic[idx][idx2].Slice[0], sizeof(short) * 4 );
				}
			}
			
			// Graphic Chunk Header //
			write_File<int>(File, UIFile.Graphic.size() * sizeof(int) );
			write_File(File, "GRCH", 4 );
			// Graphic Chunk //
			int GraphicElements = 0;
			for ( size_t idx = 0; idx < UIFile.Graphic.size(); idx++ ) {
				write_File<int>(File, GraphicElements );
				GraphicElements += UIFile.Graphic[idx].size();
				
				//write_File<int>(File, UIFile.Graphic.size() );
			}			
		}

		// Build a string table of strings //
		{
			typedef std::map<std::string, int > TableType;
			TableType Table;
			std::vector<std::string> UniqueStrings;
			int TotalLength = 0;
			int ChunkSize = 0;
			int TextCount = 0;

			// Build Table, and accumulate sizes //
			for ( size_t idx = 0; idx < UIFile.Text.size(); idx++ ) {
				for ( size_t idx2 = 0; idx2 < UIFile.Text[idx].size(); idx2++ ) {
					TextCount++;
					//Log( "%i-%i\n", idx, idx2 );
					if ( Table.find( UIFile.Text[idx][idx2] ) == Table.end() ) {
						//Log( "%s\n", UIFile.Graphic[idx][idx2].File.c_str() );
						
						// Store the offset to this string //
						Table[ UIFile.Text[idx][idx2] ] = TotalLength;
						UniqueStrings.push_back( UIFile.Text[idx][idx2] );
						TotalLength += UIFile.Text[idx][idx2].length() + 1;
					}
				}
			}

			// Text String Table Chunk Header //
			int AlignedTotalLength = TotalLength & (3 ^ -1);
			if ( TotalLength != AlignedTotalLength )
				AlignedTotalLength += 4;
			
			write_File<int>(File, AlignedTotalLength );
			write_File(File, "TX_S", 4 );
			// Text String Table Chunk //
			for ( std::vector<std::string>::iterator idx = UniqueStrings.begin(); idx != UniqueStrings.end(); idx++ ) {
				write_File(File, idx->c_str(), idx->length() + 1 );
			}
			// Pad the Chunk //
			if ( TotalLength != AlignedTotalLength )
				fill_File<char>(File, 0, 4 - (TotalLength & 3) );

			// Text Element Chunk Header //
			write_File<int>(File, TextCount * 4 );
			write_File(File, "TX_E", 4 );
			// Text Element Chunk //
			for ( size_t idx = 0; idx < UIFile.Text.size(); idx++ ) {
				for ( size_t idx2 = 0; idx2 < UIFile.Text[idx].size(); idx2++ ) {
					// Write the Offset In to the String Table //
					write_File<int>(File, Table[ UIFile.Text[idx][idx2] ] );
				}
			}

			// Text Chunk Header //
			write_File<int>(File, UIFile.Text.size() * sizeof(int) );
			write_File(File, "TXCH", 4 );
			// Text Chunk //
			int TextElements = 0;
			for ( size_t idx = 0; idx < UIFile.Text.size(); idx++ ) {
				write_File<int>(File, TextElements );
				TextElements += UIFile.Text[idx].size();
				
				//write_File<int>(File, UIFile.Text.size() );
			}
		}

		// View Chunk Header //
		write_File<int>(File, sizeof(int) * 4 * UIFile.View.size() + 4 );
		write_File(File, "VIEW", 4 );
		// View Chunk //
		write_File<int>(File, UIFile.View.size() ); // NOTE: For compatibility with PairView //
		for ( size_t idx = 0; idx < UIFile.View.size(); idx++ ) {
			write_File(File, (char*)&UIFile.View[idx].Data[0], sizeof(int) * 4 );
		}

		// View Link Chunk Header //
		write_File<int>(File, sizeof(int) * UIFile.View.size() );
		write_File(File, "VIEL", 4 );
		// View Link Chunk //
		for ( size_t idx = 0; idx < UIFile.View.size(); idx++ ) {
			write_File<int>(File, UIFile.View[idx].ElementIndex);
		}

		// View Meta Data Chunk Header //
		write_File<int>(File, (sizeof(int) * UIFile.Meta.size()) );
		write_File(File, "META", 4 );
		// Meta Chunk //
		for ( size_t idx = 0; idx < UIFile.Meta.size(); idx++ ) {
			write_File<int>(File, UIFile.Meta[idx]);
		}

		// END Chunk Header //
		write_File<int>(File, 0 );
		write_File(File, "END ", 4 );
		
		close_File( File );
	}
	
	// Exit with success //
	return 0;
}
// - ------------------------------------------------------------------------------------------ - //
