// TBH, I don't know what to do with this //

// In OpenGL 3.1 (OpenGL ES 3), you can define a set of uniforms for a shader in advance,
//   and then make a single call to switch them all in or out.
// http://www.opengl.org/wiki/Uniform_Buffer_Object

// This equivalent to Constant Buffers in Direct3D 10+. (Target/D3d11/GelRenderer.cpp)
// In D3D11's case, there is no option *NOT* to use Constant Buffers.

// So, it may eventually be ideal to implement and simulate Uniform Buffer Objects.


// Also of note, though GL uses a Uniform for setting its sampler, D3D uses a seperate
//   type to define its samplers. Also of note, that seperate type is what's used to
//   define all texture reading settings, from texture wrapping to filtering mode.
// So again, I may have to do some experiments to determine if I can change sampling
//   settings from loaded textures. This did not work with GL ES 1.0->2.0 hardware,
//   so I have been avoiding it ever since. Perhaps it has changed. I dunno. *shrug*
