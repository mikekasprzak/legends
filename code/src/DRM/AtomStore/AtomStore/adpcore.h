//----------------------------------------------------------------------------
//
// Copyright (C) 2010, Intel Corporation. All rights reserved
// Any software source code reprinted in this document is furnished under a 
// software license and may only be used or copied in accordance with the 
// license in the Intel-EULA.rtf file installed as part of the product
// installation.
//
//
// File:       adpcore.h
//
// Contents:   This header file contains constants and defines used by  
//              the library and can be used by the SDK user.
//
// Notes:      Do NOT Modify this file.  Modifications may lead to application
//              failure.
// Misc:		You can find usage example at the bottom
//----------------------------------------------------------------------------

#ifndef _ADPLIBRARY_H
#define _ADPLIBRARY_H

///<summary> Constants for Intel(R) Atom(TM) Development Program SDK </summary>
typedef enum ADP_RET_CODE_LIST {
	ADP_FAILURE = -1,
	ADP_SUCCESS = 0,
	ADP_NOT_INITIALIZED = 1, 
	ADP_NOT_AVAILABLE = 2,
	ADP_INCOMPATIBLE_VERSION = 3,
	ADP_ERR_DATA_TOO_BIG = 4,
	ADP_AUTHORIZED = 5,
	ADP_NOT_AUTHORIZED = 6,
	ADP_AUTHORIZATION_EXPIRED = 7,
	ADP_NO_APP_BEGIN_EVENT = 8,
	ADP_TIMEOUT = 9
} ADP_RET_CODE;


// ID type definitions - they could change in the future versions independently, 
// so it is highly recommended to use the proper type for the given ID parameter.
#define ADP_IDSIZE 4
typedef unsigned long ADP_IDELEMENT;
// Application ID
typedef struct {                
	ADP_IDELEMENT field[ADP_IDSIZE];         		
} ADP_APPLICATIONID;      
// Componenet ID
typedef struct {
	ADP_IDELEMENT field[ADP_IDSIZE];
} ADP_COMPONENTID;					

/// <summary> Function prototypes for Intel(R) Atom(TM) Development Program SDK </summary>

#ifdef __cplusplus
extern "C" {
#endif

	/// <summary> Define structure for custom crash report field </summary>
	typedef struct {
		wchar_t *name;
		wchar_t *value;
	} ADP_CrashReportField;

	extern const wchar_t* ADP_API_VERSION ;
	extern const unsigned long ADP_API_LEVEL;

	extern const ADP_APPLICATIONID ADP_DEBUG_APPLICATIONID;
	extern const ADP_COMPONENTID ADP_DEBUG_COMPONENTID; 
	extern const ADP_APPLICATIONID ADP_EXPIRED_APPLICATIONID; 
	extern const ADP_COMPONENTID ADP_EXPIRED_COMPONENTID;
	
	///<summary> Set up internal data structures, and determine whether the system 
	/// is compatible.</summary>
	extern ADP_RET_CODE ADP_Initialize( void );

	///<summary> Release internal data structures, and shutdown connections
	/// used by the library. </summary>
	extern ADP_RET_CODE ADP_Close( void );

	///<summary> Check the application is authorized to run. </summary>
	///<parm name = "ApplicationGUID"> App ID <param>
	///<returns> Return one of the return codes of ADP_RET_CODE </returns>
	extern ADP_RET_CODE ADP_IsAuthorized(
		ADP_APPLICATIONID ApplicationGUID);

	///<summary> Check the component is authorized to use. </summary>
	///<parm name = "ComponentGUID"> Component ID <param>
	///<returns> Return one of the return codes of ADP_RET_CODE </returns>
	extern ADP_RET_CODE ADP_IsAppAuthorized(
		ADP_COMPONENTID ComponentGUID);

	///<summary> An application to report a crash. </summary>
	///<parm name = "Module"> Where the error/crash occurred <param>
	///<parm name = "LineNumber"> The line where error/crash occurred <param>
	///<parm name = "Message"> A short message describing the error <param>
	///<parm name = "Category"> A text field that can be used for sorting and grouping <param>
	///<parm name = "ErrorData"> The detailed error data <param>
	///<parm name = "ErrorDataSize"> The size of data <param>
	///<parm name = "CustomFields"> The customized data field <param>
	///<parm name = "CustomFieldNumber"> The number of customized data fields <param>
	///<returns> Return one of the return codes of ADP_RET_CODE </returns>
	extern ADP_RET_CODE ADP_ReportCrash(
		const wchar_t 		*Module,
		unsigned long 		LineNumber,
		const wchar_t 		*Message,
		const wchar_t       *Category,
		const wchar_t 		*ErrorData,
		unsigned long 		ErrorDataSize,
		ADP_CrashReportField *CustomFields,
		unsigned long CustomFieldNumber
		);

	///<summary> Start an application instrumentation. </summary>
	extern ADP_RET_CODE ADP_ApplicationBeginEvent();

	///<summary> Stop an application instrumentation. </summary>
	extern ADP_RET_CODE ADP_ApplicationEndEvent();

#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif

#endif //_ADPLIBRARY_H

