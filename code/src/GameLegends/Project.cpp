// - ------------------------------------------------------------------------------------------ - //
#include "Project.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#define PRODUCT_NAME	"Alone, The"
#define PRODUCT_VERSION	"0.1"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// OS SUFFIX //
#if defined(USES_WINDOWS)
#define OS_SUFFIX		"(for Windows)"
#elif defined(USES_LINUX)

#ifdef USES_ATOMSTORE
#define OS_SUFFIX		"(for Moblin)"
#else // USES_ATOMSTORE //
#define OS_SUFFIX		"(for Linux)"
#endif // USES_ATOMSTORE //

#else // OS SUFFIX //
#define OS_SUFFIX	""
#endif // OS SUFFIX//
// - ------------------------------------------------------------------------------------------ - //
// STORE SUFFIX //
#if defined(USES_ATOMSTORE)
#define STORE_SUFFIX	" -- Intel Atom SE"
#else // STORE SUFFIX //
#define STORE_SUFFIX	""
#endif // STORE SUFFIX //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_ATOMSTORE
// - ------------------------------------------------------------------------------------------ - //
#include <AtomStore/adpcore.h>
// - ------------------------------------------------------------------------------------------ - //
extern const ADP_APPLICATIONID myApplicationID;

#if defined(USES_WINDOWS)
const ADP_APPLICATIONID myApplicationID = {{
	0xAC201A91,0xFE4F4AFC,0x99BE4683,0x1A554C63 }};
#else defined(USES_LINUX)
const ADP_APPLICATIONID myApplicationID = {{
	0x45BDFB64,0x892240C7,0xB6D2DCDF,0xE2C3361C }};
#endif // USES_WINDOWS/LINUX //
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_ATOMSTORE //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Product Name //
const char ProductName[] = PRODUCT_NAME;
const char FullProductName[] = PRODUCT_NAME " " OS_SUFFIX " " PRODUCT_VERSION STORE_SUFFIX;
// - ------------------------------------------------------------------------------------------ - //
