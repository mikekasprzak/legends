//----------------------------------------------------------------------------
//
// Copyright © 2010, Intel Corporation. All rights reserved
//
// Any software source code reprinted in this document is furnished under 
// a software license and may only be used or copied in accordance with 
// the license in the Intel-EULA.rtf file installed as part of the product 
// installation
//
// File:       ClientProxy.h
//
// Contents:   This header file contains class definitions used by  
//              the library and the SDK.
//
// Notes:      Do NOT Modify this file.  Modifications may lead to application
//              failure.
//----------------------------------------------------------------------------

#ifndef CLIENTPROXY_H_
#define CLIENTPROXY_H_

#include "ApplicationId.h"
#include "ComponentId.h"
#include <string>
#include "adpcore.h"

namespace com {
	namespace intel {
		namespace adp {

			/**
			 * The ClientProxy class provides encapsulation for the ADP Core Libraries.
			 */
			class ClientProxy {
				friend class Component;
				friend class Application;

			private:
				unsigned long GetApiLevel();
				const wchar_t* GetApiVersion();
				ADP_RET_CODE Initialize();
				ADP_RET_CODE Close();
				ADP_RET_CODE IsAuthorized(ApplicationId applicationId);
				ADP_RET_CODE IsAppAuthorized(ComponentId componentId);
				ADP_RET_CODE ApplicationUpgrade(ApplicationId applicationId);
				ADP_RET_CODE ApplicationBeginEvent();
				ADP_RET_CODE ApplicationEndEvent();

			public:
			   /**
				* constructor
				*/
				ClientProxy();

				/**
				 * destructor
				 */
				virtual ~ClientProxy() throw();

				ADP_RET_CODE ReportCrash(wchar_t* pwzModuleName, wchar_t* pwzMessage, wchar_t* pwzCategory, 
					unsigned long lineNumber, wchar_t* pErrorData, ADP_CrashReportField* pCrashReportFields,
					unsigned long fieldCount);
			};
		}
	}
}

#endif /* CLIENTPROXY_H_ */
