// - ------------------------------------------------------------------------------------------ - //
#ifndef __WORLD_H__
#define __WORLD_H__
// - ------------------------------------------------------------------------------------------ - //
#include "DaylightClock.h"

#include "WorldTile.h"
#include "WorldObject.h"
#include "WorldPlayer.h"
#include "WorldAnimal.h"

#include <Grid/Grid2D_Class.h>

#include <Graphics/GraphicsDraw.h>
// - ------------------------------------------------------------------------------------------ - //
class cWorld {
public:
	
	
	// Global Information About The World (which is actually just a place in the world) //
	// - State of Sunlight (More in summer, less in winter)
	// - State of Moon (full/near full moon provides extra twilight)
	// - Forecast
	//   - Cloudy
	//   - Rainy
	//   - Snowy
	//   - Clear
	// - Temperature
	// - Humidity
	// - Elevation in regards to vegetation 
	
	// True Noon Fluxuates between 12:00 PM and 1:00 PM, though closer to 12:30 PM //
	// The hours of the day are equally spread +/- noon //
	// Around here (Latitude 42) Summer days are ~15 hours, Winter days ~9 hours (+/- 3) //
	
	// Day - Sunrise to Sunset //
	// Twilight - Dawn to Sunrise, Sunset to Dusk. Atmospheric light scatterings //
	// Nautical Twilight - At sea level //
	// Civil Twilight - At typical elevation level //
	
	
	// September (~12 hour days) //
	// Nautical Twilight ~64 minutes //
	// Civil Twilight ~29 minutes //

	// July (~15 hour days) //
	// Nautical Twilight ~80 minutes //
	// Civil Twilight ~35 minutes //
	
	// December (~9 hour days) //
	// Nautical Twilight ~67 minutes //
	// Civil Twilight ~32 minutes //
	
	// Yes, the above data suggests that Summer is longer, but other data is weird //
	
	// -- The World -- //
	enum {
		// A day has equal parts Daylight and Night (summer/winter hours handled elsewhere) //
		DayPeriod 		= 8,		// Size of the ChronoType Tables //
		HalfDayPeriod	= 4,		// Half of the table //
		
		// TODO: This should probably be less. Simulation at 10 to 15 FPS. //
		DayLength 		= 60*60*4,	// Frames*Seconds*Minutes //
	};

	// -- Time/Day/Night Cycle -- //
	int Time;
	
	inline int GetTimeOfDay() {
		return Time % DayLength;
	}
	
	inline int GetDay() {
		return Time / DayLength;
	}
	
	// Daylight //
	// http://astro.unl.edu/classaction/animations/coordsmotion/daylighthoursexplorer.html
	
	// Geology //
	// http://visual.merriam-webster.com/earth/geology.php

public:
	// -- The Map -- //
	cGrid2D<cWorldTile> Map;
	
	// Camera //
	int RoomX, RoomY;
	int RoomSize; // Not seperate RoomWidth and RoomHeight, as all rooms will be square //

public:
	cWorld( const int Width, const int Height ) :
		Map( Width, Height, cWorldTile() ),
		RoomX( 0 ), RoomY( 0 ),
		RoomSize( 7 )
	{	
	}
	
public:
	// Draw what the camera sees //
	void DrawRoom( /* const Vector3D Pos */ ) {
		Real TileSize(8); // Should equal RegionSize / RoomSize
		Real TileHalfSize = TileSize * Real::Half;
			
		Real RoomHalfSize = Real(RoomSize) * Real::Half;
		
		gelSetColor( GEL_RGB_YELLOW );
		
		for ( size_t y = 0; y < RoomSize; y++ ) {
			for ( size_t x = 0; x < RoomSize; x++ ) {
				gelDrawSquare( 
					Vector3D( 
						((Real(x) - RoomHalfSize) * TileSize) + TileHalfSize, 
						((Real(y) - RoomHalfSize) * TileSize) + TileHalfSize, 
						(Real(x) / Real(1)) * Real(y)
						), 
					TileHalfSize 
					);
			}
		}
	}
	
	// - ------ - //
	
	// Draw the entire map as a top-down 2D view //
	void DrawMap2D( const Vector3D Pos ) {
		
	}

	// Draw the entire map as a top-down angled 3D view //
	void DrawMap3D( const Vector3D Pos ) {
		
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __WORLD_H__ //
// - ------------------------------------------------------------------------------------------ - //
