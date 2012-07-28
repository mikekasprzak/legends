// - ------------------------------------------------------------------------------------------ - //
#include "Project.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#define PRODUCT_NAME	"Life Formula"
#define PRODUCT_VERSION	"WIP 1"
//#define PRODUCT_VERSION	"0.1"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// OS SUFFIX //
#if defined(USES_WINDOWS)
#ifdef _MSC_VER
#ifdef USES_DIRECT3D
#ifdef USES_METRO
#define OS_SUFFIX		"(Metro Direct3D)"
#else // USES_METRO //
#define OS_SUFFIX		"(Windows Direct3D MSVC)"
#endif // USES_METRO //
#else // USES_DIRECT3D //
#define OS_SUFFIX		"(Windows OpenGL MSVC)"
#endif // USES_DIRECT3D //
#else // _MSC_VER //
#define OS_SUFFIX		"(Windows OpenGL MinGW)"
#endif // _MSC_VER //
#elif defined(USES_LINUX)
#define OS_SUFFIX		"(Linux OpenGL)"
#else // OS SUFFIX //
#define OS_SUFFIX	""
#endif // OS SUFFIX//
// - ------------------------------------------------------------------------------------------ - //
// STORE SUFFIX //
#if defined(USES_STEAMWORKS)
#define STORE_SUFFIX	" -- Steam"
#else // STORE SUFFIX //
#define STORE_SUFFIX	""
#endif // STORE SUFFIX //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Product Name //
const char ProductName[] = PRODUCT_NAME;
const char FullProductName[] = PRODUCT_NAME " " OS_SUFFIX " " PRODUCT_VERSION STORE_SUFFIX;
// - ------------------------------------------------------------------------------------------ - //
