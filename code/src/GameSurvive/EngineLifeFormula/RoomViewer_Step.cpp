// - ------------------------------------------------------------------------------------------ - //
#include <Geometry/Rect.h>
#include <Input/Input_Mouse.h>

#include "RoomViewer.h"
#include "Room.h"
// - ------------------------------------------------------------------------------------------ - //
namespace LifeFormula {
// - ------------------------------------------------------------------------------------------ - //
void cRoomViewer::Step( const Vector3D& MouseRay ) {
	SelectedTile = -1;

	Rect2D Playfield( 
		-(TileSize * HalfSize), 
		-(TileSize * HalfSize),
		+(TileSize * Real(Size)), 
		+(TileSize * Real(Size))
		);

	// Convert Mouse Cursor Position in to an Index //
	if ( Playfield == MouseRay.ToVector2D() ) {
		int x = (Playfield.MapX( MouseRay.x ) * Real(Size));
		int y = (Playfield.MapY( MouseRay.y ) * Real(Size));
		
		SelectedTile = (y * Size) + x;
	}
	else {
		SelectedTile = -1;
	}
	
	// Do Input //
	if ( SelectedTile != -1 ) {
		if ( Focus ) {
			if ( Mouse.Pressed() ) {
				int MapIndex = ToMapIndex( Room->Map, SelectedTile );
				
				Room->MoveActive( Focus, Focus->PosIndex, MapIndex );
			}
		}
	}
	
	static int Tuff = 0;
	Tuff++;
	if ( (Tuff & 15) == 0 ) {
		Integer Width = Room->Map.Width() - Size;
		Integer Height = Room->Map.Height() - Size;
		
		Uint8 *keystate = SDL_GetKeyboardState(NULL);
		if ( keystate[SDL_SCANCODE_W] ) {
			Pos.y++;
			if ( Pos.y >= Height )
				Pos.y = Height;
		}
		if ( keystate[SDL_SCANCODE_S] ) {
			Pos.y--;
			if ( Pos.y < 0 )
				Pos.y = 0;
		}
		if ( keystate[SDL_SCANCODE_A] ) {
			Pos.x--;
			if ( Pos.x < 0 )
				Pos.x = 0;
		}
		if ( keystate[SDL_SCANCODE_D] ) {
			Pos.x++;
			if ( Pos.x >= Width )
				Pos.x = Width;
		}
		if ( keystate[SDL_SCANCODE_TAB] ) {
			Room->Generate();
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace LifeFormula //
// - ------------------------------------------------------------------------------------------ - //
