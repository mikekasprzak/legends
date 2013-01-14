// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL2_TEXTURE_TEXTUREHANDLE_OPENGL_H__
#define __GEL2_TEXTURE_TEXTUREHANDLE_OPENGL_H__
// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_OPENGL2) || defined(USES_OPENGLES2)
// - ------------------------------------------------------------------------------------------ - //
#include <Style/Style.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Texture {
// - ------------------------------------------------------------------------------------------ - //
typedef unsigned int		TextureHandle;
// - ------------------------------------------------------------------------------------------ - //
TextureHandle new_TextureHandle();
void delete_TextureHandle( TextureHandle Handle );

void bind_TextureHandle( TextureHandle Handle, const st32 TextureUnit = 0 );
void unbind_TextureHandle( TextureHandle = 0, const st32 TextureUnit = 0 );
// - ------------------------------------------------------------------------------------------ - //
inline void Bind( TextureHandle Handle, const int Index = 0 ) {
	bind_TextureHandle( Handle, Index );
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Texture //
// - ------------------------------------------------------------------------------------------ - //
#endif // defined(USES_OPENGL2) || defined(USES_OPENGLES2) //
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL2_TEXTURE_TEXTUREHANDLE_OPENGL_H__ //
// - ------------------------------------------------------------------------------------------ - //
