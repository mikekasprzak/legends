//----------------------------------------------------------------------------
//
// Copyright (C) 2010, Intel Corporation. All rights reserved
//
// Any software source code reprinted in this document is furnished under 
// a software license and may only be used or copied in accordance with 
// the license in the Intel-EULA.rtf file installed as part of the product 
// installation
//
// File:       ComponentEntry.h
//
// Contents:   This header file contains class definitions used by  
//              the library and the SDK.
//
// Notes:      Do NOT Modify this file.  Modifications may lead to application
//              failure.
//----------------------------------------------------------------------------

#ifndef COMPONENTENTRY_H_
#define COMPONENTENTRY_H_

#include "adpcore.h"
#include "ComponentId.h"
#include <string>
#include <map>

using namespace std;

namespace com {
	namespace intel {
		namespace adp {

			/**
			 * The ComponentEntry class provides a structure to record the
			 * Class, AuthorizationStatus, and AdpGuid of a given
			 * Product
			 * 
			 */
			class ComponentEntry {
			private:
				ComponentId id;
				ADP_RET_CODE status;
			public:
				/**
				 * The default constructor
				 */
				ComponentEntry();

				/**
				 * @param id the ComponentId to set
				 * @param packageName the name for the package
				 * @param status the authorization status for this package
				 */
				ComponentEntry(ComponentId id, ADP_RET_CODE status);


				/**
				 * the destructor
				 */
				virtual ~ComponentEntry();

				/**
				 * @return the ComponentId
				 */
				ComponentId GetId();

				/**
				 * @param ComponentId the id to set for this component
				 */
				void SetId(ComponentId id);

				/**
				 * @return the status
				 */
				ADP_RET_CODE GetStatus();

				/**
				 * @param status the status to set
				 */
				void SetStatus(ADP_RET_CODE status);
			};

			typedef map<string, ComponentEntry*> ComponentEntryMap;
			typedef map<string, ComponentEntry*>::iterator ComponentEntryMapItr;
		}
	}
}

#endif /* COMPONENTENTRY_H_ */
