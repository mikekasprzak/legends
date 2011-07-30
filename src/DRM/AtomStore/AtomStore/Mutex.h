//----------------------------------------------------------------------------
//
// Copyright (C) 2010, Intel Corporation. All rights reserved
//
// Any software source code reprinted in this document is furnished under 
// a software license and may only be used or copied in accordance with 
// the license in the Intel-EULA.rtf file installed as part of the product 
// installation
//
// File:       Mutex.h
//
// Contents:   This header file contains class definitions used by  
//              the library and the SDK.
//
// Notes:      Do NOT Modify this file.  Modifications may lead to application
//              failure.
//----------------------------------------------------------------------------

#ifndef MUTEX_H_
#define MUTEX_H_

#ifndef WIN32
	#include <pthread.h>
	#define MutexHandle pthread_mutex_t
#else
	#include <windows.h>
	#include <process.h>
	#define MutexHandle HANDLE
#endif

namespace com {
	namespace intel {
		namespace adp {

			/**
			 * Mutex - Ensures thread safe access to shared resources and memory
			 *
			 */
			class Mutex {
			private:
				MutexHandle handle;
			public:
				/**
 				 * constructor
				 */
				Mutex();

				/**
				 * destructor
				 */
				virtual ~Mutex();

				/**
				 * Lock
				 */
				int Lock();

				/**
				 * unlock
				 */
				int Unlock();
			};
		}
	}
}

#endif /* MUTEX_H_ */
