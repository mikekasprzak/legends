
//	http://www.songho.ca/opengl/gl_vbo.html
//	http://www.khronos.org/opengles/sdk/docs/man/xhtml/glBufferData.xml

// glBufferData( GL_ARRAY_BUFFER, size, data, usage )			// Verts //
// glBufferData( GL_ELEMENT_ARRAY_BUFFER, size, data, usage )	// Indexes //

// For VBO's, your only choices are:
//	- GL_STATIC_DRAW			// One Update (ever), Multiple Uses
//	- GL_DYNAMIC_DRAW			// Multiple Updates, Multiple Uses
//	- GL_STREAM_DRAW			// One Update, One Use (and repeat)
//	Of course, you can delete a static VBO to work around the one use ever limit

// The _READ and _COPY options are only available with PBOs and FBOs, and only
//  on the Desktop. :(

// glMapBuffer and glUnmapBuffer are only available on Desktop GL. They are used
//  to get a pointer to memory that can accessed containing the original data.
//  You are not guarenteed to get the same data from subsiquenc Map/Unmap calls.

// ***** //

// D3D11_USAGE -- http://msdn.microsoft.com/en-us/library/windows/desktop/ff476259%28v=vs.85%29.aspx
//	- D3D11_USAGE_DEFAULT 		// GPU-Read, GPU-Write (Copy to VRAM with UpdateSubresource)
//	- D3D11_USAGE_DYNAMIC		// GPU-Read, CPU-Write (prefer Map and Unmap methods to UpdateSubresource)
//	- D3D11_USAGE_IMMUTABLE		// GPU-Read (can populate only on creation. I.e. STATIC)
//	- D3D11_USAGE_STAGING		// All (bulk copies preferred. CopyResource, CopySubresourceRegion)

// Yes, it does look like you can use multiple VBO's in D3D. They call them Input Slots.
// The Arguments to "IASetVertexBuffers" are arrays in linear order.
// http://msdn.microsoft.com/en-us/library/windows/desktop/bb205117%28v=vs.85%29.aspx
//
//g_pVertexBuffers[0] = VBO1;
//g_pVertexBuffers[1] = VBO2;
//g_pVertexBuffers[2] = VBO3;
//UINT strides[3];
//strides[0] = sizeof(SimpleVertex1);
//strides[1] = sizeof(SimpleVertex2);
//strides[2] = sizeof(SimpleVertex3);
//UINT offsets[3] = { 0, 0, 0 };
//g_pd3dDevice->IASetVertexBuffers( 
//    0,                 //first input slot for binding
//    3,                 //number of buffers in the array
//    &g_pVertexBuffers, //array of three vertex buffers
//    &strides,          //array of stride values, one for each buffer
//    &offsets );        //array of offset values, one for each buffer

// ***** //

// Equivalents
// 1. GL_STATIC_DRAW and D3D11_USAGE_IMMUTABLE
// 2. GL_DYNAMIC_DRAW and D3D11_USAGE_DEFAULT (w/o GPU writing)
// 3. GL_STREAM_DRAW and D3D11_USAGE_DEFAULT (faked)
// 4. GL_DYNAMIC_DRAW (with glMapBuffer) and D3D11_USAGE_DYNAMIC (with Map/Unmap)
// 
// Number 3 is a GL only feature, that *may* improve speed in exotic cases.
// Number 4 is only available in GL on the desktop.
// D3D11_USAGE_STAGING is complicated and its benefits are exotic
