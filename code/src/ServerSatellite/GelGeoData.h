// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_GELGEODATA_H__
#define __GEL_GELGEODATA_H__
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
class GELGeoData {
public:
	char IP[38+1];			// Large enough to hold an IPv6 Address //
	char Country[2+1];		// 2 character country codes //
	float Latitude;
	float Longitude;
	
	bool Success;

public:
	inline GELGeoData() { }
	GELGeoData( const char* _IP, const char* _Country, const float _Latitude, const float _Longitude, const bool _Success = false );
};
// - ------------------------------------------------------------------------------------------ - //

const GELGeoData GetMyGeoData();

// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_GELGEODATA_H__ //
// - ------------------------------------------------------------------------------------------ - //
