//----------------------------------------------------------------------------
//
// Copyright © 2010, Intel Corporation. All rights reserved
//
// Any software source code reprinted in this document is furnished under 
// a software license and may only be used or copied in accordance with 
// the license in the Intel-EULA.rtf file installed as part of the product 
// installation
//
// File:       ComponentId.h
//
// Contents:   This header file contains class definitions used by  
//              the library and the SDK.
//
// Notes:      Do NOT Modify this file.  Modifications may lead to application
//              failure.
//----------------------------------------------------------------------------

#ifndef COMPONENTID_H_
#define COMPONENTID_H_

#include <string>
#include <memory.h>
#include "adpcore.h"

using namespace std;

namespace com {
	namespace intel {
		namespace adp {

			/**
			 * A unique identifier for a Intel AppUp(SM) Developer Program component. 
			 */
			class ComponentId: public ADP_COMPONENTID {
			private:
				string strId;
				char* pszId;
			public:

				/** 
				 * Default constructor for ComponentId
				 */
				ComponentId();

				/**
				 * A constructor accepting 4 unsigned longs.  These values are
				 * assigned by ADP as part of the submission process.
				 *
				 * @param l0 The first long of the ID
				 * @param l1 The second long of the ID
				 * @param l2 The third long of the ID
				 * @param l3 The fourth long of the ID
				 */
				ComponentId(unsigned long l0, unsigned long l1, unsigned long l2,
							unsigned long l3);

				/**
				 * Copy Constructor
				 */
				ComponentId(const ComponentId& rId);

				/**
				 * A constructor receiving a C style ID
				 */
				ComponentId(const ADP_COMPONENTID& id);

				/**
				 * Destructor for ComponentId
				 */
				virtual ~ComponentId();

				/**
				 * @return The raw data array of the ID
				 */
				const unsigned long* GetData();

				/**
				 * Sets the raw data of the ID
				 */
				void SetData(long l1, long l2, long l3, long l4);

				/**
				 * Returns the ComponentId as a string
				 * @return string version of ComponentId
				 */
				string& str();

				/**
				 * Logical equals overload
				 * @param id A const ComponentId reference
				 * @return true if the local and reference copies contain identical state
				 */
				bool operator==(const ComponentId& id);

				/**
				 * Logical not equals overload
				 * @param id A const ComponentId reference
				 *
				 * @return true if the local and reference copies contain identical state
				 */
				bool operator!=(const ComponentId& id);

				/**
				 * Assignment operator overload
				 *
				 * @param id A constant ComponentId reference
				 * @return A reference to the local value after assignment (for cascading)
				 */
				ComponentId& operator=(ComponentId& id);

				/**
				 * Conversion operator to const char*.  This allows the syntax of 
				 * (const char*) ComponentId
				 */
				operator const char*(); 

				/**
				 * Conversion operator to string.  This allows the syntax of (string) ComponentId
				 */
				operator string();

			};
		}
	}
}

#endif /* COMPONENTID_H_ */
