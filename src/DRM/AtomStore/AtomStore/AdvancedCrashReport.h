//----------------------------------------------------------------------------
//
// Copyright © 2010, Intel Corporation. All rights reserved
//
// Any software source code reprinted in this document is furnished under 
// a software license and may only be used or copied in accordance with 
// the license in the Intel-EULA.rtf file installed as part of the product 
// installation
//
// File:       AdvancedCrashReport.h
//
// Contents:   This header file contains class definitions used by  
//              the library and the SDK.
//
// Notes:      Do NOT Modify this file.  Modifications may lead to application
//              failure.
//----------------------------------------------------------------------------

#ifdef WIN32
#ifdef _ADP_ADVANCED_CRASHREPORT

#ifndef ADVANCEDCRASHREPORT_H_
#define ADVANCEDCRASHREPORT_H_

#include "DefaultCrashReport.h"

namespace com {
	namespace intel {
		namespace adp {

			/**
			 * Provides the default crash reporting implementation.  See AbstractCrashReport
			 * for base class implmentation details
			 */
			class AdvancedCrashReport: public DefaultCrashReport {
			public:
				AdvancedCrashReport();
			};
		}
	}
}

#include "AdvancedCrashReport.hpp"

#endif /* ADVANCEDCRASHREPORT_H_ */

#endif
#endif