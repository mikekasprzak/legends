//----------------------------------------------------------------------------
//
// Copyright © 2010, Intel Corporation. All rights reserved
//
// Any software source code reprinted in this document is furnished under 
// a software license and may only be used or copied in accordance with 
// the license in the Intel-EULA.rtf file installed as part of the product 
// installation
//
// File:       AdpException.h
//
// Contents:   This header file contains class definitions used by  
//              the library and the SDK.
//
// Notes:      Do NOT Modify this file.  Modifications may lead to application
//              failure.
//----------------------------------------------------------------------------

#ifndef ADPEXCEPTION_H_
#define ADPEXCEPTION_H_

#include <exception>
#include <sstream>

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

			class AdpException: public exception {
			private:
				string	_message;
				long	_code;
				string	_what;
			public:
				/**
				 * A constructor that takes the message and code of the exception
				 */
				AdpException(string message, long code = 0) throw();

				/**
				 * The virtual destructor for the exception
				 */
				virtual ~AdpException() throw();

				/**
				 * Call this method to retrieve the text string reason for the exception
				 * The retreived string contains the message and causal return code
				 * @return a string containing the message and RET_CODE of the exception
				 */
				const char* what() const throw();

				/**
				 * Returns the message of the exception
				 * @return The exception message
				 */
				const char* message();

				/**
				 * Returns the code of the exception, may be a RET_CODE value
				 * @return The long code of the exception
				 */
				long code();

				/**
				 * Overloaded cascade operator to work with cout
				 *
				 * @param os A reference to an ostream object
				 * @param e A reference to an AdpException object
				 * @return A reference to a wcout (wiostream) object
				 */
				friend ostream& operator <<(ostream& os, const AdpException& e);

				/**
				 * Overloaded cascade operator to work with wcout
				 *
				 * @param os A reference to an os object
				 * @param e A reference to an AdpException object
				 * @return A reference to a wcout (wiostream) object
				 */
				friend wostream& operator <<(wostream& os, const AdpException& e);
			};
		}
	}
}

#endif /* ADPEXCEPTION_H_ */
