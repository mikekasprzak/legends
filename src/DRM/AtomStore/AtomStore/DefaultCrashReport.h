//----------------------------------------------------------------------------
//
// Copyright © 2010, Intel Corporation. All rights reserved
//
// Any software source code reprinted in this document is furnished under 
// a software license and may only be used or copied in accordance with 
// the license in the Intel-EULA.rtf file installed as part of the product 
// installation
//
// File:       DefaultCrashReport.h
//
// Contents:   This header file contains class definitions used by  
//              the library and the SDK.
//
// Notes:      Do NOT Modify this file.  Modifications may lead to application
//              failure.
//----------------------------------------------------------------------------

#ifndef DEFAULTCRASHREPORT_H_
#define DEFAULTCRASHREPORT_H_

#include "AbstractCrashReport.h"
#include "CallStack.h"

#ifdef WIN32
	#include <windows.h>
#endif

namespace com {
	namespace intel {
		namespace adp {

			/**
			 * Provides the default crash reporting implementation.  See AbstractCrashReport
			 * for base class implmentation details
			 */
			class DefaultCrashReport: public AbstractCrashReport {
			protected:
				CallStack* pCallStack;
				virtual void PopulateModuleName();
				virtual void PopulateMessage();
				virtual void PopulateErrorData();
				virtual void PopulateCategory();
				virtual void PopulateLineNumber();
				virtual void PopulateCrashReportFields();
#ifdef WIN32
				virtual void ReportCrash(ClientProxy* pClientProxy,
						struct _EXCEPTION_POINTERS *pExceptionInfo);
#else
				virtual void ReportCrash(ClientProxy* pClientProxy);
#endif

			public:
				DefaultCrashReport();
				virtual ~DefaultCrashReport();
			};
		}
	}
}

#endif /* DEFAULTCRASHREPORT_H_ */
