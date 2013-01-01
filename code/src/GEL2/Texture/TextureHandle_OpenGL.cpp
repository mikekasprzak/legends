// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_OPENGL2) || defined(USES_OPENGLES2)
// - ------------------------------------------------------------------------------------------ - //
#include <API/API_OpenGL2.h>
// - ------------------------------------------------------------------------------------------ - //
#include "TextureHandle_OpenGL.h"
// - ------------------------------------------------------------------------------------------ - //
namespace Texture {
// - ------------------------------------------------------------------------------------------ - //
TextureHandle new_TextureHandle() {
	TextureHandle Handle;
	glGenTextures( 1, &Handle );
	return Handle;
}
// - ------------------------------------------------------------------------------------------ - //
void delete_TextureHandle( TextureHandle Handle ) {
	glDeleteTextures( 1, (const GLuint*)&Handle );
}
// - ------------------------------------------------------------------------------------------ - //
void bind_TextureHandle( TextureHandle Handle, const int Index ) {
	glActiveTexture( GL_TEXTURE0 + Index );
	glBindTexture( GL_TEXTURE_2D, Handle );
}
// - ------------------------------------------------------------------------------------------ - //
// Rarely Used. Alternatively, just bund another texture //
void unbind_TextureHandle( TextureHandle ) {
	glBindTexture( GL_TEXTURE_2D, 0 );
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Texture //
// - ------------------------------------------------------------------------------------------ - //
#endif // defined(USES_OPENGL2) || defined(USES_OPENGLES2) //
// - ------------------------------------------------------------------------------------------ - //
