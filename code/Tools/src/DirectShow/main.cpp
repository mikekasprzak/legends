
#include <stdio.h>
#include <Dshow.h>

int main( int argc, char* argv[] ) {
	printf( "Lets Capture!\n" );
	
	// Initialize COM //
	HRESULT hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);

    if ( SUCCEEDED(hr) ) {
    	printf( "COM Initialized\n" );
    	
    	
    	
		CoUninitialize();
    }
	return 0;
}
