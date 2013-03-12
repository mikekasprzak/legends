// - ------------------------------------------------------------------------------------------ - //
#include <Style/Style.h>

#include <Search/Search.h>
#include <Render/Render.h>

#include <spine-gel/spine.h>

#include "App.h"
// - ------------------------------------------------------------------------------------------ - //
using namespace Texture;
using namespace Render;
// - ------------------------------------------------------------------------------------------ - //
TextureHandle Texas;
cFont* Font;
cRenderTarget* RT_Main;
cRenderTarget* RT_Blur[2];

cUberShader* PPShader;
cUberShader* BlurShader;

float animationTime = 0;
spine::Atlas* atlas = 0;
spine::SkeletonData* skeletonData = 0;
spine::Animation* animation = 0;
spine::Skeleton* skeleton = 0;
// - ------------------------------------------------------------------------------------------ - //
cApp::cApp() {
	Search::AddDirectory( "Content/" );
	
	Font = new cFont( Search::Search( "C64Pro.fnt" ) );

	// TODO: On some sort of resize event, trigger a delete and recreation of the RenderTargets.		
	int Width = Screen::Native[0].GetWidth();
	int Height = Screen::Native[0].GetHeight();
//	int Width = Screen::Native[0].GetActualWidth();
//	int Height = Screen::Native[0].GetActualHeight();

	RT_Main = new cRenderTarget( Width, Height, 1,0,0 );
	RT_Blur[0] = new cRenderTarget( Width>>2, Height>>2, 1,0,0 );
	RT_Blur[1] = new cRenderTarget( Width>>2, Height>>2, 1,0,0 );
		
	PPShader = new cUberShader( Search::Search("PPEdgeBlend.json") );
	BlurShader = new cUberShader( Search::Search("PostProcess.json") );

	animationTime = 0;
//	try 
	{
		//ifstream atlasFile("../data/spineboy.atlas");
		DataBlock* Data = new_read_DataBlock( Search::Search("spineboy.atlas") );		
		atlas = new spine::Atlas( (const char*)Data->Data, (const char*)(Data->Data+Data->Size) );
		delete_DataBlock( Data );

		spine::SkeletonJson skeletonJson(atlas);

//		ifstream skeletonFile("../data/spineboy-skeleton.json");
		Data = new_read_DataBlock( Search::Search("spineboy-skeleton.json") );		
		skeletonData = skeletonJson.readSkeletonData( (const char*)Data->Data, (const char*)(Data->Data+Data->Size) );
		delete_DataBlock( Data );

//		ifstream animationFile("../data/spineboy-walk.json");
		Data = new_read_DataBlock( Search::Search("spineboy-walk.json") );		
		animation = skeletonJson.readAnimation( (const char*)Data->Data, (const char*)(Data->Data+Data->Size), skeletonData);
		delete_DataBlock( Data );

		skeleton = new spine::Skeleton(skeletonData);
		skeleton->flipX = false;
		skeleton->flipY = true;
		skeleton->setToBindPose();
		skeleton->getRootBone()->x = -350;
		skeleton->getRootBone()->y = -150;
		skeleton->updateWorldTransform();
	}

	Project = new cProject();
}
// - ------------------------------------------------------------------------------------------ - //
cApp::~cApp() {
	delete Project;

	// Cleanup //
	delete BlurShader;
	delete PPShader;
	
	delete RT_Blur[0];
	delete RT_Blur[1];
	delete RT_Main;
	
	delete Font;
	
	delete_TextureHandle( Texas );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#ifdef PRODUCT_CLIENT
// - ------------------------------------------------------------------------------------------ - //
void cApp::Step( ) {
//	World->Client_Step();
	animationTime += 1.0f/120.0f;
	animation->apply(skeleton, animationTime, true);
	skeleton->updateWorldTransform();
}
// - ------------------------------------------------------------------------------------------ - //
void cApp::Draw( Screen::cNative& Native ) {	
	static const float Verts[] = {
		-1,-1,0,
		-1,+1,0,
		+1,-1,0,
		+1,+1,0,
	};

	static const UVType UVs[] = {
		UV_ZERO,UV_ZERO,
		UV_ZERO,UV_ONE,
		UV_ONE,	UV_ZERO,
		UV_ONE,	UV_ONE,
	};

	// ******* //

	RT_Main->Bind();

	// Clear BG with Noise //	
	{
		Default->Bind( NoiseShader );
		Default->UniformMatrix4x4( 0, Matrix4x4::Identity );
		Default->UniformColor( 1, GEL_RGB(96,96,96) ); // GlobalColor //
		static float SeedHack = 0;
		SeedHack += 0.01f;
		if ( SeedHack > 1.0f )
			SeedHack = 0.0f;
		Default->Uniform1f( 3, SeedHack ); // Seed //
		Default->BindUniforms();
		Default->Attrib( 0, Verts );
		Default->Attrib( 1, UVs );
		Default->DrawArrays( GEL_TRIANGLE_STRIP, 4 );		
	}
	
	Matrix4x4 Matrix = Matrix4x4::Identity;
	Matrix(0,0) = 1.0f / (float)Native.GetWidth();//1.0f/(2.0f);
	Matrix(1,1) = 1.0f / (float)Native.GetHeight();//1.0f/(2.0f * Native.GetAspectRatio());
	
	// Draw Something //
	{
		ViewMatrix = Matrix;		

		Matrix4x4 LocalMatrix = Matrix4x4::Identity;
		LocalMatrix(0,0) = 2;//1.0f/1024.0f;//(12*16)*3;
		LocalMatrix(1,1) = 2;//1.0f/1024.0f;//(12*16)*3;
			
		ViewMatrix *= LocalMatrix;
	
//		Default->Bind( TextureShader );
//		Default->UniformMatrix4x4( 0, ViewMatrix );
//		Default->UniformColor( 1, GEL_RGB_WHITE ); // GlobalColor //
//		Default->Uniform1i( 2, 0 );	// TexImage0 //
//		Default->BindUniforms();
//		Texture::Bind( Texas, 0 );
//		Default->Attrib( 0, Verts );
//		Default->Attrib( 1, UVs );
//		Default->DrawArrays( GEL_TRIANGLE_STRIP, 4 );
		
		//Render::EnableAlphaBlending();
		Render::EnablePremultipliedAlphaBlending();
//		World->Client_Draw( Matrix );

		skeleton->draw( ViewMatrix );

		Render::DisableBlending();
	}
	
	RT_Main->UnBind();
	
	// Blur Pass //
	{
		RT_Blur[0]->Bind();
		BlurShader->Bind( 0 );
		BlurShader->UniformMatrix4x4( 0, Matrix4x4::Identity );
		BlurShader->Uniform1i( 2, 0 ); // TexImage0 //
		BlurShader->BindUniforms();
		RT_Main->BindAsTexture();
		BlurShader->Attrib( 0, Verts );
		BlurShader->Attrib( 1, UVs );
		BlurShader->DrawArrays( GEL_TRIANGLE_STRIP, 4 );

		RT_Blur[1]->Bind();
		BlurShader->Bind( 1 );
		BlurShader->UniformMatrix4x4( 0, Matrix4x4::Identity );
		BlurShader->Uniform1i( 2, 0 ); // TexImage0 //
		BlurShader->BindUniforms();
		RT_Blur[0]->BindAsTexture();
		BlurShader->Attrib( 0, Verts );
		BlurShader->Attrib( 1, UVs );
		BlurShader->DrawArrays( GEL_TRIANGLE_STRIP, 4 );

		RT_Blur[1]->UnBind();
	}
	
	// Draw Buffer to Screen //
	{
		Default->Bind( TextureShader );
		Default->UniformMatrix4x4( 0, Matrix4x4::Identity );
		Default->UniformColor( 1, GEL_RGB_WHITE ); // GlobalColor //
		Default->Uniform1i( 2, 0 ); // TexImage0 //
		Default->BindUniforms();
		RT_Main->BindAsTexture();
		Default->Attrib( 0, Verts );
		Default->Attrib( 1, UVs );
		Default->DrawArrays( GEL_TRIANGLE_STRIP, 4 );

//		Render::EnableAlphaBlending();
//		{
//			cUberShader* Sh = PPShader;
//			PPShader->Bind();
//			
////			cUberShader* Sh = Default;
////			Default->Bind( TextureShader );
//	
//			Sh->UniformMatrix4x4( 0, Matrix4x4::Identity );
//			Sh->UniformColor( 1, GEL_RGB_WHITE ); // GlobalColor //
//			Sh->Uniform1i( 2, 0 ); // TexImage0 //
//			Sh->Uniform2f( 3, 1.0f / Native.GetAspectRatio(), 1.0f ); // AspectScalar //
//			Sh->BindUniforms();
//			RT_Blur[1]->BindAsTexture();
//			Sh->Attrib( 0, Verts );
//			Sh->Attrib( 1, UVs );
//			Sh->DrawArrays( GEL_TRIANGLE_STRIP, 4 );
//		}		
//		Render::DisableBlending();
	}
	
	// Draw Text //
	{
		ViewMatrix = Matrix;

		Matrix4x4 LocalMatrix = Matrix4x4::Identity;
		LocalMatrix(0,0) = (4)*2;
		LocalMatrix(1,1) = (4)*2;

		ViewMatrix *= LocalMatrix;

		Render::EnablePremultipliedAlphaBlending();
		Font->printf( Vector3D(-100,-50,0), 8.0f, GEL_ALIGN_DEFAULT, "Hey Dude" );
		Render::DisableBlending();
	}
}
// - ------------------------------------------------------------------------------------------ - //
#endif // PRODUCT_CLIENT //
// - ------------------------------------------------------------------------------------------ - //
