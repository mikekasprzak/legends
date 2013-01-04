
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
//		{	// First 0 is indexes in to Matrices (0-3), 2nd 0 is which input slot (multiple VBO's). One layout for all //
//			{ "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
//			{ "TEXCOORD", 0, DXGI_FORMAT_R16G16_SINT, 0, D3D11_APPEND_ALIGNED_ELEMENT,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
//			{ "COLOR", 0, DXGI_FORMAT_R8G8B8A8_UNORM, 0, D3D11_APPEND_ALIGNED_ELEMENT,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
//		};	// http://msdn.microsoft.com/en-us/library/windows/desktop/ff476180%28v=vs.85%29.aspx
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


// D3D is only ever this complex, if all data is created. //
//
//	UINT stride = sizeof(cInputVertexPositionTexColor);
//	UINT offset = 0;
//
//	Renderer->m_d3dContext->IASetVertexBuffers( 0, 1, _vertexBuffer.GetAddressOf(), &stride, &offset );
//	Renderer->m_d3dContext->IASetIndexBuffer( _indexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0 );
//
//	Renderer->m_d3dContext->IASetPrimitiveTopology( (D3D11_PRIMITIVE_TOPOLOGY)Mode );
//
//	Renderer->m_d3dContext->DrawIndexed( IndexCount, 0, 0 );
//
// One Vertex Buffer Set per Vertex Buffer. One Index Buffer Set. I suppos the only thing missing is the
//   binding of textures.

// That said...
//
//	Renderer->m_d3dContext->IASetInputLayout( Renderer->TexturedColorsShader_inputLayout.Get() );
//	Renderer->m_d3dContext->VSSetShader( Renderer->TexturedColorsShader_vertexShader.Get(), nullptr, 0 );
//	Renderer->m_d3dContext->VSSetConstantBuffers( 0, 1, Renderer->Common_constantBuffer.GetAddressOf() );
//	Renderer->m_d3dContext->PSSetShader( Renderer->TexturedColorsShader_pixelShader.Get(), nullptr, 0 );
//	Renderer->m_d3dContext->PSSetSamplers( 0, 1, Renderer->TexturedColorsShader_samplerState.GetAddressOf() );
//
// This needs to be set before the Draw call to load the shader.
//
//	Renderer->m_d3dContext->PSSetShaderResources( 0, 1, TextureInfo[ Texture ].D3DTextureView.GetAddressOf() );
//
// And this is how the texture is specified. (glBindTexture)
//
// A texture is (after BS loading) described by both a ID3D11Texture2D* and a ID3D11ShaderResourceView*.
// The Texture3D is the data, and the View is what is used to bind it to a shader.


// Hmm.
// Regrettably, D3D InputLayouts are not exactly the same as Vertex Array Objects. VAO's are actually
//   a more higher lever structure, that combines multiple VBOs and the idea of the Input Layout in
//   to one. Input Layouts, like most other D3D structures, are the complete state data of attributes.
//   Again, part of the information is compiled in to shader in OpenGL, and the rest needs to be
//   specified using glAttribPointer calls. In D3D's case, this data is already made available (Input
//   layout), and you simply need to specify the base address pointer. Thus, the D3D solution may
//   actually be the superior solution, but only if GL blocks. GL may not actually block. In that case
//   the performance loss of GL having to specify each Attrib Pointer plus all its data may be
//   insignificant.
// So on that note, yes InputLayouts should probably be defined in advance (as D3D has no choice).
//   But that said, the OpenGL implentation should always be several calls to glAttribPointer,
//   which also means that a shader program stores attrib data in an indexable fashion (which it
//   already does), and the AttribPointer call should follow the syntax of IASetVertexBuffers.
//   Of note, Stride and Offset are part of IASetVertexBuffers, so the only new data attached to
//   the attribute definition is the size of the individual attribute parts... oh shit, and they
//   have internal stride as well.
// After some digging, it seems yes the Input Layout is: Type, Count (elements) and stride size.
//   The stride part of IASetVertexBuffers should almost always be fixed to the whole vertex size.
//   I suppose it's there since D3D does not check it's internal types to know how much to space
//   out its own data. Okay, good to know. This data can be determined as part of the Attribs.
// Okay! How to implement.
//   Simply add more options to the Attrib part of the JSON file. Then provide a simpler
//   function for glAttribPointer, just the data pointer and slot. In D3D's case, we can
//   calculate the stride size. Also, definitions will need to be looked up in a table-like
//   structure. DXGI_FORMAT_R8G8B8A8_UNORM is 8bit color data. DXGI_FORMAT_R32G32_FLOAT is
//   Vector2D pair. So it's a little wonky yes (not as clean as GL's GL_FLOAT and 2 of 'em).


// After doing some looking, it seems OpenGL ES 3.0 fully supports all these constructs, including
//   GL Instanced Arrays, which is found in OpenGL 3.3. So ya, my claim that GL ES is the "best of"
//   OpenGL is very much true.
