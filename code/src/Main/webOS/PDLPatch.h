// - ------------------------------------------------------------------------------------------ - //
#ifndef __PDLPATCH_H__
#define __PDLPATCH_H__
// - ------------------------------------------------------------------------------------------ - //
#include <PDL.h>
// - ------------------------------------------------------------------------------------------ - //
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus //
// - ------------------------------------------------------------------------------------------ - //
PDL_Err WebOS_PDL_Init(unsigned int flags);
PDL_Err WebOS_PDL_GetDataFilePath(const char *dataFileName, char *buffer, int bufferLen);
PDL_Err WebOS_PDL_GetCallingPath(const char *buffer, int bufferLen);

//int WebOS_PDL_GetHardwareID(void);

int WebOS_PDL_isAppLicensedForDevice(const char *appid);

PDL_Err WebOS_145Patch_GetDataFilePath( const char *dataFileName, char *buffer, int bufferLen);
PDL_Err WebOS_140Patch_GetDataFilePath( const char *dataFileName, char *buffer, int bufferLen);
// - ------------------------------------------------------------------------------------------ - //
#ifdef __cplusplus
};
#endif // __cplusplus //
// - ------------------------------------------------------------------------------------------ - //
#endif // __PDLPATCH_H__ //
// - ------------------------------------------------------------------------------------------ - //
