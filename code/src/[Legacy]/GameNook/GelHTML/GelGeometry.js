
// - -------------------------------------------------------------------------------------------------------------- - //
function NearestPoint_on_Sphere( ) {
}
// - -------------------------------------------------------------------------------------------------------------- - //
function NearestPoint_on_Edge_of_Sphere( ) {
}
// - -------------------------------------------------------------------------------------------------------------- - //
function Test_Sphere_vs_Sphere( v1, Radius1, v2, Radius2 ) {
	var Diff = v1.clone();
	Diff.Sub( v2 );
	var RadiusSum = Radius1 + Radius2;
	return Diff.MagnitudeSquared() < (RadiusSum * RadiusSum);
}
// - -------------------------------------------------------------------------------------------------------------- - //
function Solve_Sphere_vs_Sphere( v1, Radius1, v2, Radius2 ) {
	var Diff = v1.clone();
	Diff.Sub( v2 );
	
	var RadiusSum = Radius1 + Radius2;
	var Mag = Diff.NormalizeRet();
	
	if ( Mag > RadiusSum )
		return;
	
	var Push = (RadiusSum - Mag) * 0.5;
	
	Diff.MultScalar( Push );
	
	v1.Add( Diff );
	Diff.Negate();
	v2.Add( Diff );	
}
// - -------------------------------------------------------------------------------------------------------------- - //
function Solve_Sphere_vs_Sphere_with_Mass( v1, Radius1, Mass1, v2, Radius2, Mass2 ) {
	var Diff = v1.clone();
	Diff.Sub( v2 );
	
	var RadiusSum = Radius1 + Radius2;
	var Mag = Diff.NormalizeRet();
	
	if ( Mag > RadiusSum )
		return;
	
	var TotalMass = Mass1+Mass2;
	Mass1 /= TotalMass;
	Mass2 /= TotalMass;
	
	var Push = (RadiusSum - Mag);
	
	var Diff2 = Diff.clone();
	Diff.MultScalar( Push * Mass2 );
	Diff2.MultScalar( Push * Mass1 );
	Diff2.Negate();
	
	v1.Add( Diff );
	v2.Add( Diff2 );	
}
// - -------------------------------------------------------------------------------------------------------------- - //
function Solve_Sphere_vs_Sphere_with_Weights( v1, Radius1, Weight1, v2, Radius2, Weight2 ) {
	var Diff = v1.clone();
	Diff.Sub( v2 );
	
	var RadiusSum = Radius1 + Radius2;
	var Mag = Diff.NormalizeRet();
	
	if ( Mag > RadiusSum )
		return;
	
	var Push = (RadiusSum - Mag);
	
	var Diff2 = Diff.clone();
	Diff.MultScalar( Push * Weight1 );
	Diff2.MultScalar( Push * Weight2 );
	Diff2.Negate();
	
	v1.Add( Diff );
	v2.Add( Diff2 );	
}
// - -------------------------------------------------------------------------------------------------------------- - //

// - -------------------------------------------------------------------------------------------------------------- - //
function NearestPoint_on_AABB( v1, _x, _y, _w, _h ) {
	var Vec = v1.clone();
	
	// Clamp to X //
	if ( Vec.x > _x + _w ) {
		Vec.x = _x + _w;
	}
	else if ( Vec.x < _x ) {
		Vec.x = _x;
	}
	
	// Clamp to Y //
	if ( Vec.y > _y + _h ) {
		Vec.y = _y + _h;
	}
	else if ( Vec.y < _y ) {
		Vec.y = _y;
	}
	
	return Vec;
}
// - -------------------------------------------------------------------------------------------------------------- - //
function NearestPoint_on_Edge_of_AABB( v1, _x, _y, _w, _h ) {
	var Vec = v1.clone();
	
	// Clamp to X //
	if ( Vec.x > _x + _w ) {
		Vec.x = _x + _w;
	}
	else if ( Vec.x < _x ) {
		Vec.x = _x;
	}
	else {
		// Round towards nearest edge //
		if ( (Vec.x - _x) > (_w >> 1) ) {
			Vec.x = _x + _w;
		}
		else {
			Vec.x = _x;
		}
	}
	
	// Clamp to Y //
	if ( Vec.y > _y + _h ) {
		Vec.y = _y + _h;
	}
	else if ( Vec.y < _y ) {
		Vec.y = _y;
	}
	else {
		// Round towards nearest edge //
		if ( (Vec.y - _y) > (_h >> 1) ) {
			Vec.y = _y + _h;
		}
		else {
			Vec.y = _y;
		}		
	}
	
	return Vec;
}
// - -------------------------------------------------------------------------------------------------------------- - //

