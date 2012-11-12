// - ------------------------------------------------------------------------------------------ - //
#ifndef __SAT_SATGEODATA_H__
#define __SAT_SATGEODATA_H__
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
class SatGeoData {
public:
	char IP[38+1];			// Large enough to hold an IPv6 Address //
	char Country[2+1];		// 2 character country codes //
	float Latitude;
	float Longitude;
	
	bool Success;

public:
	inline SatGeoData() { }
	SatGeoData( const char* _IP, const char* _Country, const float _Latitude, const float _Longitude, const bool _Success = false );
};
// - ------------------------------------------------------------------------------------------ - //

const SatGeoData GetMyGeoData();

// - ------------------------------------------------------------------------------------------ - //
#endif // __SAT_SATGEODATA_H__ //
// - ------------------------------------------------------------------------------------------ - //
