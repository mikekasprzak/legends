// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_SCREEN_NATIVE_SDL_H__
#define __GEL_SCREEN_NATIVE_SDL_H__
// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_SDL2
// - ------------------------------------------------------------------------------------------ - //
#include <API/API_SDL2.h>
#include <API/API_OpenGL2.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Core/GelError.h>
#include <Core/GelArray.h>
#include <Debug/Log.h>
#include <MainClient/Main_Product.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Screen {
// - ------------------------------------------------------------------------------------------ - //
// TODO: Derive from cNativeBase. Base is the only one visible to game code. //
class cNative {
	int Index;					// Stored Index... it's either this or pass it in always //
public:
	SDL_Rect DisplayBounds;		// x,y,w,h of the Actual Display //
	SDL_Rect Bounds;			// x,y,w,h of the Window //
	SDL_Window* pWindow;		// Opaque. No direct access to members. //
	SDL_GLContext GLContext;	// (void*) //

public:
	inline cNative() :
		Index( 0 ),
		pWindow( 0 ),
		GLContext( 0 )
	{
	}

public:
	// Outside Interface. Call these only after creating a Window. //
	inline const int GetWidth() const {
		return Bounds.w;
	}
	inline const int GetHeight() const {
		return Bounds.h;
	}
	inline const int GetX() const {
		return Bounds.x;
	}
	inline const int GetY() const {
		return Bounds.y;
	}
	
	inline const float GetAspectRatio() const {
		return (float)Bounds.h / (float)Bounds.w;
	}
	
	// TODO: Some sort of "IsAvailable" //

public:	
	// Call when you just want the NativeScreen to know it's own bounds //
	inline GelError Init( const int _Index ) {
		Index = _Index;
		
		return_if( GetDisplayBounds() );
		
		return GEL_OK;
	}
	
	// Call when you want to create a Window and Context for this screen //
	inline GelError InitWindow( const int _Index, const bool FullScreen = true ) {
		Index = _Index;
		
		return_if( GetDisplayBounds() );
		
		return_if( NewWindow( FullScreen ) );

		return_if( NewGLContext() );
		
		return GEL_OK;
	}
		
	inline GelError Destroy() {
		return_if( DeleteGLContext() );
		return_if( DeleteWindow() );
		return GEL_OK;
	}
	
	inline const int GetIndex() const {
		return Index;
	}
	
	inline GelError MakeCurrent() { // const?
		return SDL_GL_MakeCurrent( pWindow, GLContext );
	}

	inline GelError Swap() { // const?
		SDL_GL_SwapWindow( pWindow );
		return GEL_OK;
	}
	
	inline GelError UpdateViewport( const bool FullScreen ) const {
		glViewport( 0, 0, Bounds.w, Bounds.h );
		
		return GEL_OK;
	}

	inline bool HasWindow() const {
		return pWindow;
	}
	inline bool HasGLContext() const {
		return GLContext;
	}
	
	// Call me inside Resize and Move events so the Bounds are updated correctly //
	inline GelError UpdateBounds() {
		if ( HasWindow() ) {
			SDL_GetWindowPosition( pWindow, &Bounds.x, &Bounds.y );
			SDL_GetWindowSize( pWindow, &Bounds.w, &Bounds.h );
			
			Log( "* Window %i [%i] Bounds Updated: (%i, %i) (%i, %i)", Index, SDL_GetWindowID(pWindow), Bounds.x, Bounds.y, Bounds.w, Bounds.h );
		}
		return GEL_OK;
	}
		
public:
	inline GelError GetDisplayBounds() {
		return_if( SDL_GetDisplayBounds( Index, &DisplayBounds ) );
		return GEL_OK;
	}
	
	inline GelError NewWindow( const int Width, const int Height, const bool FullScreen ) {
		return_if( DeleteWindow() );

		pWindow = SDL_CreateWindow(
			FullProductName, 						// Window Title //
			SDL_WINDOWPOS_CENTERED_DISPLAY(Index),	// Window Position X //
			SDL_WINDOWPOS_CENTERED_DISPLAY(Index),	// Window Position Y //
			Width, Height,
			SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | (FullScreen ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_RESIZABLE) | ((FullScreen && (Index==0)) ? SDL_WINDOW_INPUT_GRABBED : 0)
			);
		
		// SDL_WINDOW_BORDERLESS, SDL_WINDOW_RESIZABLE
		
		if ( FullScreen ) {
			return_if_Log( pWindow == NULL, "! Error Creating Full Screen Window[%i]: %s", Index, SDL_GetError() );
			Log( "* Full Screen Window %i with ID %i Created", Index, SDL_GetWindowID( pWindow ) );
		}
		else {
			return_if_Log( pWindow == NULL, "! Error Creating Window[%i]: %s", Index, SDL_GetError() );
			Log( "* Window %i with ID %i Created", Index, SDL_GetWindowID( pWindow ) );
		}

		return_if( UpdateBounds() );		
		
		return_if( MakeCurrent() );
		
		return_if( UpdateViewport( FullScreen ) );
		
		return GEL_OK;
	}

	// Creates a Window based on the knowledge of the DisplayBounds //
	inline GelError NewWindow( const bool FullScreen ) {
		float Scalar = 1.0f;
		if ( !FullScreen ) {
			Scalar = 0.8f;
		}

		return NewWindow( 
			(int)((float)DisplayBounds.w * Scalar),
			(int)((float)DisplayBounds.h * Scalar),
			FullScreen 
			);
	}

