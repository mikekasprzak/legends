//----------------------------------------------------------------------------
//
// Copyright (C) 2010, Intel Corporation. All rights reserved
//
// Any software source code reprinted in this document is furnished under 
// a software license and may only be used or copied in accordance with 
// the license in the Intel-EULA.rtf file installed as part of the product 
// installation
//
// File:       Product.h
//
// Contents:   This header file contains class definitions used by  
//              the library and the SDK.
//
// Notes:      Do NOT Modify this file.  Modifications may lead to application
//              failure.
//----------------------------------------------------------------------------

#ifndef PRODUCT_H_
#define PRODUCT_H_

#include "ClientProxy.h"

namespace com {
	namespace intel {
		namespace adp {

			/**
			 * The Product class is the root of the Intel AppUp(SM) Developer Program class
			 * hierarchy. The class, in addition to establishing static utility methods and
			 * abstract overrides, provides a static, thread-safe map that maintains the relationship
			 * between developer class types and ADP product entries.
			 * 
			 * A product can be : 
			 * <ul>
			 * <li>An application</li>
			 * <li>A component</li>
			 * </ul>
			 *
			 */
			class Product {
			protected:
				static ClientProxy* pClientProxy;
			public:
				/** 
				 * constructor for Product
				 */
				Product();

				/** 
				 * destructor for Product
				 */
				virtual ~Product();
			};
		}
	}
}

#endif /* PRODUCT_H_ */
