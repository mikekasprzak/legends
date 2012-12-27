// Frag Heap - A type of fragmented memory structure that allocates chunks in a linked list.
//   Memory is then allocated from each chunk (page), and when not enough memory is available,
//   a new chunk (page) is allocated, and noted on the tail end of the linked list.
// The point of this is to efficiently allow you to allocate data, while at the same
//   time not breaking any existing pointers to data inside the memory. Not recommended for
//   large objects (use regular allocation instead). This is designed to provide an optimal
//   allocator for many small objects, such as a linked list.
//   A variation can be provided that's optimized for equalized types, just as there's one
//   optimized for varying sized types (multi-blocks).

// Have a function for indexing in to the heap. Returns a base address pointer. Typical use
//   would be to pass the first (0) index offset to this function, and you get the true base
//   address back from the call. You can then index it normally using the base address.

// Have a Stream type built on top of the heap. Same as above, but knows that a chunk of a
//   certain size will exist inside a space. So, when it needs needs the next chunk, do a 
//   lookup like above (i.e. step through memory to find the address of the next chunk)