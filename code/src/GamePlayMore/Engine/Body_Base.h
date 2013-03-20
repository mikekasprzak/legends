// - ------------------------------------------------------------------------------------------ - //
#ifndef __PLAYMORE_BODY_BASE_H__
#define __PLAYMORE_BODY_BASE_H__
// - ------------------------------------------------------------------------------------------ - //
class cBody_Base {
public: // - Members -------------------------------------------------------------------------- - //
public: // - Constructors and Destructors ----------------------------------------------------- - //
	inline cBody_Base() {
	}

	virtual ~cBody_Base() {
	}

public: // - Methods -------------------------------------------------------------------------- - //
	virtual void Step() { }
//	virtual const Real& GetFriction() const {
//		static const Real DefaultFriction( 1.0f );
//		return DefaultFriction;
//	}
//	inline static const Real& GetAirFriction() {
//		static const Real DefaultAirFriction( 0.00f );
//		return DefaultAirFriction;
//	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __PLAYMORE_BODY_BASE_H__ //
// - ------------------------------------------------------------------------------------------ - //
