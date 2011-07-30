// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_GELCore_File_MakeHandleUtil_H__
#define __Library_GELCore_File_MakeHandleUtil_H__
// - ------------------------------------------------------------------------------------------ - //
#define MAKE_GEL_FILE_HANDLEINIT_FUNCTIONS( _TYPE, _NEW ) \
\
inline void init_##_NEW() { \
	init_##_TYPE(); \
} \
\
inline void exit_##_NEW() { \
	exit_##_TYPE(); \
} \
// - ------------------------------------------------------------------------------------------ - //
#define MAKE_GEL_FILE_HANDLE_FUNCTIONS( _TYPE, _NEW ) \
\
typedef _TYPE _NEW; \
\
inline _NEW* open_##_NEW( const char* _FileName, const char* _OpenMask = "rb" ) { \
	return (_NEW*)open_##_TYPE( _FileName, _OpenMask ); \
} \
\
inline _NEW* open_readonly_##_NEW( const char* _FileName ) { \
	return (_NEW*)open_readonly_##_TYPE( _FileName ); \
} \
\
inline _NEW* open_writeonly_##_NEW( const char* _FileName ) { \
	return (_NEW*)open_writeonly_##_TYPE( _FileName ); \
} \
\
inline _NEW* open_appendonly_##_NEW( const char* _FileName ) { \
	return (_NEW*)open_appendonly_##_TYPE( _FileName ); \
} \
\
inline void close_##_NEW( _NEW* fp ) { \
	close_##_TYPE( (_TYPE*)fp ); \
} \
\
inline const size_t size_##_NEW( const char* _FileName ) { \
	return size_##_TYPE( _FileName ); \
} \
\
inline const size_t size_##_NEW( _NEW* fp ) { \
	return size_##_TYPE( (_TYPE*)fp ); \
} \
\
inline const size_t read_##_NEW( _NEW* fp, char* Data, const size_t Size ) { \
	return read_##_TYPE( (_TYPE*)fp, Data, Size ); \
} \
\
inline const size_t write_##_NEW( _NEW* fp, const char* Data, const size_t Size ) { \
	return write_##_TYPE( (_TYPE*)fp, Data, Size ); \
} \
\
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_GEL_Core_File_MakeHandleUtil_H__ //
// - ------------------------------------------------------------------------------------------ - //
