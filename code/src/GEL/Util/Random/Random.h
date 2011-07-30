// - ------------------------------------------------------------------------------------------ - //
// Caissie Random Number Generation //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Rebel_Random_H__
#define __Rebel_Random_H__
// - ------------------------------------------------------------------------------------------ - //
class cRandom {
public:
	int Data[4];

	inline cRandom() {
		Seed( 0 );
	}
	
	inline cRandom( int _Seed ) {
		Seed( _Seed );
	}
	
public:
	inline void Seed( int Seed ) {
		Data[0] = Seed;
		Data[1] = 0;
		Data[2] = 0;
		Data[3] = 0;
	}
	
	inline int Get() {
		Data[3]++;
		Data[2] += Data[3] ^ Data[0];
		Data[1] += Data[2] ^ (Data[3] >> 8);
		Data[0] += Data[1] ^ (Data[2] >> 8);
	
		return Data[0];
	}
	
	inline int Get( int Size ) {
		return Get() % Size;
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __Rebel_Random_H__ //
// - ------------------------------------------------------------------------------------------ - //
