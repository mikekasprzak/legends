// - ------------------------------------------------------------------------------------------ - //
#include "LzmaAllocators.h"
// - ------------------------------------------------------------------------------------------ - //
#include <Core/DataBlock_Core.h>

void *alloc_LZMA(void*, SizeT size) { 
	return reinterpret_cast<void*>(new_DataBlock(size)->Data);
}
void free_LZMA(void*, void *address) { 
	if ( address ) {
		delete_DataBlock( (DataBlock*)((char*)(address) - sizeof(DataBlock)) );
	}
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// VTable for allocating the memory LZMA needs //
ISzAlloc lzma_alloc_struct = { alloc_LZMA, free_LZMA };
// - ------------------------------------------------------------------------------------------ - //
