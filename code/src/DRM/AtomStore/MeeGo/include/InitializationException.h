//----------------------------------------------------------------------------
//
// Copyright (C) 2010, Intel Corporation. All rights reserved
//
// Any software source code reprinted in this document is furnished under 
// a software license and may only be used or copied in accordance with 
// the license in the Intel-EULA.rtf file installed as part of the product 
// installation
//
// File:       InitializationException.h
//
// Contents:   This header file contains class definitions used by  
//              the library and the SDK.
//
// Notes:      Do NOT Modify this file.  Modifications may lead to application
//              failure.
//----------------------------------------------------------------------------

#ifndef INITIALIZATIONEXCEPTION_H_
#define INITIALIZATIONEXCEPTION_H_

#include <exception>
#include <string>
#include "AdpErrorException.h"

using namespace std;

namespace com {
	namespace intel {
		namespace adp {

			/**
			 * This exception is thrown if the developer does not invoke the Atom
			 * Developer Program initialization method prior to invoking any other Atom
			 * Developer Program method.  It can also be called if a Component is
			 * instanciated before the Application object.
			 *
			 */
			class InitializationException: public AdpErrorException {
			public:
				/**
				 * Constructor
				 *
				 * @param message The message describing the exception
				 * @param code (optional) The code of the error that occurred.
				 */
				InitializationException(string message, int code = 0) throw();

			};
		}
	}
}

#endif /* INITIALIZATIONEXCEPTION_H_ */
