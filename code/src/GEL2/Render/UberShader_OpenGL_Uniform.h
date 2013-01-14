// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL2_SHADER_UBERSHADER_OPENGL_UNIFORM_H__
#define __GEL2_SHADER_UBERSHADER_OPENGL_UNIFORM_H__
// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_OPENGL2) || defined(USES_OPENGLES2)
// - ------------------------------------------------------------------------------------------ - //
namespace Render {
// - ------------------------------------------------------------------------------------------ - //
void cUberShader::Uniform1i( const st32 Index, const int v0 ) {
	int* Target = (int*)&CurrentShader->UniformData->Data[ CurrentShader->Uniform[Index].Offset ];
	Target[0] = v0;
}
// - ------------------------------------------------------------------------------------------ - //
void cUberShader::Uniform2i( const st32 Index, const int v0, const int v1 ) {
	int* Target = (int*)&CurrentShader->UniformData->Data[ CurrentShader->Uniform[Index].Offset ];
	Target[0] = v0;
	Target[1] = v1;
}
// - ------------------------------------------------------------------------------------------ - //
void cUberShader::Uniform3i( const st32 Index, const int v0, const int v1, const int v2 ) {
	int* Target = (int*)&CurrentShader->UniformData->Data[ CurrentShader->Uniform[Index].Offset ];
	Target[0] = v0;
	Target[1] = v1;
	Target[2] = v2;
}
// - ------------------------------------------------------------------------------------------ - //
void cUberShader::Uniform4i( const st32 Index, const int v0, const int v1, const int v2, const int v3 ) {
	int* Target = (int*)&CurrentShader->UniformData->Data[ CurrentShader->Uniform[Index].Offset ];
	Target[0] = v0;
	Target[1] = v1;
	Target[2] = v2;
	Target[3] = v3;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cUberShader::Uniform1f( const st32 Index, const float v0 ) {
	float* Target = (float*)&CurrentShader->UniformData->Data[ CurrentShader->Uniform[Index].Offset ];
	Target[0] = v0;
}
// - ------------------------------------------------------------------------------------------ - //
void cUberShader::Uniform2f( const st32 Index, const float v0, const float v1 ) {
	float* Target = (float*)&CurrentShader->UniformData->Data[ CurrentShader->Uniform[Index].Offset ];
	Target[0] = v0;
	Target[1] = v1;
}
// - ------------------------------------------------------------------------------------------ - //
void cUberShader::Uniform3f( const st32 Index, const float v0, const float v1, const float v2 ) {
	float* Target = (float*)&CurrentShader->UniformData->Data[ CurrentShader->Uniform[Index].Offset ];
	Target[0] = v0;
	Target[1] = v1;
	Target[2] = v2;
}
// - ------------------------------------------------------------------------------------------ - //
void cUberShader::Uniform4f( const st32 Index, const float v0, const float v1, const float v2, const float v3 ) {
	float* Target = (float*)&CurrentShader->UniformData->Data[ CurrentShader->Uniform[Index].Offset ];
	Target[0] = v0;
	Target[1] = v1;
	Target[2] = v2;
	Target[3] = v3;
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
void cUberShader::Uniform1iv( const st32 Index, const int* v, const st32 Count ) {
	int* Target = (int*)&CurrentShader->UniformData->Data[ CurrentShader->Uniform[Index].Offset ];
	copy_Data( v, Target, sizeof(int)*1*Count );
}
// - ------------------------------------------------------------------------------------------ - //
void cUberShader::Uniform2iv( const st32 Index, const int* v, const st32 Count ) {
	int* Target = (int*)&CurrentShader->UniformData->Data[ CurrentShader->Uniform[Index].Offset ];
	copy_Data( v, Target, sizeof(int)*2*Count );
}
// - ------------------------------------------------------------------------------------------ - //
void cUberShader::Uniform3iv( const st32 Index, const int* v, const st32 Count ) {
	int* Target = (int*)&CurrentShader->UniformData->Data[ CurrentShader->Uniform[Index].Offset ];
	copy_Data( v, Target, sizeof(int)*3*Count );
}
// - ------------------------------------------------------------------------------------------ - //
void cUberShader::Uniform4iv( const st32 Index, const int* v, const st32 Count ) {
	int* Target = (int*)&CurrentShader->UniformData->Data[ CurrentShader->Uniform[Index].Offset ];
	copy_Data( v, Target, sizeof(int)*4*Count );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cUberShader::Uniform1fv( const st32 Index, const float* v, const st32 Count ) {
	float* Target = (float*)&CurrentShader->UniformData->Data[ CurrentShader->Uniform[Index].Offset ];
	copy_Data( v, Target, sizeof(float)*1*Count );
}
// - ------------------------------------------------------------------------------------------ - //
void cUberShader::Uniform2fv( const st32 Index, const float* v, const st32 Count ) {
	float* Target = (float*)&CurrentShader->UniformData->Data[ CurrentShader->Uniform[Index].Offset ];
	copy_Data( v, Target, sizeof(float)*2*Count );
}
// - ------------------------------------------------------------------------------------------ - //
void cUberShader::Uniform3fv( const st32 Index, const float* v, const st32 Count ) {
	float* Target = (float*)&CurrentShader->UniformData->Data[ CurrentShader->Uniform[Index].Offset ];
	copy_Data( v, Target, sizeof(float)*3*Count );
}
// - ------------------------------------------------------------------------------------------ - //
void cUberShader::Uniform4fv( const st32 Index, const float* v, const st32 Count ) {
	float* Target = (float*)&CurrentShader->UniformData->Data[ CurrentShader->Uniform[Index].Offset ];
	copy_Data( v, Target, sizeof(float)*4*Count );
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
void cUberShader::UniformMatrix2x2( const st32 Index, const Matrix2x2& v ) {
	Matrix2x2* Target = (Matrix2x2*)&CurrentShader->UniformData->Data[ CurrentShader->Uniform[Index].Offset ];
	copy_Data( &v, Target, sizeof(Matrix2x2) );
}
// - ------------------------------------------------------------------------------------------ - //
void cUberShader::UniformMatrix3x3( const st32 Index, const Matrix3x3& v ) {
	Matrix3x3* Target = (Matrix3x3*)&CurrentShader->UniformData->Data[ CurrentShader->Uniform[Index].Offset ];
	copy_Data( &v, Target, sizeof(Matrix3x3) );
}
// - ------------------------------------------------------------------------------------------ - //
void cUberShader::UniformMatrix4x4( const st32 Index, const Matrix4x4& v ) {
	Matrix4x4* Target = (Matrix4x4*)&CurrentShader->UniformData->Data[ CurrentShader->Uniform[Index].Offset ];
	copy_Data( &v, Target, sizeof(Matrix4x4) );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cUberShader::UniformMatrix2fv( const st32 Index, const float* v, const size_t Count  ) {
	float* Target = (float*)&CurrentShader->UniformData->Data[ CurrentShader->Uniform[Index].Offset ];
	copy_Data( v, Target, sizeof(float)*2*2*Count );
}
// - ------------------------------------------------------------------------------------------ - //
void cUberShader::UniformMatrix3fv( const st32 Index, const float* v, const size_t Count  ) {
	float* Target = (float*)&CurrentShader->UniformData->Data[ CurrentShader->Uniform[Index].Offset ];
	copy_Data( v, Target, sizeof(float)*3*3*Count );
}
// - ------------------------------------------------------------------------------------------ - //
void cUberShader::UniformMatrix4fv( const st32 Index, const float* v, const size_t Count  ) {
	float* Target = (float*)&CurrentShader->UniformData->Data[ CurrentShader->Uniform[Index].Offset ];
	copy_Data( v, Target, sizeof(float)*4*4*Count );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cUberShader::UniformColor( const st32 Index, const GelColor Color ) {
	float* Target = (float*)&CurrentShader->UniformData->Data[ CurrentShader->Uniform[Index].Offset ];
//	Log( "%i -- 0x%x", Index, Target );
	Target[0] = ((float)GEL_GET_R(Color))*(1.0f/255.0f);
	Target[1] = ((float)GEL_GET_G(Color))*(1.0f/255.0f);
	Target[2] = ((float)GEL_GET_B(Color))*(1.0f/255.0f);
	Target[3] = ((float)GEL_GET_A(Color))*(1.0f/255.0f);
}
// - ------------------------------------------------------------------------------------------ - //
void cUberShader::UniformSColor( const st32 Index, const GelSColor Color ) {
	float* Target = (float*)&CurrentShader->UniformData->Data[ CurrentShader->Uniform[Index].Offset ];
	Target[0] = ((float)GEL_SGET_R(Color))*(1.0f/255.0f);
	Target[1] = ((float)GEL_SGET_G(Color))*(1.0f/255.0f);
	Target[2] = ((float)GEL_SGET_B(Color))*(1.0f/255.0f);
	Target[3] = ((float)GEL_SGET_A(Color))*(1.0f/255.0f);
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Render //
// - ------------------------------------------------------------------------------------------ - //
#endif // defined(USES_OPENGL2) || defined(USES_OPENGLES2) //
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL2_SHADER_UBERSHADER_OPENGL_UNIFORM_H__ //
// - ------------------------------------------------------------------------------------------ - //
