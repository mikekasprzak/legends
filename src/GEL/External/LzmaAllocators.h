
#ifndef __LZMA_ALLOCATORS_H__
#define __LZMA_ALLOCATORS_H__

#include <External/LZMA/LzmaTypes.h>

void *alloc_LZMA(void *p, SizeT size);
void free_LZMA(void *p, void *address);

// VTable for allocating the memory LZMA needs //
extern ISzAlloc lzma_alloc_struct;

#endif // __LZMA_ALLOCATORS_H__ //
