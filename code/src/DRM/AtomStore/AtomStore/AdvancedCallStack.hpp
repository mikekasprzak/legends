//----------------------------------------------------------------------------
//
// Copyright © 2010, Intel Corporation. All rights reserved
// 
// Any software source code reprinted in this document is furnished under 
// a software license and may only be used or copied in accordance with 
// the license in the Intel-EULA.rtf file installed as part of the product 
// installation
//
// File:       AdvancedCallStack.hpp
//
// Contents:   This header file contains class definitions used by  
//              the library and the SDK.
//
// Notes:      Do NOT Modify this file.  Modifications may lead to application
//              failure.
//----------------------------------------------------------------------------

// This symbol must only be defined if the following conditions are met:
// 1. A version of DBGHELP.DLL and DBGHELP.LIB 5.1 or later has been installed
// 2. The application is built with dbghelp.lib specified as an element in linker input
// 3. The application will be shipped with DBGHELP.DLL in it's root directory to ensure compatibility
// 4.  _ADP_ADVANCED_CRASHREPORT is defined as a preprocessor symbol in the compiler setting

#include <iostream>

namespace com {
	namespace intel {
		namespace adp {
#ifdef WIN32
	#include <windows.h>
	#pragma warning(disable : 4312 4800)
			inline CallStackEntryList& AdvancedCallStack::Parse(CONTEXT* pContext) {
				// Get handles to both the current process and thread
				HANDLE hProcess = ::GetCurrentProcess();
				HANDLE hThread = ::GetCurrentThread();

				// Initialize the DbgHelp library and our variables
				SymInitialize(hProcess, NULL, true);

				IMAGEHLP_SYMBOL64 *pSymbol = NULL;
				IMAGEHLP_MODULEW module;
				IMAGEHLP_LINEW64 line;
				STACKFRAME64 stackFrame64;
				DWORD imageType;

				memset(&stackFrame64, 0, sizeof(stackFrame64));

				imageType = IMAGE_FILE_MACHINE_I386;
				stackFrame64.AddrPC.Offset = pContext->Eip;
				stackFrame64.AddrFrame.Offset = pContext->Ebp;
				stackFrame64.AddrStack.Offset = pContext->Esp;
				stackFrame64.AddrFrame.Mode = AddrModeFlat;
				stackFrame64.AddrPC.Mode = AddrModeFlat;
				stackFrame64.AddrStack.Mode = AddrModeFlat;

				pSymbol = (IMAGEHLP_SYMBOL64 *) malloc(sizeof(IMAGEHLP_SYMBOL64)
						+ CALLSTACK_MAX_NAMELEN);

				memset(pSymbol, 0, sizeof(IMAGEHLP_SYMBOL64) + CALLSTACK_MAX_NAMELEN);
				pSymbol->SizeOfStruct = sizeof(IMAGEHLP_SYMBOL64);
				pSymbol->MaxNameLength = CALLSTACK_MAX_NAMELEN;

				memset(&line, 0, sizeof(line));
				line.SizeOfStruct = sizeof(line);

				memset(&module, 0, sizeof(module));
				module.SizeOfStruct = sizeof(module);

				bool bParse = true;
				while (bParse == true) {
					bParse = ::StackWalk64(imageType, hProcess, hThread, &stackFrame64, pContext,
						AdvancedCallStack::ReadProcessMemory, SymFunctionTableAccess64, SymGetModuleBase64, NULL);

					if (bParse == true) {
						CallStackEntry callStackEntry;

						if (stackFrame64.AddrPC.Offset == stackFrame64.AddrReturn.Offset ||
							stackFrame64.AddrReturn.Offset == 0) {
							bParse = false;
						}
						if (stackFrame64.AddrPC.Offset != 0) {
							DWORD64 offset;
							if (SymGetSymFromAddr64(hProcess, stackFrame64.AddrPC.Offset,
									&offset, pSymbol) != FALSE) {
								wchar_t buffer[CALLSTACK_MAX_NAMELEN];
								size_t converted;
								::mbstowcs_s(&converted, buffer, strlen(pSymbol->Name) + 1, pSymbol->Name, CALLSTACK_MAX_NAMELEN);
								callStackEntry.symbolName = buffer;
							}
							DWORD displacement;
							if (::SymGetLineFromAddrW64(hProcess, stackFrame64.AddrPC.Offset,
									&displacement, &line) != FALSE) {
								callStackEntry.lineNumber = line.LineNumber;
								callStackEntry.fileName = line.FileName;
							}

							if (::SymGetModuleInfoW(hProcess, (DWORD) stackFrame64.AddrPC.Offset,
									&module) != FALSE) {
								callStackEntry.moduleName = module.ModuleName;
							}
						}
						entries.push_back(callStackEntry);
					}
				}

				free(pSymbol);
				::SymCleanup(hProcess);
				return entries;
			}

			inline BOOL __stdcall AdvancedCallStack::ReadProcessMemory(HANDLE hProcess,
					DWORD64 baseAddress, PVOID pBuffer, DWORD size,
					LPDWORD bytesRead) {
				BOOL b = ::ReadProcessMemory(hProcess, (LPVOID) baseAddress,
						pBuffer, size, bytesRead);
				return b;
			}
#endif
		}
	}
}
