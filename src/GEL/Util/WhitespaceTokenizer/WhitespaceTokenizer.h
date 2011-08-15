// - ------------------------------------------------------------------------------------------ - //
// A class that, given a string, breaks it down in to elements //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __WhitespaceTokenizer_H__
#define __WhitespaceTokenizer_H__
// - ------------------------------------------------------------------------------------------ - //
#include <sstream>
#include <string>
#include <stdlib.h>

#include <Core/DataBlock.h>
// - ------------------------------------------------------------------------------------------ - //
class cWhitespaceTokenizer {
	std::stringstream Data;
	std::stringstream Line;
	std::string CurrentToken;
public:
	int CurrentLine;

	// - -------------------------------------------------------------------------------------- - //
	inline cWhitespaceTokenizer() :
		CurrentLine(0)
	{
	}
	// - -------------------------------------------------------------------------------------- - //
	inline cWhitespaceTokenizer( const char* FileName ) {
		Load( FileName );
	}
	// - -------------------------------------------------------------------------------------- - //
	inline cWhitespaceTokenizer( const DataBlock* Block ) {
		Load( Block );
	}
	// - -------------------------------------------------------------------------------------- - //
	inline bool Load( const DataBlock* Block ) {
		CurrentLine = 0;
		
		Data.clear();
		Data << std::string( (const char*)Block->Data, Block->Size );
		
		// Process the next (first) line //
		NextLine();
		
		return true;
	}	// - -------------------------------------------------------------------------------------- - //
	inline bool Load( const char* FileName ) {
		CurrentLine = 0;
		
		DataBlock* Block = new_read_DataBlock( FileName );
		if ( Block == 0 )
			return false;
		Data.clear();
		Data << std::string( (char*)Block->Data, Block->Size );
		delete_DataBlock( Block );
		
		// Process the next (first) line //
		NextLine();
		
		return true;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline bool Save( const char* FileName ) {
		DataBlock* Block = copy_DataBlock( Data.str().data(), Data.str().size() );
		bool Error = write_DataBlock( Block, FileName ) != 0;
		delete_DataBlock(Block);
		
		return Error;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline void Clear() {
		Data.clear();
	}
	// - -------------------------------------------------------------------------------------- - //
	inline std::stringstream& Write() {
		return Data;
	}
	// - -------------------------------------------------------------------------------------- - //		

public:
	// - -------------------------------------------------------------------------------------- - //
	// Steps the tokenizer to the next line, returns false if no lines left //
	inline bool NextLine() {
		bool FoundToken;
		
		// Loop until we're sure we find a line with a usable token //
		do {
			// Grab a whole line in to a string //
			std::string TempString;
			TempString.clear();
			getline( Data, TempString );
			Line.str( "" );
			Line.clear();
			Line << TempString;
			
			// Read the next token //
			FoundToken = NextToken();
			
			// In case we happen to breach the end of Data, no token found //
			if ( Data.eof() )
				return false;
			
			CurrentLine++;
		} while ( !FoundToken );
		
		// Token found //
		return true;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Steps the tokenizer to the next token on this line, returns false if no tokens left //
	inline bool NextToken() {
		// Store the stream position, just in case //
		std::streampos Position = Line.tellg();
		
		// Grab the next token of the line //
		CurrentToken = "";
		Line >> CurrentToken;
		
		// If the token begins with a quote, it's a string //
		// NOTE: multi-line strings not supported.  \" not supported either. //
		if ( CurrentToken[0] == '\"' ) {
			// Undo the step //
			Line.seekg( Position );
			
			// Seek out the first quote (hack) //
			getline( Line, CurrentToken, '\"' );
			
			// Store the contents up until the 2nd quote //
			getline( Line, CurrentToken, '\"' );
		}
		// If the token begins with a "/" //
		else if ( CurrentToken[0] == '/' ) {
			// If it's followed by a 2nd "/", it's a C++ line comment //
			if ( CurrentToken[1] == '/' ) {
				// Jump to the end of the line //
				Line.seekg( 0, std::ios_base::end );
				// Return that we failed to find a suitable token //
				return false;
			}
			// Note: Block comments would only work for a singe line, without a flag. //
		}
			
		return !Line.eof();
	}
	// - -------------------------------------------------------------------------------------- - //	
	// Returns true if the next token exists //
	inline bool IsTokenAvailable() const {
		return !Line.eof();
	}
	// - -------------------------------------------------------------------------------------- - //	
	// Returns true if the next token exists //
	inline const char* GetLine() const {
		return Line.str().c_str();
	}
	// - -------------------------------------------------------------------------------------- - //

public:
	// - -------------------------------------------------------------------------------------- - //
	// Tests if the current token matches a pattern //
	inline bool IsStringToken( const char* Pattern ) const {
		return CurrentToken == std::string( Pattern );
	}
	
	// Returns the current token as a string //
	inline const std::string StringToken() const {
		return CurrentToken;
	}
	
	// Returns the current token as a string, and steps to the next token //
	inline const std::string StepStringToken() {
		const std::string Token = StringToken();
		NextToken();
		return Token;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Tests if the current token matches a pattern //
	inline bool IsIntegerToken( const int Pattern ) const {
		return atoi(CurrentToken.c_str()) == Pattern;
	}
	
	// Returns the current token as an Integer //
	inline const int IntegerToken() const {
		return atoi(CurrentToken.c_str());
	}
	
	// Returns the current token as an Integer, and steps to the next token //
	inline const int StepIntegerToken() {
		const int Token = IntegerToken();
		NextToken();
		return Token;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Tests if the current token matches a pattern //
	inline bool IsFloatToken( const float Pattern ) const {
		return atof(CurrentToken.c_str()) == Pattern;
	}
	
	// Returns the current token as a Float //
	inline const float FloatToken() const {
		return (float)atof(CurrentToken.c_str());
	}
	
	// Returns the current token as a Float, and steps to the next token //
	inline const float StepFloatToken() {
		const float Token = FloatToken();
		NextToken();
		return Token;
	}
	// - -------------------------------------------------------------------------------------- - //
};

// - ------------------------------------------------------------------------------------------ - //
#undef _PREFIX
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __WhitespaceTokenizer_H__ //
// - ------------------------------------------------------------------------------------------ - //
