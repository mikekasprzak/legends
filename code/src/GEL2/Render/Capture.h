
// http://www.opengl.org/wiki/Pixel_Transfer

// glReadPixels is still the main way. Reads framebuffers.
// glGetTexImage is a function (desktop only) that can read textures.

// Hope that AMD/ATI drivers have been updated, I guess.
// May need to use glGetTexImage with RenderTarget's.

// The other other option is to use glMapBuffers to get the pointer, but that
//   is WRITE_ONLY on mobile. //

// Pixel Buffer Objects can be used on Desktop for faster (async) reading of data.
// http://www.songho.ca/opengl/gl_pbo.html
// PBO's use glReadPixels to read, but the target is VRAM not RAM. Non blocking.
