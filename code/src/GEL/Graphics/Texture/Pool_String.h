// - ------------------------------------------------------------------------------------------ - //
#ifndef __GLGraphics_Pool_String_H__
#define __GLGraphics_Pool_String_H__
// - ------------------------------------------------------------------------------------------ - //
#include <string>
// - ------------------------------------------------------------------------------------------ - //
const char Slash = '/';
const char OtherSlash = '\\';
const char Dot = '.';
const char Dash = '-';
// - ------------------------------------------------------------------------------------------ - //
// Return the File-Name part of a string //
inline std::string FileName( const std::string& _FileName ) {
	// Find the last slash //
	size_t SlashPos = _FileName.rfind( Slash );
	
	if ( SlashPos == std::string::npos ) {
		// Slash not found //
		return _FileName;
	}
	
	// Return the entire string after the slash position //
	return _FileName.substr( SlashPos + 1 );
}
// - ------------------------------------------------------------------------------------------ - //
// Return the Directory part of a string, including the slash //
inline std::string DirectorySlash( const std::string& _FileName ) {
	// Find the last slash //
	size_t SlashPos = _FileName.rfind( Slash );
	
	if ( SlashPos == std::string::npos ) {
		// Slash not found //
		return "";
	}
	
	// Return the entire string before the slash position //
	return _FileName.substr( 0, SlashPos + 1 - 0 );
}	
// - ------------------------------------------------------------------------------------------ - //
// Return the base name (filename without extensions) of the filename //
inline std::string BaseName( const std::string& _FileName ) {
	std::string WorkString = FileName( _FileName );
		
	// Find the first dot //
	size_t DotPos = WorkString.find( Dot );
	
	if ( DotPos == std::string::npos ) {
		// Dot not found //
		return WorkString;
	}
	
	// Return the entire string before the first period //
	return WorkString.substr( 0, DotPos - 0 );
}
// - ------------------------------------------------------------------------------------------ - //
// Return all but the direct Extensions //
inline std::string NoExtensions( const std::string& _FileName ) {
	// Return the entire string after excluding the file extensions //
	return DirectorySlash( _FileName ) + BaseName( _FileName );
}	
// - ------------------------------------------------------------------------------------------ - //
#endif // __GLGraphics_Pool_String_H__ //
// - ------------------------------------------------------------------------------------------ - //
