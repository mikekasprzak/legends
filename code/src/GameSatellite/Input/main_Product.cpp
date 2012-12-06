// - ------------------------------------------------------------------------------------------ - //
#include "main_Product.h"
// - ------------------------------------------------------------------------------------------ - //
#ifdef PRODUCT_NAME
	const char* const ProductName = PRODUCT_NAME;
#else // PRODUCT_NAME //
	const char* const ProductName = "Unknown";
#endif // PRODUCT_NAME //
// - ------------------------------------------------------------------------------------------ - //
#ifdef FULL_PRODUCT_NAME
	const char* const FullProductName = FULL_PRODUCT_NAME;
#elif defined( PRODUCT_NAME )
	const char* const FullProductName = PRODUCT_NAME;
#else // PRODUCT_NAME //
	const char* const FullProductName = "Unknown (?) v0.0";
#endif // PRODUCT_SKU //
// - ------------------------------------------------------------------------------------------ - //
