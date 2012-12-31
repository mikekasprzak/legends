// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL2_RENDER_VERTEXHANDLE_OPENGL_H__
#define __GEL2_RENDER_VERTEXHANDLE_OPENGL_H__
// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_OPENGL2) || defined(USES_OPENGLES2)
// - ------------------------------------------------------------------------------------------ - //
namespace Render {
// - ------------------------------------------------------------------------------------------ - //
typedef unsigned int		VertexHandle;
// - ------------------------------------------------------------------------------------------ - //
VertexHandle new_VertexHandle();
void delete_VertexHandle( VertexHandle Handle );

void bind_VertexHandle( VertexHandle Handle );
void unbind_VertexHandle( VertexHandle = 0 );	// TODO: Remove this argument, once unbind confirmed
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Render //
// - ------------------------------------------------------------------------------------------ - //
#endif // defined(USES_OPENGL2) || defined(USES_OPENGLES2) //
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL2_RENDER_VERTEXHANDLE_OPENGL_H__ //
// - ------------------------------------------------------------------------------------------ - //
