// - ------------------------------------------------------------------------------------------ - //
#ifndef __GraphicsDraw_Markers3D_H__
#define __GraphicsDraw_Markers3D_H__
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawCircle( const Vector3D& Center, const Vector3D& Radius, const GelColor Color = Current::Color, const int Steps = 16 ) {
/*
	gelSetColor( Color );

	float Verts[Steps*3];
	float FloatSteps = Steps;
    
	for ( int idx = 0; idx < Steps; idx++ ) {
		Verts[(idx*3)+0] = Center.x + (Real::Cos(idx / FloatSteps) * Radius.x);
		Verts[(idx*3)+1] = Center.y + (Real::Sin(idx / FloatSteps) * Radius.y);
		Verts[(idx*3)+2] = Center.z;
	}
    
    glVertexPointer( 3, GL_FLOAT, 0, Verts );
    glDrawArrays( GL_LINE_LOOP, 0, Steps );

	gelRestoreColor( Color );
*/
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawCircle( const Vector3D& Center, const Vector2D& Radius, const GelColor Color = Current::Color, const int Steps = 16 ) {
	gelDrawCircle( Center, Radius.ToVector3D(), Color, Steps );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawCircle( const Vector3D& Center, const Real& Radius, const GelColor Color = Current::Color, const int Steps = 16 ) {
	gelDrawCircle( Center, Vector3D(Radius,Radius,0), Color, Steps );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawCircleFill( const Vector3D& Center, const Vector3D& Radius, const GelColor Color = Current::Color, const int Steps = 16 ) {
/*
	gelSetColor( Color );

	float Verts[Steps*3];
	float FloatSteps = Steps;
    
	for ( int idx = 0; idx < Steps; idx++ ) {
		Verts[(idx*3)+0] = Center.x + (Real::Cos(idx / FloatSteps) * Radius.x);
		Verts[(idx*3)+1] = Center.y + (Real::Sin(idx / FloatSteps) * Radius.y);
		Verts[(idx*3)+2] = Center.z;
	}
    
    glVertexPointer( 3, GL_FLOAT, 0, Verts );
    glDrawArrays( GL_TRIANGLE_FAN, 0, Steps );

	gelRestoreColor( Color );
*/
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawCircleFill( const Vector3D& Center, const Vector2D& Radius, const GelColor Color = Current::Color, const int Steps = 16 ) {
	gelDrawCircleFill( Center, Radius.ToVector3D(), Color, Steps );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawCircleFill( const Vector3D& Center, const Real& Radius, const GelColor Color = Current::Color, const int Steps = 16 ) {
	gelDrawCircleFill( Center, Vector3D(Radius,Radius,0), Color, Steps );
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawSquare( const Vector3D& Center, const Real& Radius, const GelColor Color = Current::Color ) {
	gelDrawRect( Vector3D( Center.x-Radius, Center.y-Radius, Center.z ), Vector3D( Center.x+Radius, Center.y+Radius, Center.z ), Color );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawSquare( const Vector3D& Center, const Vector3D& Radius, const GelColor Color = Current::Color ) {
	gelDrawRect( Center-Radius, Center+Radius, Color );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawSquare( const Vector3D& Center, const Vector2D& Radius, const GelColor Color = Current::Color ) {
	gelDrawSquare( Center, Radius.ToVector3D(), Color );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawSquareFill( const Vector3D& Center, const Real& Radius, const GelColor Color = Current::Color ) {
	gelDrawRectFill( Vector3D( Center.x-Radius, Center.y-Radius, Center.z ), Vector3D( Center.x+Radius, Center.y+Radius, Center.z ), Color );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawSquareFill( const Vector3D& Center, const Vector3D& Radius, const GelColor Color = Current::Color ) {
	gelDrawRectFill( Center-Radius, Center+Radius, Color );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawSquareFill( const Vector3D& Center, const Vector2D& Radius, const GelColor Color = Current::Color ) {
	gelDrawSquareFill( Center, Radius.ToVector3D(), Color );
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawDiamond( const Vector3D& Center, const Real& Radius, const GelColor Color = Current::Color ) {
	gelDrawCircle( Center, Radius, Color, 4 );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawDiamond( const Vector3D& Center, const Vector3D& Radius, const GelColor Color = Current::Color ) {
	gelDrawCircle( Center, Radius, Color, 4 );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawDiamond( const Vector3D& Center, const Vector2D& Radius, const GelColor Color = Current::Color ) {
	gelDrawDiamond( Center, Radius.ToVector3D(), Color );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawDiamondFill( const Vector3D& Center, const Real& Radius, const GelColor Color = Current::Color ) {
	gelDrawCircleFill( Center, Radius, Color, 4 );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawDiamondFill( const Vector3D& Center, const Vector3D& Radius, const GelColor Color = Current::Color ) {
	gelDrawCircleFill( Center, Radius, Color, 4 );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawDiamondFill( const Vector3D& Center, const Vector2D& Radius, const GelColor Color = Current::Color ) {
	gelDrawDiamondFill( Center, Radius.ToVector3D(), Color );
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawRadiusTriangle( const Vector3D& Center, const Real& Radius, const GelColor Color = Current::Color ) {
	gelDrawCircle( Center, Radius, Color, 3 );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawRadiusTriangle( const Vector3D& Center, const Vector3D& Radius, const GelColor Color = Current::Color ) {
	gelDrawCircle( Center, Radius, Color, 3 );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawRadiusTriangle( const Vector3D& Center, const Vector2D& Radius, const GelColor Color = Current::Color ) {
	gelDrawRadiusTriangle( Center, Radius.ToVector3D(), Color );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawRadiusTriangleFill( const Vector3D& Center, const Real& Radius, const GelColor Color = Current::Color ) {
	gelDrawCircleFill( Center, Radius, Color, 3 );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawRadiusTriangleFill( const Vector3D& Center, const Vector3D& Radius, const GelColor Color = Current::Color ) {
	gelDrawCircleFill( Center, Radius, Color, 3 );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawRadiusTriangleFill( const Vector3D& Center, const Vector2D& Radius, const GelColor Color = Current::Color ) {
	gelDrawRadiusTriangleFill( Center, Radius.ToVector3D(), Color );
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawCross( const Vector3D& Center, const Vector3D& Radius, const GelColor Color = Current::Color ) {
/*
	gelSetColor( Color );
 
    float Verts[] = {
		Center.x-Radius.x, Center.y, Center.z,
		Center.x+Radius.x, Center.y, Center.z,
		Center.x, Center.y-Radius.y, Center.z,
		Center.x, Center.y+Radius.y, Center.z,
    };
    
    glVertexPointer( 3, GL_FLOAT, 0, Verts );
    glDrawArrays( GL_LINES, 0, 4 );

	gelRestoreColor( Color );
*/
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawCross( const Vector3D& Center, const Vector2D& Radius, const GelColor Color = Current::Color ) {
	gelDrawCross( Center, Radius.ToVector3D(), Color );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawCross( const Vector3D& Center, const Real& Radius, const GelColor Color = Current::Color ) {
	gelDrawCross( Center, Vector3D(Radius,Radius,0), Color );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawX( const Vector3D& Center, const Vector3D& Radius, const GelColor Color = Current::Color ) {
/*
	gelSetColor( Color );

    float Verts[] = {
		Center.x-Radius.x, Center.y-Radius.y, Center.z,
		Center.x+Radius.x, Center.y+Radius.y, Center.z,
		Center.x+Radius.x, Center.y-Radius.y, Center.z,
		Center.x-Radius.x, Center.y+Radius.y, Center.z,
    };
    
    glVertexPointer( 3, GL_FLOAT, 0, Verts );
    glDrawArrays( GL_LINES, 0, 4 );

	gelRestoreColor( Color );
*/
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawX( const Vector3D& Center, const Vector2D& Radius, const GelColor Color = Current::Color ) {
	gelDrawX( Center, Radius.ToVector3D(), Color );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawX( const Vector3D& Center, const Real& Radius, const GelColor Color = Current::Color ) {
	gelDrawX( Center, Vector3D(Radius,Radius,0), Color );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __GraphicsDraw_Markers3D_H__ //
// - ------------------------------------------------------------------------------------------ - //
