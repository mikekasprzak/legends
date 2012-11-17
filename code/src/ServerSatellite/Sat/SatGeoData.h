// - ------------------------------------------------------------------------------------------ - //
#ifndef __SAT_SATGEODATA_H__
#define __SAT_SATGEODATA_H__
// - ------------------------------------------------------------------------------------------ - //
// Functor //
// - ------------------------------------------------------------------------------------------ - //
class SatGeoData {
	friend const SatGeoData LookupGeoData( const struct SatGeoService* Service );
	bool Good;

public:
	char IP[38+1];			// Large enough to hold an IPv6 Address //
	char Country[2+1];		// 2 character country codes //
	float Latitude;
	float Longitude;

public:
	inline SatGeoData() :
		Good( false )
	{ }
	SatGeoData( const char* _IP, const char* _Country, const float _Latitude, const float _Longitude, const bool _Success = false );
	
	void operator()( );
	
	inline const bool IsGood() const {
		return Good;
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __SAT_SATGEODATA_H__ //
// - ------------------------------------------------------------------------------------------ - //
