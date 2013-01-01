// - ------------------------------------------------------------------------------------------ - //
#include <Style/Style.h>

#include <Search/Search.h>
#include <Render/Render.h>

#include "App.h"
#include <Net/Net_Host.h>
// - ------------------------------------------------------------------------------------------ - //
#ifdef PRODUCT_SERVER
#include <Text/Out.h>
#endif // PRODUCT_SERVER //
// - ------------------------------------------------------------------------------------------ - //
#ifdef PRODUCT_CLIENT
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
// - ------------------------------------------------------------------------------------------ - //
#endif // PRODUCT_CLIENT //
// - ------------------------------------------------------------------------------------------ - //
cApp::cApp() {
	Search::AddDirectory( "Content/" );

	MyGeo = new TFunctor<SatGeoData>();	// Start Thread //
	
	Adapters = new_pNetAdapterInfo();
	Adapter = get_primary_pNetAdapterInfo( Adapters );
	
	Log( "%s: %s (%s) -- %s [%s]", Adapter->Name, Adapter->IP, Adapter->MAC, Adapter->NetMask, Adapter->Broadcast );
	
#ifdef PRODUCT_CLIENT
	{
		const char* File = Search::Search( "Tiles" );
		
		DataBlock* Data = new_read_DataBlock( File );
		STBTexture Tex = new_STBTexture( Data->Data, Data->Size );
		delete_DataBlock( Data );
		
		Log( "%s -- %i, %i (%i)", File, Tex.Width, Tex.Height, Tex.Info );
		
		Texas = upload_STBTexture( Tex, false );
		
		delete_STBTexture( Tex );
		
		File = Search::Search( "Tiles_Info" );
		Data = new_read_DataBlock( File );
		Tex = new_STBTexture( Data->Data, Data->Size );
		delete_DataBlock( Data );
		
		Log( "%s -- %i, %i (%i)", File, Tex.Width, Tex.Height, Tex.Info );
		
		// I needed some alpha in the image, otherwise the alpha got discarded.
		cGrid2D<st8> Byter = to_8bit_Grid2D_STBTexture( Tex );
		
		Log( "%i, %i (%x %x -- %x %x)", Byter.Width(), Byter.Height(), (int)Byter(0,0),(int)Byter(12,0),(int)Byter(0,12),(int)Byter(12,12) );
		
		delete_STBTexture( Tex );
	}
	
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
				
	// Init //
//	Client_Start();
//	Client_Connect();
	Net::Host_Init();
	Net::Host_StartClient();
	Net::Host_Connect();
//	Net::Host_SendPing();

	glEnableVertexAttribArray( 0 );
#endif // PRODUCT_CLIENT //

	// Wait for threads to finish //
	MyGeo->join();
}
// - ------------------------------------------------------------------------------------------ - //
cApp::~cApp() {
#ifdef PRODUCT_CLIENT
	// Cleanup //
	delete BlurShader;
	delete PPShader;
	
	delete RT_Blur[0];
	delete RT_Blur[1];
	delete RT_Main;
	
	delete Font;
	
	delete_TextureHandle( Texas );

	Net::Host_StopClient();
#endif // PRODUCT_CLIENT //

	delete_pNetAdapterInfo( Adapters );

	delete( MyGeo );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#ifdef PRODUCT_CLIENT
// - ------------------------------------------------------------------------------------------ - //
void cApp::Step( ) {
	Net::Host_Poll();
}
// - ------------------------------------------------------------------------------------------ - //
void cApp::Draw( Screen::cNative& Native ) {
//	glClearColor( 0.3, 0, 0, 1 );
//	glClear( GL_COLOR_BUFFER_BIT );

	
	static float Verts[] = {
		-1,-1,
		-1,+1,
		+1,-1,
		+1,+1,
	};

	static UVType UVs[] = {
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
		Default->BindUniformColor( "GlobalColor", GEL_RGB(96,96,96) );
		Default->BindUniformMatrix4x4( "ViewMatrix", Matrix4x4::Identity );
		static float SeedHack = 0;
		SeedHack += 0.01f;
		if ( SeedHack > 1.0f )
			SeedHack = 0.0f;
		Default->BindUniform1f( "Seed", SeedHack );
		Default->AttribPointer( 0, 2, GL_FLOAT, false, sizeof(float)*2, Verts );
		Default->AttribPointer( 1, 2, GL_UVType, false, sizeof(UVType)*2, UVs );
		Default->DrawArrays( GL_TRIANGLE_STRIP, 4 );		
	}
	
	Matrix4x4 Matrix = Matrix4x4::Identity;
	Matrix(0,0) = 1.0f / (float)Native.GetWidth();//1.0f/(2.0f);
	Matrix(1,1) = 1.0f / (float)Native.GetHeight();//1.0f/(2.0f * Native.GetAspectRatio());
	
	// Draw Something //
	{
		ViewMatrix = Matrix;		

		Matrix4x4 LocalMatrix = Matrix4x4::Identity;
		LocalMatrix(0,0) = (12*16)*3;
		LocalMatrix(1,1) = (12*16)*3;
			
		ViewMatrix *= LocalMatrix;
	
		Default->Bind( TextureShader );
		Default->BindUniformColor( "GlobalColor", GEL_RGB_WHITE );
		Default->BindUniformMatrix4x4( "ViewMatrix", ViewMatrix );
		Texture::Bind( Texas, 0 );
		Default->BindUniform1i( "TexImage0", 0 );
		Default->AttribPointer( 0, 2, GL_FLOAT, false, sizeof(float)*2, Verts );
		Default->AttribPointer( 1, 2, GL_UVType, false, sizeof(UVType)*2, UVs );
		Default->DrawArrays( GL_TRIANGLE_STRIP, 4 );
	}
	
	RT_Main->UnBind();
	
	// Blur Pass //
	{
		RT_Blur[0]->Bind();
		BlurShader->Bind( 0 );
		//BlurShader->BindUniformColor( "GlobalColor", GEL_RGB_WHITE );
		BlurShader->BindUniformMatrix4x4( "ViewMatrix", Matrix4x4::Identity );
		RT_Main->BindAsTexture();
		BlurShader->BindUniform1i( "TexImage0", 0 );
		BlurShader->AttribPointer( 0, 2, GL_FLOAT, false, sizeof(float)*2, Verts );
		BlurShader->AttribPointer( 1, 2, GL_UVType, false, sizeof(UVType)*2, UVs );
		BlurShader->DrawArrays( GL_TRIANGLE_STRIP, 4 );

		RT_Blur[1]->Bind();
		BlurShader->Bind( 1 );
		//BlurShader->BindUniformColor( "GlobalColor", GEL_RGB_WHITE );
		BlurShader->BindUniformMatrix4x4( "ViewMatrix", Matrix4x4::Identity );
		RT_Blur[0]->BindAsTexture();
		BlurShader->BindUniform1i( "TexImage0", 0 );
		BlurShader->AttribPointer( 0, 2, GL_FLOAT, false, sizeof(float)*2, Verts );
		BlurShader->AttribPointer( 1, 2, GL_UVType, false, sizeof(UVType)*2, UVs );
		BlurShader->DrawArrays( GL_TRIANGLE_STRIP, 4 );

		RT_Blur[1]->UnBind();
	}
	
	// Draw Buffer to Screen //
	{
		Default->Bind( TextureShader );
		Default->BindUniformColor( "GlobalColor", GEL_RGB_WHITE );
		Default->BindUniformMatrix4x4( "ViewMatrix", Matrix4x4::Identity );
		RT_Main->BindAsTexture();
		//RT_Blur[1]->BindAsTexture();
		Default->BindUniform1i( "TexImage0", 0 );
		Default->AttribPointer( 0, 2, GL_FLOAT, false, sizeof(float)*2, Verts );
		Default->AttribPointer( 1, 2, GL_UVType, false, sizeof(UVType)*2, UVs );
		Default->DrawArrays( GL_TRIANGLE_STRIP, 4 );

		Render::EnableAlphaBlending();
		{
			cUberShader* Sh = PPShader;
			PPShader->Bind();
			
//			cUberShader* Sh = Default;
//			Default->Bind( TextureShader );
	
			Sh->BindUniformColor( "GlobalColor", GEL_RGB_WHITE );
			Sh->BindUniformMatrix4x4( "ViewMatrix", Matrix4x4::Identity );
			Sh->BindUniform2f( "AspectScalar", 1.0f / Native.GetAspectRatio(), 1.0f );
			//RT_Main->BindAsTexture();
			RT_Blur[1]->BindAsTexture();
			Sh->BindUniform1i( "TexImage0", 0 );
			Sh->AttribPointer( 0, 2, GL_FLOAT, false, sizeof(float)*2, Verts );
			Sh->AttribPointer( 1, 2, GL_UVType, false, sizeof(UVType)*2, UVs );
			Sh->DrawArrays( GL_TRIANGLE_STRIP, 4 );
		}		
		Render::DisableBlending();
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
#ifdef PRODUCT_SERVER
// - ------------------------------------------------------------------------------------------ - //
int cApp::operator()( ) {
	// Wait for threads to finish //
	MyGeo->join();
			
	// Init //
	WebServer_Start();
	//Server_Start();
	Net::Host_Init();
	Net::Host_StartServer();
	
	
	// Do Stuff //
	int TheChar;
	while ( (TheChar = GetCh()) != 27 ) {
		Net::Host_Poll(50);
		//Server_Poll(50); // Time in MS //
		//Wait(50); // 20 times per second //
	}
		
	// Cleanup //
	//Server_Stop();
	Net::Host_StopServer();
	WebServer_Stop();

	// Finished //
	return 0;
}
// - ------------------------------------------------------------------------------------------ - //
#endif // PRODUCT_SERVER //
// - ------------------------------------------------------------------------------------------ - //
