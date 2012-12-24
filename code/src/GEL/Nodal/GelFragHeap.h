// Frag Heap - A type of fragmented memory structure that allocates chunks in a linked list.
//   Memory is then allocated from each chunk (page), and when not enough memory is available,
//   a new chunk (page) is allocated, and noted on the tail end of the linked list.
// The point of this is to efficiently allow you to allocate data, while at the same
//   time not breaking any existing pointers to data inside the memory. Not recommended for
//   large objects (use regular allocation instead). This is designed to provide an optimal
//   allocator for many small objects, such as a linked list.
//   A variation can be provided that's optimized for equalized types, just as there's one
//   optimized for varying sized types (multi-blocks).
