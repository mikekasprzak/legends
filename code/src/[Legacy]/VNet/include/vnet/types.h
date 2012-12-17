#ifndef __VNET_TYPES_H__
#define __VNET_TYPES_H__

typedef unsigned char vnet_uint8;		// unsigned 8-bit type //
typedef unsigned short vnet_uint16;		// unsigned 16-bit type //
typedef unsigned int vnet_uint32;		// unsigned 32-bit type //

typedef signed char vnet_int8;			// signed 8-bit type //
typedef signed short vnet_int16;		// signed 16-bit type //
typedef signed int vnet_int32;			// signed 32-bit type //

// This shouldn't go here (per platform), but I'm not dealing with DLLs //
#define VNET_API

#endif // __VNET_TYPES_H__ //

