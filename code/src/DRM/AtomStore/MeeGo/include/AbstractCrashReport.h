//----------------------------------------------------------------------------
//
// Copyright © 2010, Intel Corporation. All rights reserved
// 
// Any software source code reprinted in this document is furnished under 
// a software license and may only be used or copied in accordance with 
// the license in the Intel-EULA.rtf file installed as part of the product 
// installation
//
// File:       AbstractCrashReport.h
//
// Contents:   This header file contains class definitions used by  
//              the library and the SDK.
//
// Notes:      Do NOT Modify this file.  Modifications may lead to application
//              failure.
//----------------------------------------------------------------------------

#ifndef AbstractCrashReport_H_
#define AbstractCrashReport_H_

#include "ClientProxy.h"

#ifdef WIN32
#include <windows.h>
#endif

namespace com {
	namespace intel {
		namespace adp {

			/**
			 * AbstractCrashReport defines the abstract base class for exception
			 * reporting.  The application developer may subclass this, overriding
			 * the methods GetModuleName, GetMessage, GetErrorData,
			 * GetLineNumber, GetCrashReportFields, and GetCrashReportFieldCount
			 * to provide the ReportCrash method with the data it needs to send a report to
			 * the ADP system.  Reports will be made available to the developer to help diagnose
			 * issues that occur with their application out in the field.
			 */
			class AbstractCrashReport {
				friend class Application;
			protected:
				wchar_t module[80];
				wchar_t message[80];
				wchar_t category[80];
				wchar_t errorData[4000];
				long    lineNumber;
				ADP_CrashReportField* pCrashReportFields;
				long    crashReportFieldCount;

#ifdef WIN32
				struct _EXCEPTION_POINTERS *pExceptionInfo;
#else
                                int signal;
#endif
				/**
				 * A pure virtual method to populate the module name for the report
				 */
				virtual void PopulateCategory() = 0;			

				/**
				 * A pure virtual method to populate the message field for the report
				 */
				virtual void PopulateMessage() = 0;

				/**
				 * A pure virtual method to populate the module name for the report
				 */
				virtual void PopulateModuleName() = 0;

				/**
				 * A pure virtual method to populate the error data field for the report
				 */
				virtual void PopulateErrorData() = 0;

				/**
				 * A pure virtual method to populate the CrashReportField array for the report.
				 */
				virtual void PopulateCrashReportFields() = 0;

				/**
				 * A pure virtual method to populate the line number for the report.
				 */
				virtual void PopulateLineNumber() = 0;

			protected:

				/**
				 * The protected method to file the report.  The logic of this method will call
				 * into the abstract methods to retrieve the data for the report.  This method
				 * is called by the Application upon an uncaught exception in the main
				 * application thread.
				 */
#ifdef WIN32
				virtual void ReportCrash(ClientProxy* pClientProxy,
						struct _EXCEPTION_POINTERS *pExceptionInfo);
#else
                                virtual void ReportCrash(ClientProxy* pClientProxy, int signal);
#endif
			public:
				/**
				 * The constructor for AbstractCrashReport, currently just
				 * a placeholder
				 */
				AbstractCrashReport();

				/**
				 * The destructor for AbstractCrashReport.  If the internal
				 * array pointer to CrashReportRecord has been initialized, the
				 * destructor will free the allocated memory.
				 */
				virtual ~AbstractCrashReport();
			};
		}
	}
}

#endif /* AbstractCrashReport_H_ */
