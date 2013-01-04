
// Yet another "searching for commonality" between D3D and GL.

// This time I'm using the D3D name. Input Layouts in D3D11 let you describe the parts of vertex
//   data all in one shot. Again, this makes switching shaders easier. Less calls.

// The OpenGL version is called Vertex Array Objects, not to be confused with VBO's.
// http://www.opengl.org/wiki/Vertex_Array_Object#Vertex_Array_Object

// http://ogldev.atspace.co.uk/www/tutorial32/tutorial32.html
//    glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[POS_VB]);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(Positions[0]) * Positions.size(), &Positions[0], GL_STATIC_DRAW);
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); // Data (last) is zero because of the Buffer Object //
// Doing all that inside a "glBindVertexArray" block creates the entry in the VAO. It may just be
//   the last 2 lines though (AttribArray AttribPointer). This functionality is similar to how data
//   is asigned in D3D.
//		const D3D11_INPUT_ELEMENT_DESC vertexDesc[] = 
//		{
//			{ "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
//		};
// OpenGL breaks this up in to 2 parts. The names and slot numbers are defined during compile. //
//		glBindAttribLocation( Program, 0, "POSITION" );
// Then the types and data pointers are specified upon use //
//		glAttribPointer( 0, 2, GL_FLOAT, false, sizeof(float)*2, Verts );
//		glAttribPointer( 1, 2, GL_UVType, false, sizeof(UVType)*2, UVs );
// In the first example, it may imply that VAO actually attaches specific VBO's to the VAO.
// Therefor, if you are to change the contents of a VBO object, the VAO will safely update.
// Huh. That's cool. Okay. TBD then is whether this behavior is consistent with D3D11.

// NOTE: This might be something I can handle inside the JSON file.
// EDIT: Maybe not, because VAO's use VBO's, which may not exist yet by JSON time.


// After doing some looking, it seems OpenGL ES 3.0 fully supports all these constructs, including
//   GL Instanced Arrays, which is found in OpenGL 3.3. So ya, my claim that GL ES is the "best of"
//   OpenGL is very much true.
