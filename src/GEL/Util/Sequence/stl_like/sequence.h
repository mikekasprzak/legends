// - ------------------------------------------------------------------------------------------ - //
// - Sequence.h - v1.0 - By Michael Kasprzak (Sykhronics Entertainment) ----------------------- - //
// --- http://www.sykhronics.com ----------- http://www.toonormal.com ------------------------- - //
// - ------------------------------------------------------------------------------------------ - //
// Copyright Notice:
//   This code is and remains the property of Michael Kasprzak.
//   This code is made available freely for Commercial and Non Commercial use, under the
//     single requirement that this complete copyright notice be left unchanged in any
//     and all derivatives of this file.
//   You're free to adjust the code below to suit any internal or personal coding styles.
//   No warranty is provided for this code.  Use at own risk.
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Rebel_Sequence_H__
#define __Rebel_Sequence_H__
// - ------------------------------------------------------------------------------------------ - //
class sequence {
	// The Value Tested and used over time //
	int Value;
	
	// The Accumulator for local sequence generation //
	int Accumulator;
	// The Last Accumulator value, for correct Get and Set returns //
	int LastAccumulator;
	
	// The number of times looped //
	int LoopCount;

public:
	// Constructor //
	inline sequence( const int StartValue = 0 ) :
		Value( StartValue ),
		Accumulator( 0 ),
		LastAccumulator( 0 ),
		LoopCount( 0 )
	{
	}

public:
	// Activate a Sequence //
	inline void activate() {
		// Only activate if you weren't active before //
		if ( Value == 0 )
			Value = 1;
	}

	// Forcefully Activate a Sequence //
	inline void force_activate() {
		Value = 1;
	}
	
	// Reset, or prematurely end a sequence (also clears the loop count) //
	inline void reset() {
		Value = 0;
		LoopCount = 0;
	}
	
	// If a sequence is currently active //
	inline const bool is_active() const {
		return Value != 0;
	}

public:
	// Start a Sequence (1 of these) //
	inline const bool begin( const int TestValue = 1 ) {
		if ( IsActive() ) {
			Accumulator = TestValue + 1;
			LastAccumulator = 2;
			Value++;
			
			return Value <= Accumulator;
		}
		return false;
	}
	
	// Continue a Sequence (0 or more of these) //
	inline const bool next( const int TestValue = 1 ) {
		if ( IsActive() ) {
			LastAccumulator = Accumulator + 1;
			Accumulator += TestValue;
			
			return Value <= Accumulator;
		}
		return false;
	}

	// End a Sequence (1 of these, or a Loop) //
	inline const bool end() {
		if ( Value > Accumulator ) {
			Value = 0;

			// If this was a non looping sequence, note as if we looped (run) once //
			if ( LoopCount == 0 ) {
				LoopCount = 1;
			}

			return true;
		}
		return false;
	}

	// Loop a Sequence (0 or 1 of these) //
	inline const bool loop( const int Loops = -1, const int LoopPoint = 0 ) {
		// If not -1, then we're looping a specific number of times //
		if ( Loops != -1 ) {
			if ( LoopCount == Loops )
				return false;
		
			if ( Value > Accumulator ) {
				++LoopCount;
				if ( LoopCount != Loops ) {
					Value = LoopPoint + 1;
				}
				return true;
			}
		}
		// If it is -1, then we loop forever //
		else {
			if ( Value > Accumulator ) {
				++LoopCount;

				Value = LoopPoint + 1;
				return true;
			}
		}
		return false;
	}

public:
	// Return the number of times the Sequence has played (before Resetting) //	
	inline const int get_loop_count() const {
		return LoopCount;	
	}
	
	// Local Begin and Next Scope Only! - Get the Current Iteration //
	inline const int get() const {
		return Value - LastAccumulator;
	}

	// Local Begin and Next Scope Only! - Set the Current Iteration (Be Careful with this!) //
	inline void set( const int NewValue ) {
		Value = NewValue + LastAccumulator - 1;
	}
	
	// Get the Current Frame //
	inline const int get_frame() const {
		return Value - 1;
	}

	// Set the Current Frame (Be Careful with this!) //
	inline void set_frame( const int NewValue ) {
		Value = NewValue + 1;
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __Rebel_Sequence_H__ //
// - ------------------------------------------------------------------------------------------ - //
