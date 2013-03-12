// - ------------------------------------------------------------------------------------------ - //
#ifndef __PUCK_SCENEGAME_H__
#define __PUCK_SCENEGAME_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Engine/Engine.h>
// - ------------------------------------------------------------------------------------------ - //
class cSceneGame: public cScene {
public: // - Class Helpers -------------------------------------------------------------------- - //
	typedef cSceneGame thistype;
	inline void* GetThis() { return this; }
public: // - Members -------------------------------------------------------------------------- - //
public: // - Constructors and Destructors ----------------------------------------------------- - //
	//virtual void Create() { // Can't do this in C++. See Project.h. Using Constructor instead. //
	cSceneGame()
	{
		// Add Templates //
		
		// Add Objects //
		
		
		// Whatever //
		Log( "Hey it's me" );
		cUID Scobe;
		cUID Scob;
		Log( "%i", Scob.Get() );
			
		flex MyFlex = true;
		MyFlex += "Scores!";
		MyFlex += 44;
		
		flex Shoe = 144;
		Shoe += 10;
		Shoe += "Sock";
		Shoe += true;
		Shoe += false;
		
		MyFlex += Shoe;

		Log( "YO! %s %s %i %f o_o", MyFlex.ToString(), Shoe.ToString(), MyFlex.ToInt(), MyFlex.ToFloat() );
	}

	//virtual void Destroy() { // See Above //
	virtual ~cSceneGame() {
		
	}	

public: // - Methods -------------------------------------------------------------------------- - //
	
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __PUCK_SCENEGAME_H__ //
// - ------------------------------------------------------------------------------------------ - //
