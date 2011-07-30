// - ------------------------------------------------------------------------------------------ - //
// GelContentTreeHandle - Directory wrapping utility library for finding assets //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_GELCore_GelContentTreeHandle_H__
#define __Library_GELCore_GelContentTreeHandle_H__
// - ------------------------------------------------------------------------------------------ - //
#include "GelDirectory.h"

typedef GelDirectory GelContentTreeHandle;

inline const size_t add_GelDirectory( GelDirectory* p, const char* _String ) {
inline const size_t size_GelDirectory( const GelDirectory* p ) {
inline const char* index_GelDirectory( const GelDirectory* p, const size_t Index ) { 
inline GelDirectory* new_GelDirectory() {
inline void delete_GelDirectory( GelDirectory* p ) {
inline GelDirectory* new_GelDirectory( GelDirectory* p, const char* Pattern ) {
inline void init_GelDirectory() {
inline void exit_GelDirectory() {
inline void populate_GelDirectory( GelDirectory* p, const char* SearchDirectory, const char* Prefix ) {
inline void populate_GelDirectory( GelDirectory* p ) {
inline GelDirectory* new_GelDirectory( const char* _BaseName ) {


//// Utilities for associating FileIO methods with the function types
//#include "File_MakeHandleUtil.h"
//#include "File_ReadWriteUtil.h"
//
//// TODO: Some method of making GelContentHandle Read-only //
//MAKE_GEL_FILE_HANDLE_FUNCTIONS( GelFile, GelContentHandle );
//MAKE_GEL_FILE_READWRITE_UTIL_FUNCTIONS( GelContentHandle );
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_GELCore_GelContentTreeHandle_H__ //
// - ------------------------------------------------------------------------------------------ - //
