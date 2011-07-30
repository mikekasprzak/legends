//----------------------------------------------------------------------------
//
// Copyright © 2010, Intel Corporation. All rights reserved
//
// Any software source code reprinted in this document is furnished under 
// a software license and may only be used or copied in accordance with 
// the license in the Intel-EULA.rtf file installed as part of the product 
// installation
//
// File:       ApplicationId.h
//
// Contents:   This header file contains class definitions used by  
//              the library and the SDK.
//
// Notes:      Do NOT Modify this file.  Modifications may lead to application
//              failure.
//----------------------------------------------------------------------------

#ifndef APPLICATIONID_H_
#define APPLICATIONID_H_

#include <string>
#include <memory.h>
#include "adpcore.h"

using namespace std;

namespace com {
	namespace intel {
		namespace adp {

			/**
			 * A unique identifier for a Intel AppUp(SM) Developer Program application. 
			 */
			class ApplicationId: public ADP_APPLICATIONID {
			private:
				string strId;
			public:

				/** 
				 * Default constructor for ApplicationId
				 */
				ApplicationId();

				/**
				 * A constructor accepting 4 unsigned longs
				 */
				ApplicationId(unsigned long l1, unsigned long l2, unsigned long l3,
							unsigned long l4);

				/**
				 * A constructor accepting a C style ID
				 */
				ApplicationId(ADP_APPLICATIONID);

				/**
				 * Copy Constructor
				 */
				ApplicationId(const ApplicationId &rId);

				/**
				 * Destructor for ApplicationId
				 */
				virtual ~ApplicationId();

				/**
				 * @return The raw byte array of the ID
				 */
				const unsigned long* GetData();

				/**
				 * Returns the ApplicationId as a string
				 * @return string version of ApplicationId
				 */
				string& str();

								/**
				 * Logical equals overload
				 * @param A const ApplicationId reference
				 * @return true if the local and reference copies contain identical state
				 */
				bool operator==(const ApplicationId& id);

				/**
				 * Logical not-equals overload
				 * 
				 * @param A constant ApplicationId reference
				 * @return true if the local and argument copies have identical state
				 */
				bool operator!=(const ApplicationId& id);

				/**
				 * Assignment operator overload
				 *
				 * @param id A constant ApplicationId reference
				 * @return A reference to the local value (for cascading)
				 */
				ApplicationId& operator=(const ApplicationId& id);

				/**
				 * Conversion operator to const char*.  This allows the syntax of 
				 * (const char*) ApplicationId
				 */
				operator const char*(); 

				/**
				 * Conversion operator to string.  This allows the syntax of 
				 * (string) ApplicationId
				 */
				operator string(); 

			};
		}
	}
}

#endif /* APPLICATIONID_H_ */
