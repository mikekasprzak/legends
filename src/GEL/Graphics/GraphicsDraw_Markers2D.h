// - ------------------------------------------------------------------------------------------ - //
#ifndef __GraphicsDraw_Markers2D_H__
#define __GraphicsDraw_Markers2D_H__
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawCircle( const Vector2D& Center, const Vector2D& Radius, const ColorType Color = Current::Color, const int Steps = 16 ) {
//	gelSetColor( Color );

	float Verts[Steps*2];
	float FloatSteps = Steps;
    
	for ( int idx = 0; idx < Steps; idx++ ) {
		Verts[(idx*2)+0] = Center.x + (Real::Cos(idx / FloatSteps) * Radius.x);
		Verts[(idx*2)+1] = Center.y + (Real::Sin(idx / FloatSteps) * Radius.y);
	}
   
	gelDrawLineLoop( (Vector2D*)Verts, Steps, Color );
	
//    glVertexPointer( 2, GL_FLOAT, 0, Verts );
//    glDrawArrays( GL_LINE_LOOP, 0, Steps );
//
//	gelRestoreColor( Color );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawCircle( const Vector2D& Center, const Real& Radius, const ColorType Color = Current::Color, const int Steps = 16 ) {
	gelDrawCircle( Center, Vector2D(Radius,Radius), Color, Steps );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawCircleFill( const Vector2D& Center, const Vector2D& Radius, const ColorType Color = Current::Color, const int Steps = 16 ) {
//	gelSetColor( Color );

	float Verts[Steps*2];
	float FloatSteps = Steps;
    
	for ( int idx = 0; idx < Steps; idx++ ) {
		Verts[(idx*2)+0] = Center.x + (Real::Cos(idx / FloatSteps) * Radius.x);
		Verts[(idx*2)+1] = Center.y + (Real::Sin(idx / FloatSteps) * Radius.y);
	}
    
	gelDrawTriangleFan( (Vector2D*)Verts, Steps, Color );

//    glVertexPointer( 2, GL_FLOAT, 0, Verts );
//    glDrawArrays( GL_TRIANGLE_FAN, 0, Steps );
//
//	gelRestoreColor( Color );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawCircleFill( const Vector2D& Center, const Real& Radius, const ColorType Color = Current::Color, const int Steps = 16 ) {
	gelDrawCircleFill( Center, Vector2D(Radius,Radius), Color, Steps );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawSquare( const Vector2D& Center, const Real& Radius, const ColorType Color = Current::Color ) {
	gelDrawRect( Center.x-Radius, Center.y-Radius, Center.x+Radius, Center.y+Radius, Color );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawSquare( const Vector2D& Center, const Vector2D& Radius, const ColorType Color = Current::Color ) {
	gelDrawRect( Center.x-Radius.x, Center.y-Radius.y, Center.x+Radius.x, Center.y+Radius.y, Color );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawSquareFill( const Vector2D& Center, const Real& Radius, const ColorType Color = Current::Color ) {
	gelDrawRectFill( Center.x-Radius, Center.y-Radius, Center.x+Radius, Center.y+Radius, Color );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawSquareFill( const Vector2D& Center, const Vector2D& Radius, const ColorType Color = Current::Color ) {
	gelDrawRectFill( Center.x-Radius.x, Center.y-Radius.y, Center.x+Radius.x, Center.y+Radius.y, Color );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawDiamond( const Vector2D& Center, const Real& Radius, const ColorType Color = Current::Color ) {
	gelDrawCircle( Center, Radius, Color, 4 );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawDiamond( const Vector2D& Center, const Vector2D& Radius, const ColorType Color = Current::Color ) {
	gelDrawCircle( Center, Radius, Color, 4 );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawDiamondFill( const Vector2D& Center, const Real& Radius, const ColorType Color = Current::Color ) {
	gelDrawCircleFill( Center, Radius, Color, 4 );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawDiamondFill( const Vector2D& Center, const Vector2D& Radius, const ColorType Color = Current::Color ) {
	gelDrawCircleFill( Center, Radius, Color, 4 );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawRadiusTriangle( const Vector2D& Center, const Real& Radius, const ColorType Color = Current::Color ) {
	gelDrawCircle( Center, Radius, Color, 3 );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawRadiusTriangle( const Vector2D& Center, const Vector2D& Radius, const ColorType Color = Current::Color ) {
	gelDrawCircle( Center, Radius, Color, 3 );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawRadiusTriangleFill( const Vector2D& Center, const Real& Radius, const ColorType Color = Current::Color ) {
	gelDrawCircleFill( Center, Radius, Color, 3 );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawRadiusTriangleFill( const Vector2D& Center, const Vector2D& Radius, const ColorType Color = Current::Color ) {
	gelDrawCircleFill( Center, Radius, Color, 3 );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawCross( const Vector2D& Center, const Vector2D& Radius, const ColorType Color = Current::Color ) {
//	gelSetColor( Color );
 
    float Verts[] = {
		Center.x-Radius.x, Center.y,
		Center.x+Radius.x, Center.y,
		Center.x, Center.y-Radius.y,
		Center.x, Center.y+Radius.y,
    };

	gelDrawLines( (Vector2D*)Verts, 4, Color );
    
//    glVertexPointer( 2, GL_FLOAT, 0, Verts );
//    glDrawArrays( GL_LINES, 0, 4 );
//
//	gelRestoreColor( Color );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawCross( const Vector2D& Center, const Real& Radius, const ColorType Color = Current::Color ) {
	gelDrawCross( Center, Vector2D(Radius,Radius), Color );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawX( const Vector2D& Center, const Vector2D& Radius, const ColorType Color = Current::Color ) {
//	gelSetColor( Color );

    float Verts[] = {
		Center.x-Radius.x, Center.y-Radius.y,
		Center.x+Radius.x, Center.y+Radius.y,
		Center.x+Radius.x, Center.y-Radius.y,
		Center.x-Radius.x, Center.y+Radius.y,
    };

	gelDrawLines( (Vector2D*)Verts, 4, Color );
    
//    glVertexPointer( 2, GL_FLOAT, 0, Verts );
//    glDrawArrays( GL_LINES, 0, 4 );
//
//	gelRestoreColor( Color );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawX( const Vector2D& Center, const Real& Radius, const ColorType Color = Current::Color ) {
	gelDrawX( Center, Vector2D(Radius,Radius), Color );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __GraphicsDraw_Markers2D_H__ //
// - ------------------------------------------------------------------------------------------ - //
