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
#ifndef __Rebel_C_Sequence_H__
#define __Rebel_C_Sequence_H__
// - ------------------------------------------------------------------------------------------ - //
typedef struct {
	// The Value Tested and used over time //
	int Value;
	
	// The Accumulator for local sequence generation //
	int Accumulator;
	// The Last Accumulator value, for correct Get and Set returns //
	int LastAccumulator;
	
	// The number of times looped //
	int LoopCount;
} sequence;
// - ------------------------------------------------------------------------------------------ - //
// Constructor //
inline void seq_Init( sequence* Seq ) {
	Seq->Value = 0;
	Seq->Accumulator = 0;
	Seq->LastAccumulator = 0;
	Seq->LoopCount = 0;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Activate a Sequence //
inline void seq_Activate( sequence* Seq ) {
	// Only activate if you weren't active before //
	if ( Seq->Value == 0 )
		Seq->Value = 1;
}
// - ------------------------------------------------------------------------------------------ - //
// Forcefully Activate a Sequence //
inline void seq_ForceActivate( sequence* Seq ) {
	Seq->Value = 1;
}
// - ------------------------------------------------------------------------------------------ - //
// Reset, or prematurely end a sequence (also clears the loop count) //
inline void seq_Reset( sequence* Seq ) {
	Seq->Value = 0;
	Seq->LoopCount = 0;
}
// - ------------------------------------------------------------------------------------------ - //
// If a sequence is currently active //
inline const int seq_IsActive( sequence* Seq ) {
	return Seq->Value != 0;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Start a Sequence (1 of these) //
// Defaults: TestValue = 1 //
inline const int seq_Begin( sequence* Seq, const int TestValue ) {
	if ( seq_IsActive( Seq ) ) {
		Seq->Accumulator = TestValue + 1;
		Seq->LastAccumulator = 2;
		Seq->Value++;
		
		return Seq->Value <= Seq->Accumulator;
	}
	return 0;
}
// - ------------------------------------------------------------------------------------------ - //
// Continue a Sequence (0 or more of these) //
// Defaults: TestValue = 1 //
inline const int seq_Next( sequence* Seq, const int TestValue ) {
	if ( seq_IsActive( Seq ) ) {
		Seq->LastAccumulator = Seq->Accumulator + 1;
		Seq->Accumulator += TestValue;
		
		return Seq->Value <= Seq->Accumulator;
	}
	return 0;
}
// - ------------------------------------------------------------------------------------------ - //
// End a Sequence (1 of these, or a Loop) //
inline const int seq_End( sequence* Seq ) {
	if ( Seq->Value > Seq->Accumulator ) {
		Seq->Value = 0;

		// If this was a non looping sequence, note as if we looped (run) once //
		if ( Seq->LoopCount == 0 ) {
			Seq->LoopCount = 1;
		}

		return Seq->LoopCount;
	}
	return 0;
}
// - ------------------------------------------------------------------------------------------ - //
// Loop a Sequence (0 or 1 of these) //
// Defaults: LoopPoint = 0, Loops = -1 //
inline const int seq_Loop( sequence* Seq, const int Loops, const int LoopPoint ) {
	// If not -1, then we're looping a specific number of times //
	if ( Loops != -1 ) {
		if ( Seq->LoopCount == Loops )
			return 0;
	
		if ( Seq->Value > Seq->Accumulator ) {
			++Seq->LoopCount;
			if ( Seq->LoopCount != Loops ) {
				Seq->Value = LoopPoint + 1;
			}
			return 1;
		}
	}
	// If it is -1, then we loop forever //
	else {
		if ( Seq->Value > Seq->Accumulator ) {
			++Seq->LoopCount;

			Seq->Value = LoopPoint + 1;
			return 1;
		}
	}
	return 0;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Return the number of times the Sequence has played (before Resetting) //	
inline const int seq_GetLoopCount( sequence* Seq ) {
	return Seq->LoopCount;
}
// - ------------------------------------------------------------------------------------------ - //
// Local Begin and Next Scope Only! - Get the Current Iteration //
inline const int seq_Get( sequence* Seq ) {
	return Seq->Value - Seq->LastAccumulator;
}
// - ------------------------------------------------------------------------------------------ - //
// Local Begin and Next Scope Only! - Set the Current Iteration (Be Careful with this!) //
inline void seq_Set( sequence* Seq, const int NewValue ) {
	Seq->Value = NewValue + Seq->LastAccumulator - 1;
}
// - ------------------------------------------------------------------------------------------ - //
// Get the Current Frame //
inline const int seq_GetFrame( sequence* Seq ) {
	return Seq->Value - 1;
}
// - ------------------------------------------------------------------------------------------ - //
// Set the Current Frame (Be Careful with this!) //
inline void seq_SetFrame( sequence* Seq, const int NewValue ) {
	Seq->Value = NewValue + 1;
}
// - ------------------------------------------------------------------------------------------ - //
#endif // __Rebel_C_Sequence_H__ //
// - ------------------------------------------------------------------------------------------ - //
