
#include <stdio.h>
//#include <fstream>

#include <Core/DataBlock.h>
#include <Core/GelFile.h>

using namespace std;

int main( int argc, char* argv[] ) {
	if ( argc == 1 ) {
		printf( "You did it wrong!\n" );
		return -1;
	}
	
	char Text[4096];
	sprintf( Text, "%s.js", argv[1] );
	
	DataBlock* InData = new_read_DataBlock( argv[1] );
	GelFile* OutFile = open_writeonly_GelFile( Text );
	
	sprintf( Text, "var ContentMapData = " );	
	write_GelFile( OutFile, Text, strlen( Text ) );
	
//	write_DataBlock( InData, OutFile );
	write_GelFile( OutFile, InData->Data, InData->Size );

	sprintf( Text, ";" );	
	write_GelFile( OutFile, Text, strlen( Text ) );
	
	close_GelFile( OutFile );
	delete_DataBlock( InData );
		
	return 0;
}
