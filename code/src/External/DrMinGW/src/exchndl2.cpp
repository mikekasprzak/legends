/* exchndl2.cxx
 *
 * A portable way to load the EXCHNDL.DLL on startup.
 *
 * Jose Fonseca
 *
 * Modified by Mike Kasprzak
 */

#include <windows.h>

class ExceptionHandler
{
	public:
	
	ExceptionHandler()
	{
		if ( LoadLibrary("exchndl.dll") ) {
			// TODO: Something on Success
		}
	}
};

static ExceptionHandler gExceptionHandler;	//  global instance of class
