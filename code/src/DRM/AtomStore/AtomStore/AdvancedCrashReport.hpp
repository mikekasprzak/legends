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

using namespace std;

#include "AdvancedCallStack.h"

namespace com {
	namespace intel {
		namespace adp {
			inline AdvancedCrashReport::AdvancedCrashReport() {
				pCallStack = new AdvancedCallStack;
				wchar_t* pTemp = L"An application fault occurred!";
				::wcscpy_s(message, wcslen(pTemp) + 1, pTemp);

				pTemp = L"N/A";
				::wcscpy_s(module, wcslen(pTemp) + 1, pTemp);

				pTemp = L"N/A";
				::wcscpy_s(module, wcslen(pTemp) + 1, pTemp);

				pTemp = L"Unknown Exception";
				::wcscpy_s(module, wcslen(pTemp) + 1, pTemp);

				lineNumber = 0;
			}
		}
	}
}