	inline GelError DeleteWindow() {
		if ( HasWindow() ) {
			Log( "* Window %i with ID %i Destroyed", Index, SDL_GetWindowID( pWindow ) );
			SDL_DestroyWindow( pWindow );
			pWindow = 0;
		}
		return (GelError)pWindow; // Should always be zero //
	}
	
	inline GelError NewGLContext() {
		return_if( DeleteGLContext() );
		
		Assert( pWindow == 0, "Window not created before SDL_GL_CreateContext called" );
		
		GLContext = SDL_GL_CreateContext( pWindow );
		
		return_if_Log( GLContext == NULL, "! Error Creating GLContext %i: %i", Index, GLContext );
		Log( "* GLContext %i Created: %i", Index, GLContext );
		
		return GEL_OK;
	}
	
	inline GelError DeleteGLContext() {
		if ( HasGLContext() ) {
			Log( "* GLContext %i Destroyed: %i", Index, GLContext );
			SDL_GL_DeleteContext( GLContext );
			GLContext = 0;
		}
		return (GelError)GLContext;	// Should always be zero //
	}
};
// - ------------------------------------------------------------------------------------------ - //
extern bool FullScreen;
extern cGelArray<cNative> Native;
// - ------------------------------------------------------------------------------------------ - //
inline void InitNative() {
	FullScreen = false;

	const size_t NumVideoDisplays = SDL_GetNumVideoDisplays();
	Native = new_GelArray<cNative>( NumVideoDisplays );
	
	// Init the Bounds, Window and GL Context for the first display //
	Native[0].InitWindow( 0, FullScreen );

	// Only Init the Bounds for the rest of the displays //
	for ( size_t idx = 1; idx < NumVideoDisplays; idx++ ) {
		Native[idx].Init( idx );
	}
}
// - ------------------------------------------------------------------------------------------ - //
inline void DestroyNative() {
	for ( size_t idx = 0; idx < Native.Size(); idx++ ) {
		Native[idx].Destroy();
	}
}
// - ------------------------------------------------------------------------------------------ - //
inline void SetFocus( const int _Index = 0 ) {
	Assert( !Native[_Index].HasWindow(), "Screen %i has no Window", _Index );
	SDL_RaiseWindow( Native[_Index].pWindow ); // Make [_Index] the focus Window //
}
// - ------------------------------------------------------------------------------------------ - //
inline void ToggleScreens( const bool _FullScreen ) {
	FullScreen = _FullScreen;

	for ( size_t idx = 0; idx < Native.Size(); idx++ ) {
		if ( Native[idx].HasWindow() ) { // Only toggle if there is a Window. Otherwise ignore //
			Native[idx].NewWindow( FullScreen );
		}
	}
	
	SetFocus( 0 );
}
// - ------------------------------------------------------------------------------------------ - //
inline void ToggleScreens() {	
	ToggleScreens( !FullScreen );
}
// - ------------------------------------------------------------------------------------------ - //
inline void AddScreen( const int Index ) {
	Warning( Index < 0, "Invalid Index: %i [%i]", Index, Native.Size() );
	Warning( (size_t)Index >= Native.Size(), "Invalid Index: %i [%i]", Index, Native.Size() );
	
	Native[Index].NewWindow( FullScreen );
	
	if ( !Native[Index].HasGLContext() ) {
		Native[Index].NewGLContext();
	}
}
// - ------------------------------------------------------------------------------------------ - //
inline void RemoveScreen( const int Index ) {
	Warning( Index < 0, "Invalid Index: %i [%i]", Index, Native.Size() );
	Warning( (size_t)Index >= Native.Size(), "Invalid Index: %i [%i]", Index, Native.Size() );
	
	Native[Index].DeleteWindow();
}
// - ------------------------------------------------------------------------------------------ - //
inline void AddScreens() { // Add all screens //
	for ( size_t idx = 1; idx < Native.Size(); idx++ ) {
		AddScreen( idx );
	}

	SetFocus( 0 );
}
// - ------------------------------------------------------------------------------------------ - //
inline void RemoveScreens() { // Remove all screens, except 0 //
	for ( size_t idx = 1; idx < Native.Size(); idx++ ) {
		RemoveScreen( idx );
	}

	SetFocus( 0 );
}
// - ------------------------------------------------------------------------------------------ - //
inline int GetIndexByWindowID( const Uint32 WindowID ) {
	for ( size_t idx = 0; idx < Native.Size(); idx++ ) {
		if ( SDL_GetWindowID( Native[idx].pWindow ) == WindowID ) {
			return idx;
		}
	}
	Log( "! WindowID %i Not Found!", WindowID );
	return -1;
}
// - ------------------------------------------------------------------------------------------ - //
inline GelError Update( const int Index ) {
	return_if( Native[Index].UpdateBounds() );
	return_if( Native[Index].MakeCurrent() );
	return_if( Native[Index].UpdateViewport( FullScreen ) );
	return GEL_OK;
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Screen //
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_SDL2 //
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_SCREEN_NATIVE_SDL_H__ //
// - ------------------------------------------------------------------------------------------ - //
