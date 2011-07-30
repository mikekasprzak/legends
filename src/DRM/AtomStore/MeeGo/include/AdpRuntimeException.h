//----------------------------------------------------------------------------
//
// Copyright (C) 2010, Intel Corporation. All rights reserved
//
// Any software source code reprinted in this document is furnished under 
// a software license and may only be used or copied in accordance with 
// the license in the Intel-EULA.rtf file installed as part of the product 
// installation
//
// File:       AdpRuntimeException.h
//
// Contents:   This header file contains class definitions used by  
//              the library and the SDK.
//
// Notes:      Do NOT Modify this file.  Modifications may lead to application
//              failure.
//----------------------------------------------------------------------------

#ifndef ADPRUNTIMEEXCEPTION_H_
#define ADPRUNTIMEEXCEPTION_H_

#include <exception>
#include <string>
#include "AdpErrorException.h"

using namespace std;

namespace com {
	namespace intel {
		namespace adp {

			/**
			 * This exception is a catch all for all errors that are not 
			 * covered by InitializationException or UnauthorizedException.
			 *
			 */
			class AdpRuntimeException: public AdpErrorException {
			public:
				/**
				 * Constructor
				 *
				 * @param message The message describing the exception
				 * @param code (optional) The code of the error that occurred.
				 */
				AdpRuntimeException(string message, int code = 0) throw();

			};
		}
	}
}

#endif /* ADPRUNTIMEEXCEPTION_H_ */
