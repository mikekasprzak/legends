//----------------------------------------------------------------------------
//
// Copyright © 2010, Intel Corporation. All rights reserved
//
// Any software source code reprinted in this document is furnished under 
// a software license and may only be used or copied in accordance with 
// the license in the Intel-EULA.rtf file installed as part of the product 
// installation
//
// File:       Application.h
//
// Contents:   This header file contains class definitions used by  
//              the library and the SDK.
//
// Notes:      Do NOT Modify this file.  Modifications may lead to application
//              failure.
//----------------------------------------------------------------------------

#ifndef APPLICATION_H_
#define APPLICATION_H_


#include "adpcore.h"
#include "Product.h"
#include "ApplicationId.h"
#include "AdpException.h"
#include "InitializationException.h"
#include "UnauthorizedException.h"
#include "AdpRuntimeException.h"
#include "AdpWarningException.h"
#include "Mutex.h"
#include "AbstractCrashReport.h"
#include <map>

#ifdef WIN32
#include <windows.h>
#endif

using namespace std;

namespace com {
	namespace intel {
		namespace adp {

			/**
			 * Developers extend the Application class to create an app for the Atom(TM)
			 * Developer Program.  The Application class may either be extended or used
			 * as a delegate to verify authorization with the ADP environment.
			 */
			class Application: public Product {
			private:

				/**
				 * The current authorization status of the Application
				 */
 				static ADP_RET_CODE adpStatus;

				/**
				 * The mutex governing shared memory accessed in the constructor.
				 */
				static Mutex mutex;

				/**
				 * The AbstractCrashReport variable, utilized for uncaught exceptions
				 */
				static AbstractCrashReport* pCrashReport;

				/**
				 * The id of the application, assigned by the ADP program
				 */
				ApplicationId id;

			public:

			   /**
				* The constructor for Application objects.  The constructor throws the noted exceptions
				* as the basis for the authorization model for ADP applications.  In addition to authorization,
				* the Application must be a singleton in its process scope.  If an exception is caught from the
				* Application allocation attempt, the application can not run.
				*
				* @param id The ApplicationId of this application.
				* @throw InitializationException Thrown if multiple instances of an application are attempted.
				* @throw AdpRuntimeException Thrown if the runtime encounters an error.
				* @throw UnauthorizedException Thrown if the application is not authorized for execution on the current machine.
				*/
				Application(ApplicationId id);

			   /**
				* The default destructor for Application objects.
				*/
				virtual ~Application() throw();

				/**
				 * This method allows the application developer to replace the
				 * means by which application crashes are reported to the ADP
				 * system.  At the heart is the AbstractCrashReport,
				 * which features virtual methods for deriving report information.
				 *
				 * @param pCrashReporter A class based on AbstractCrashReport to publish crash report data
				 */
				static void SetCrashReport(AbstractCrashReport* pCrashReport) throw();

				/**
				 * Called to provide indication of the start of an application, which will allow
				 * the ADP system to provide meterics on application use.  If the developer invokes
				 * BeginAppEvent, they must also invoke EndAppEvent
				 *
				 * @throws AdpRuntimeException upon system error
				 */
				void BeginEvent();

				/**
				 * Called upon application shutdown if BeginEvent has been called to inform the system
				 * that application metering should be concluded
				 *
				 * @throws AdpRuntimeException upon system error
				 */
				void EndEvent();

				/**
				 * The termination handler for the application.  Installed with the
				 * underlying c++ runtime as a callback, and then invoked when
				 * the application ends unexpectedly due to an uncaught exception.
				 * The AbstractCrashReport assigned to the application will be
				 * responsible for entering a crash report to the system.
				 *
				 * See SetCrashReport
				 */
#ifndef WIN32
				static void TerminateHandler();
#else
				static ULONG WINAPI TerminateHandler(struct _EXCEPTION_POINTERS *pExceptionInfo);
#endif
				/**
				 * Returns the authorization status of the application
				 */
				static ADP_RET_CODE GetAuthorizationStatus();
			};
		}
	}
}

#endif /* APPLICATION_H_ */
