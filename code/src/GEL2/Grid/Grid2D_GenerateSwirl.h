// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL2_GRID_GRID2D_GENERATESWIRL_H__
#define __GEL2_GRID_GRID2D_GENERATESWIRL_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Math/IVector.h>
// - ------------------------------------------------------------------------------------------ - //
// NOTE: Swirl map max size with u16 is 65535, i.e. smaller than 256x256 //
template< typename tType >
inline void GenerateSwirlGrid2D( Grid2D<tType>& Dest, const int x1, const int y1 ) {
	const tType Max = (tType)0xFFFFFFFF;
	Dest.Fill( Max );
	
	IVector2D Pos(x1,y1);
	IVector2D Facing(0,-1);

	tType Value = 0;
	Dest.Wrap(Pos.x,Pos.y) = Value++;

	while( true ) {
		IVector2D Turn( Pos+Facing.Tangent() );
		IVector2D Forward( Pos+Facing );
		IVector2D OtherTurn( Pos-Facing.Tangent() );
		
		if ( Dest.Wrap(Turn.x,Turn.y) == Max) {
			Facing = Facing.Tangent();
			Pos = Turn;
			Dest.Wrap(Pos.x,Pos.y) = Value++;
		}
		else if ( Dest.Wrap(Forward.x,Forward.y) == Max ) {
			Pos = Forward;
			Dest.Wrap(Pos.x,Pos.y) = Value++;
		}
		else if ( Dest.Wrap(OtherTurn.x,OtherTurn.y) == Max ) {
			Facing = -Facing.Tangent();
			Pos = OtherTurn;
			Dest.Wrap(Pos.x,Pos.y) = Value++;
		}
		else {
			break;
		}
	};
}
// - ------------------------------------------------------------------------------------------ - //
template< typename tType >
inline const Grid2D<tType> GenerateSwirlGrid2D( const szt w, const szt h, const int CenterX, const int CenterY ) {
	Grid2D<tType> Ret(w,h);
	GenerateSwirlGrid2D( Ret, CenterX, CenterY );
	return Ret;
}
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL2_GRID_GRID2D_GENERATESWIRL_H__ //
// - ------------------------------------------------------------------------------------------ - //
