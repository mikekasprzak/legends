// - ------------------------------------------------------------------------------------------ - //
// String - Frontend and common C string functionality //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Data_String_Number_H__
#define __Library_Data_String_Number_H__
// - ------------------------------------------------------------------------------------------ - //
#include <stdio.h>
#include <stdlib.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline char* comma_String( const int Number ) {
	static char Text[32];
	char Sign[2];
	
	int AbsNumber = Number;
	if ( AbsNumber < 0 ) {
		AbsNumber = -AbsNumber;
		Sign[0] = '-';
		Sign[1] = 0;
	}
	else {
		Sign[0] = 0;
	}
	
	if ( AbsNumber < 1000 ) {
		sprintf( Text, "%s%i", Sign, AbsNumber );
	}
	else if ( AbsNumber < 1000000 ) {
		sprintf( Text, "%s%i,%03i", Sign, AbsNumber / 1000, AbsNumber % 1000 );
	}
	else if ( AbsNumber < 1000000000 ) {
		sprintf( Text, "%s%i,%03i,%03i", Sign, (AbsNumber/1000000), (AbsNumber / 1000) % 1000, AbsNumber % 1000 );
	}
	else {
		sprintf( Text, "%s%i,%03i,%03i,%03i", Sign, (AbsNumber/1000000000), (AbsNumber/1000000) % 1000, (AbsNumber / 1000) % 1000, AbsNumber % 1000 );
	}
	
	return Text;
}
// - ------------------------------------------------------------------------------------------ - //
inline char* dot_String( const int Number ) {
	static char Text[32];
	char Sign[2];
	
	int AbsNumber = Number;
	if ( AbsNumber < 0 ) {
		AbsNumber = -AbsNumber;
		Sign[0] = '-';
		Sign[1] = 0;
	}
	else {
		Sign[0] = 0;
	}
	
	if ( AbsNumber < 1000 ) {
		sprintf( Text, "%s%i", Sign, AbsNumber );
	}
	else if ( AbsNumber < 1000000 ) {
		sprintf( Text, "%s%i.%03i", Sign, AbsNumber / 1000, AbsNumber % 1000 );
	}
	else if ( AbsNumber < 1000000000 ) {
		sprintf( Text, "%s%i.%03i.%03i", Sign, (AbsNumber/1000000), (AbsNumber / 1000) % 1000, AbsNumber % 1000 );
	}
	else {
		sprintf( Text, "%s%i.%03i.%03i.%03i", Sign, (AbsNumber/1000000000), (AbsNumber/1000000) % 1000, (AbsNumber / 1000) % 1000, AbsNumber % 1000 );
	}
	
	return Text;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_String_Number_H__ //
// - ------------------------------------------------------------------------------------------ - //