// - -------------------------------------------------------------------------------------------------------------- - //
function NearestPoint_on_WedgeTopLeft( v1, _x, _y, _w, _h ) {
	var Vec = v1.clone();
	var Change = 0;
	
	// Clamp to X //
	if ( Vec.x > _x + _w ) { 	// Right //
		Vec.x = _x + _w;
		Change--;
	}
	else if ( Vec.x < _x ) { 	// Left //
		Vec.x = _x;
		Change++;
	}
	
	// Clamp to Y //
	if ( Vec.y > _y + _h ) {	// Bottom //
		Vec.y = _y + _h;
		Change--;
	}
	else if ( Vec.y < _y ) {	// Top //
		Vec.y = _y;
		Change++;
	}
	
	// Return if there were changes //
	if ( Change > 0 )
		return Vec;
		
	// If there were no changes, we still have work to do //
	var From = new Vector2D( _x, _y + _h );
	var RayTo = new Vector2D( _x + _w, _y );
	RayTo.Sub( From );
	
	var Me = v1.clone();
	Me.Sub( From );
	
	var RayLength = RayTo.NormalizeRet();
	var Result = Dot( RayTo, Me );
	
	if ( Result < 0 ) {
		Vec.x = _x;
		Vec.y = _y + _h;
	}
	else if ( Result > RayLength ) {
		Vec.x = _x + _w;
		Vec.y = _y;
	}
	else {
		Vec.x = From.x + (RayTo.x * Result);
		Vec.y = From.y + (RayTo.y * Result);
	}
	
	return Vec;
}
// - -------------------------------------------------------------------------------------------------------------- - //

// - -------------------------------------------------------------------------------------------------------------- - //
function NearestPoint_on_WedgeBottomRight( v1, _x, _y, _w, _h ) {
	var Vec = v1.clone();
	var Change = 0;
	
	// Clamp to X //
	if ( Vec.x > _x + _w ) { 	// Right //
		Vec.x = _x + _w;
		Change++;
	}
	else if ( Vec.x < _x ) { 	// Left //
		Vec.x = _x;
		Change--;
	}
	
	// Clamp to Y //
	if ( Vec.y > _y + _h ) {	// Bottom //
		Vec.y = _y + _h;
		Change++;
	}
	else if ( Vec.y < _y ) {	// Top //
		Vec.y = _y;
		Change--;
	}
	
	// Return if there were changes //
	if ( Change > 0 )
		return Vec;
		
	// If there were no changes, we still have work to do //
	var From = new Vector2D( _x, _y + _h );
	var RayTo = new Vector2D( _x + _w, _y );
	RayTo.Sub( From );
	
	var Me = v1.clone();
	Me.Sub( From );
	
	var RayLength = RayTo.NormalizeRet();
	var Result = Dot( RayTo, Me );
	
	if ( Result < 0 ) {
		Vec.x = _x;
		Vec.y = _y + _h;
	}
	else if ( Result > RayLength ) {
		Vec.x = _x + _w;
		Vec.y = _y;
	}
	else {
		Vec.x = From.x + (RayTo.x * Result);
		Vec.y = From.y + (RayTo.y * Result);
	}
	
	return Vec;
}
// - -------------------------------------------------------------------------------------------------------------- - //

