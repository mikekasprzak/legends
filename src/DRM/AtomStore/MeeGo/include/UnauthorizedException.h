//----------------------------------------------------------------------------
//
// Copyright (C) 2010, Intel Corporation. All rights reserved
//
// Any software source code reprinted in this document is furnished under 
// a software license and may only be used or copied in accordance with 
// the license in the Intel-EULA.rtf file installed as part of the product 
// installation
//
// File:       UnauthorizedException.h
//
// Contents:   This header file contains class definitions used by  
//              the library and the SDK.
//
// Notes:      Do NOT Modify this file.  Modifications may lead to application
//              failure.
//----------------------------------------------------------------------------

#ifndef UNAUTHORIZEDEXCEPTION_H_
#define UNAUTHORIZEDEXCEPTION_H_

#include <exception>
#include <string>
#include "AdpErrorException.h"

using namespace std;

namespace com {
	namespace intel {
		namespace adp {

			/**
			 * This exception is thrown if an application or
			 * component is not authorized or is expired.
			 *
			 */
			class UnauthorizedException: public AdpErrorException {
			public:
				/**
				 * Constructor
				 *
				 * @param message The message describing the exception
				 * @param code (optional) The code of the error that occurred.
				 */
				UnauthorizedException(string message, int code = 0) throw();

			};
		}
	}
}

#endif /* UNAUTHORIZEDEXCEPTION_H_ */
