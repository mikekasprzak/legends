// - ------------------------------------------------------------------------------------------ - //
#ifndef __DAYLIGHTCLOCK_H__
#define __DAYLIGHTCLOCK_H__
// - ------------------------------------------------------------------------------------------ - //
// Used to convert 
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Real.h>
// - ------------------------------------------------------------------------------------------ - //
class cDaylightClock {
public:
	// http://en.wikipedia.org/wiki/Latitude //
	Real Latitude;	// Horizontal -- North Pole = +1 (+90°), South Pole = -1 (-90°), Equator = 0 //
	// http://en.wikipedia.org/wiki/Longitude //
//	Real Longitude;	// Vertical   -- East = +2 (+180°), West = -2 (-180°), Prime Meridian = 0 //

	// March 20th is SIN(0) -- First Day of Spring -- Vernal Equinox -- Perfect 12 hour day, no matter the Latitude //
	// June 21st/20th is SIN(90) -- First Day of Summer -- Summer Equinox -- Longest day //
	// September 22nd/23rd is SIN(180) -- First Day of Fall -- Autumnal Equinox -- Perfect 12 hour day before winter //
	// December 21st/22nd is SIN(270) -- First Day of Winter -- Winter Equinox -- Shortest day //
	Real Season;	// Sine Angle (0-1) //
public:
	cDaylightClock() :
		Latitude( 0 )
	{
	}
	
public:
	// Daylight Hours explorer uses a "Sine Like" graph that increases in amplitude as you get //
	// further and further from the equator. Using Sine isn't correct, but it's close. //
	
	// Arctic Circle       -- 66° 33' 39" N -- Latitudes above this have days of 24 hour day/night //
	// Tropic of Cancer    -- 23° 26' 21" N -- Mexico... uh. Northern Tropic. //
	// Equator             --  0°  0'  0"   -- Constant 12 hour day/night cycles //
	// Tropic of Capricorn -- 23° 26' 21" S -- Australia... uh. Southern Tropic. Also at the Ecliptic //
	// Antarctic Circle    -- 66° 33' 39" S -- Latitudes above this have days of 24 hour day/night //
	
	
	// TODO: Do a MIX on the Sin and SinSaw, so to make the two blend between Sine-like and rigid.
	// TODO: Add an Angle conversion function to Real, so to correctly convert the Arctic Circle.
	//   The Arctic Circle is the amplitude of the waveform //
	Real GetDaylight() {
		Real Light = Real(12);// + ( 12 * ( Season.Sin() ) );
		
		if ( Light > Real(24) )
			return Real(24);
		else if ( Light < Real::Zero )
			return Real::Zero;
		return Light;
	}
	
	// http://social.msdn.microsoft.com/Forums/eu/vemapcontroldev/thread/15c1c2e5-280c-4978-b2b0-6d253a58c78c //
	// P = asin[.39795*cos(.2163108 + 2*atan{.9671396*tan[.00860(J-186)]})];
	// LengthOfDay = 24 - (24/pi)*acos((sin(0.8333*pi/180) + sin(L*pi/180)*sin(P)) /  (cos(L*pi/180)*cos(P)));
	// Where L = latitude, and J = day of the year.
	
	// Sunlight Exposure Formula is here: http://en.wikipedia.org/wiki/Sunlight //
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __DAYLIGHTCLOCK_H__ //
// - ------------------------------------------------------------------------------------------ - //
