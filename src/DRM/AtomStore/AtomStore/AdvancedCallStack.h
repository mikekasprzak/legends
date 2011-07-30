//----------------------------------------------------------------------------
//
// Copyright © 2010, Intel Corporation. All rights reserved
//
// Any software source code reprinted in this document is furnished under
// a software license and may only be used or copied in accordance with
// the license in the Intel-EULA.rtf file installed as part of the product
// installation
//
// File:       AdvancedCallStack.h
//
// Contents:   This header file contains class definitions used by
//              the library and the SDK.
//
// Notes:      Do NOT Modify this file.  Modifications may lead to application
//              failure.
//----------------------------------------------------------------------------

#ifdef WIN32
#ifdef _ADP_ADVANCED_CRASHREPORT

#ifndef ADVANCEDCALLSTACK_H_
#define ADVANCEDCALLSTACK_H_


#include "CallStack.h"

namespace com {
	namespace intel {
		namespace adp {

			class AdvancedCallStack: public CallStack {
			public:
				/**
				 * Parse will attempt to walk the stack via the Microsoft system library, DBGHELP.LIB.
				 * If successful, the internal private list, entries, will be populated with CallStackEntry
				 * elements.  These elements can provide critical information to the developer in the event
				 * of an application crash.  These elements are used by DefaultCrashReport when notifying the
				 * ADP system of such an event.
				 */
				virtual CallStackEntryList& Parse(CONTEXT* pContext);
				static BOOL __stdcall ReadProcessMemory(HANDLE hProcess,
					DWORD64 baseAddress, PVOID pBuffer, DWORD size,
					LPDWORD numberOfBytesRead);
			};
		}
	}
}

#include "AdvancedCallStack.hpp"

#endif /* CALLSTACK_H_ */
#endif /* _ADP_ADVANCED_CRASHREPORT */
#endif /* WIN32 */
