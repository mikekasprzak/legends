
#include <stdio.h>
#include <stdlib.h>

#include "Net.h"

int main( int argc, char* argv[] ) {
	printf( "Start!\n" );
	
	netInit();
	
	const char* CountryHostName =  "syk-country.appspot.com";
	const char* ServerHostName =  "sykhronics.com";

	fflush( 0 );

//	{
//		char* Data = netGetHTTPData( CountryHostName );
//		printf( "Country Data: \n%s\n", Data );
//		netDeleteHTTPData( Data );
//	}
	
	{
		char* Data = netPostHTTPData( ServerHostName, "action=update&Address=1.1.1.1&Port=10240&Version=100" );
		printf( "Data: \n%s\n", Data );
		netDeleteHTTPData( Data );
	}

	netExit();

	return 0;	
}
