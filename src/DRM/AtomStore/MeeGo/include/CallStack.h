//----------------------------------------------------------------------------
//
// Copyright © 2010, Intel Corporation. All rights reserved
//
// Any software source code reprinted in this document is furnished under
// a software license and may only be used or copied in accordance with
// the license in the Intel-EULA.rtf file installed as part of the product
// installation
//
// File:       CallStack.h
//
// Contents:   This header file contains class definitions used by
//              the library and the SDK.
//
// Notes:      Do NOT Modify this file.  Modifications may lead to application
//              failure.
//----------------------------------------------------------------------------

#ifndef CALLSTACK_H_
#define CALLSTACK_H_

// Only compile this code if we're on Linux, or the developer has
// ensured that the correct versions of dbghelp.lib and dgbhelp.dll
// are present.  Please see the developer's guide for more information

#include <string>
#include <sstream>
#include <list>

#define CALLSTACK_MAX_NAMELEN	1024

#ifdef WIN32
	#include <windows.h>
	#define DBGHELP_TRANSLATE_TCHAR
	#include <dbghelp.h>
#else
	#include <execinfo.h>
#endif

using namespace std;

namespace com {
	namespace intel {
		namespace adp {

			struct CallStackEntry {
				wstring fileName;
				wstring moduleName;
				wstring symbolName;
				unsigned long lineNumber;
				void* pAddress;

				CallStackEntry();
				wstring str();
			};

			typedef list<CallStackEntry> CallStackEntryList;
			typedef CallStackEntryList::iterator CallStackEntryListItr;

			class CallStack {
			protected:
				CallStackEntryList entries;
			public:
#ifdef WIN32
				/**
				 * Parse will attempt to walk the stack via the stack frame pointer in maintained by the
				 * context structure provided.
				 * 
				 * @param pContext A pointer to a CONTEXT structure representing the state of an execution thread
				 * @return A reference to a CallStackEntryList built during the stack traversal.
				 */
				virtual CallStackEntryList& Parse(CONTEXT* pContext);
#else
				/**
				 * Parse will attempt to get the backtrace information from libc.
				 * If the application is linked with -rdynamic, the method will have access to symbols,
				 * line numbers, in addition to module info and addresses.  If -rdynamic is not used in
				 * linkage, only module name and addresses will be available.
				 */
				CallStackEntryList& Parse();
#endif
				/**
				 * Returns a reference to the call stack entry list
				 * @return The reference to the list of CallStackEntry elements
				 */
				CallStackEntryList& GetEntries();
			};
		}
	}
}

#endif /* CALLSTACK_H_ */
