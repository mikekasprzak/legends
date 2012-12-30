
//	http://www.songho.ca/opengl/gl_vbo.html
//	http://www.khronos.org/opengles/sdk/docs/man/xhtml/glBufferData.xml

// glBufferData( GL_ARRAY_BUFFER, size, data, usage )			// Verts //
// glBufferData( GL_ELEMENT_ARRAY_BUFFER, size, data, usage )	// Indexes //

//	For VBO's, your only choices are:
//	- GL_STATIC_DRAW			// One Update (ever), Multiple Uses
//	- GL_DYNAMIC_DRAW			// Multiple Updates, Multiple Uses
//	- GL_STREAM_DRAW			// One Update, One Use (and repeat)
//	Of course, you can delete a static VBO to work around the one use ever limit

//	The _READ and _COPY options are only available with PBOs and FBOs, and only
//  on the Desktop.

