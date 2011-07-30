//----------------------------------------------------------------------------
//
// Copyright © 2010, Intel Corporation. All rights reserved
//
// Any software source code reprinted in this document is furnished under 
// a software license and may only be used or copied in accordance with 
// the license in the Intel-EULA.rtf file installed as part of the product 
// installation
//
// File:       Component.h
//
// Contents:   This header file contains class definitions used by  
//              the library and the SDK.
//
// Notes:      Do NOT Modify this file.  Modifications may lead to application
//              failure.
//----------------------------------------------------------------------------

#ifndef COMPONENT_H_
#define COMPONENT_H_

#include "Product.h"
#include "ComponentEntry.h"
#include "ComponentId.h"
#include "Mutex.h"
#include <map>


using namespace std;

namespace com {
	namespace intel {
		namespace adp {

			/**
			 * Developers extend the Component class to create a component for the Atom(TM)
			 * Developer Program. 
			 */
			class Component: public Product {
				friend class Application;
			private:

				/**
				 * The component map, storing the authorization status of each component type
				 */
				static ComponentEntryMap componentMap;

				/**
				 * The mutex governing the shared componentMap resource, making it threadsafe
				 */
				static Mutex mutex;

				/**
				 * Called when the application is closing by the application
				 * The method performs static clean up not applicable to an instance
				 * destructor
				 */
				static void OnClose() throw();

			public:

				/**
				 * The constructor to create a component. Performs authorization on the Component
				 * validating the license, as well as ensuring that the component is operating in a valid
				 * runtime environment.  If the component is not authorized to execute in its application
				 * environment, an exception is thrown.
				 * 
				 * @param componentId The ComponentId for this component, an ID either assigned by the developer store upon submission, or set to a debug value.
				 * @throws UnauthorizedException Thrown if the Component class is unauthorized
				 * @throws InitializationException Thrown if the Component class has been instantiated before the application object
				 * @throws AdpRuntimeException Thrown if the ADP runtime environemt has been corrupted
				 */
				Component(ComponentId id);

				/**
				 * Returns the response from the ADP system indicating the 
				 * authorization status of the component
				 *
				 * @param the ComponentId of the Component
				 */
				static ADP_RET_CODE GetAuthorizationStatus(ComponentId& id);

			};
		}
	}
}

#endif /* COMPONENT_H_ */