// - -------------------------------------------------------------------------------------------------------------- - //
function NearestPoint_on_WedgeTopRight( v1, _x, _y, _w, _h ) {
	var Vec = v1.clone();
	var Change = 0;
	
	// Clamp to X //
	if ( Vec.x > _x + _w ) { 	// Right //
		Vec.x = _x + _w;
		Change++;
	}
	else if ( Vec.x < _x ) { 	// Left //
		Vec.x = _x;
		Change--;
	}
	
	// Clamp to Y //
	if ( Vec.y > _y + _h ) {	// Bottom //
		Vec.y = _y + _h;
		Change--;
	}
	else if ( Vec.y < _y ) {	// Top //
		Vec.y = _y;
		Change++;
	}
	
	// Return if there were changes //
	if ( Change > 0 )
		return Vec;
		
	// If there were no changes, we still have work to do //
	var From = new Vector2D( _x, _y );
	var RayTo = new Vector2D( _x + _w, _y + _h );
	RayTo.Sub( From );
	
	var Me = v1.clone();
	Me.Sub( From );
	
	var RayLength = RayTo.NormalizeRet();
	var Result = Dot( RayTo, Me );
	
	if ( Result < 0 ) {
		Vec.x = _x;
		Vec.y = _y;
	}
	else if ( Result > RayLength ) {
		Vec.x = _x + _w;
		Vec.y = _y + _h;
	}
	else {
		Vec.x = From.x + (RayTo.x * Result);
		Vec.y = From.y + (RayTo.y * Result);
	}
	
	return Vec;
}
// - -------------------------------------------------------------------------------------------------------------- - //


// - -------------------------------------------------------------------------------------------------------------- - //
function NearestPoint_on_WedgeBottomLeft( v1, _x, _y, _w, _h ) {
	var Vec = v1.clone();
	var Change = 0;
	
	// Clamp to X //
	if ( Vec.x > _x + _w ) { 	// Right //
		Vec.x = _x + _w;
		Change--;
	}
	else if ( Vec.x < _x ) { 	// Left //
		Vec.x = _x;
		Change++;
	}
	
	// Clamp to Y //
	if ( Vec.y > _y + _h ) {	// Bottom //
		Vec.y = _y + _h;
		Change++;
	}
	else if ( Vec.y < _y ) {	// Top //
		Vec.y = _y;
		Change--;
	}
	
	// Return if there were changes //
	if ( Change > 0 )
		return Vec;
		
	// If there were no changes, we still have work to do //
	var From = new Vector2D( _x, _y );
	var RayTo = new Vector2D( _x + _w, _y + _h );
	RayTo.Sub( From );
	
	var Me = v1.clone();
	Me.Sub( From );
	
	var RayLength = RayTo.NormalizeRet();
	var Result = Dot( RayTo, Me );
	
	if ( Result < 0 ) {
		Vec.x = _x;
		Vec.y = _y;
	}
	else if ( Result > RayLength ) {
		Vec.x = _x + _w;
		Vec.y = _y + _h;
	}
	else {
		Vec.x = From.x + (RayTo.x * Result);
		Vec.y = From.y + (RayTo.y * Result);
	}
	
	return Vec;
}
// - -------------------------------------------------------------------------------------------------------------- - //

// - -------------------------------------------------------------------------------------------------------------- - //
function Solve_Sphere_vs_XYWHShape( v1, Radius1, _x, _y, _w, _h, _Func ) {
	// NOTE: This will break if v1 enters the AABB //
	var Diff = v1.clone();
	Diff.Sub( _Func( v1, _x,_y,_w,_h ) );
	
	var Mag = Diff.NormalizeRet();

	if ( Mag > Radius1 )
		return;
	
	var Push = (Radius1 - Mag);// * 0.5;
	
	Diff.MultScalar( Push );
	
	v1.Add( Diff );
}
// - -------------------------------------------------------------------------------------------------------------- - //

