//----------------------------------------------------------------------------
//
// Copyright © 2010, Intel Corporation. All rights reserved
//
// Any software source code reprinted in this document is furnished under 
// a software license and may only be used or copied in accordance with 
// the license in the Intel-EULA.rtf file installed as part of the product 
// installation
//
// File:       AdpErrorException.h
//
// Contents:   This header file contains class definitions used by  
//              the library and the SDK.
//
// Notes:      Do NOT Modify this file.  Modifications may lead to application
//              failure.
//----------------------------------------------------------------------------

#ifndef ADPERROREXCEPTION_H_
#define ADPERROREXCEPTION_H_

#include <exception>
#include <sstream>
#include <AdpException.h>

using namespace std;

namespace com {
	namespace intel {
		namespace adp {

			/**
			 * The base class of ADP exceptions.  The exception includes information
			 * on the message of the exception, which provides the direct nature of the
			 * issue, as well as the code of the exception.  
			 *
			 * When contacting Intel(R) support on an issue related to this exception, please
			 * have the exception type, message, and code ready.
			 */

			class AdpErrorException: public AdpException 
			{
			public:
				/**
				 * A constructor that takes the message and code of the exception
				 */
				AdpErrorException(string message, long code = 0) throw();
			};
		}
	}
}

#endif /* ADPERROREXCEPTION_H_ */