// - -------------------------------------------------------------------------------------------------------------- - //
function Solve_Sphere_vs_AABB( v1, Radius1, _x, _y, _w, _h ) {
	Solve_Sphere_vs_XYWHShape( v1, Radius1, _x, _y, _w, _h, NearestPoint_on_AABB );
}
// - -------------------------------------------------------------------------------------------------------------- - //
function Solve_Sphere_vs_WedgeBottomLeft( v1, Radius1, _x, _y, _w, _h ) {
	Solve_Sphere_vs_XYWHShape( v1, Radius1, _x, _y, _w, _h, NearestPoint_on_WedgeBottomLeft );
}
// - -------------------------------------------------------------------------------------------------------------- - //
function Solve_Sphere_vs_WedgeTopLeft( v1, Radius1, _x, _y, _w, _h ) {
	Solve_Sphere_vs_XYWHShape( v1, Radius1, _x, _y, _w, _h, NearestPoint_on_WedgeTopLeft );
}
// - -------------------------------------------------------------------------------------------------------------- - //
function Solve_Sphere_vs_WedgeBottomRight( v1, Radius1, _x, _y, _w, _h ) {
	Solve_Sphere_vs_XYWHShape( v1, Radius1, _x, _y, _w, _h, NearestPoint_on_WedgeBottomRight );
}
// - -------------------------------------------------------------------------------------------------------------- - //
function Solve_Sphere_vs_WedgeTopRight( v1, Radius1, _x, _y, _w, _h ) {
	Solve_Sphere_vs_XYWHShape( v1, Radius1, _x, _y, _w, _h, NearestPoint_on_WedgeTopRight );
}
// - -------------------------------------------------------------------------------------------------------------- - //

// - -------------------------------------------------------------------------------------------------------------- - //
function Test_Sphere_vs_XYWHShape( v1, Radius1, _x, _y, _w, _h, _Func ) {
	var Diff = v1.clone();
	Diff.Sub( _Func( v1, _x,_y,_w,_h ) );
	return Diff.MagnitudeSquared() < (Radius1 * Radius1);
}
// - -------------------------------------------------------------------------------------------------------------- - //

// - -------------------------------------------------------------------------------------------------------------- - //
function Test_Sphere_vs_AABB( v1, Radius1, _x, _y, _w, _h ) {
	return Test_Sphere_vs_XYWHShape( v1, Radius1, _x, _y, _w, _h, NearestPoint_on_AABB );
}
// - -------------------------------------------------------------------------------------------------------------- - //
function Test_Sphere_vs_WedgeBottomLeft( v1, Radius1, _x, _y, _w, _h ) {
	return Test_Sphere_vs_XYWHShape( v1, Radius1, _x, _y, _w, _h, NearestPoint_on_WedgeBottomLeft );
}
// - -------------------------------------------------------------------------------------------------------------- - //
function Test_Sphere_vs_WedgeTopLeft( v1, Radius1, _x, _y, _w, _h ) {
	return Test_Sphere_vs_XYWHShape( v1, Radius1, _x, _y, _w, _h, NearestPoint_on_WedgeTopLeft );
}
// - -------------------------------------------------------------------------------------------------------------- - //
function Test_Sphere_vs_WedgeBottomRight( v1, Radius1, _x, _y, _w, _h ) {
	return Test_Sphere_vs_XYWHShape( v1, Radius1, _x, _y, _w, _h, NearestPoint_on_WedgeBottomRight );
}
// - -------------------------------------------------------------------------------------------------------------- - //
function Test_Sphere_vs_WedgeTopRight( v1, Radius1, _x, _y, _w, _h ) {
	return Test_Sphere_vs_XYWHShape( v1, Radius1, _x, _y, _w, _h, NearestPoint_on_WedgeTopRight );
}
// - -------------------------------------------------------------------------------------------------------------- - //
