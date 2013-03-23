// - ------------------------------------------------------------------------------------------ - //
#include "Engine.h"
#include <Render/Render.h>
#include <Generate/Vertex.h>

#include <Geometry/Vs/3D.h>
// - ------------------------------------------------------------------------------------------ - //
using namespace Render;
// - ------------------------------------------------------------------------------------------ - //
const Matrix4x4 cBody::GetTransform() {
	if ( IsPoint() ) {
		return Matrix4x4::TranslationMatrix( GetPoint() );
	}
	else if ( IsCircle() || IsSphere() ) {
		return Matrix4x4::TranslationMatrix( GetCircle().Pos );
	}
	else if ( IsCircleV() || IsSphereV() ) {
		return Matrix4x4::TranslationMatrix( GetCircleV().Pos );
	}
	else if ( IsHalfCircle() || IsHalfSphere() ) {
		return Matrix4x4::TranslationMatrix( GetHalfCircle().Pos );
	}
	else if ( IsHalfCircleV() || IsHalfSphereV() ) {
		return Matrix4x4::TranslationMatrix( GetHalfCircleV().Pos );
	}
	else if ( IsCapsule() ) {
		return Matrix4x4::TranslationMatrix( GetCapsule().GetCenter() );
	}
	else {
		return Matrix4x4::Identity;
	}
}
// - ------------------------------------------------------------------------------------------ - //
const Rect3D cBody::GetRect() {
	// TODO: Make HalfCircles return a smaller bounding box //
	if ( IsPoint() ) {
		return Rect3D( GetPoint(), Vector3D::Zero );
	}
	else if ( IsCircle() ) {
		return Rect3D( 
			GetCircle().Pos - GetCircle().Radius._xx0(),	// NOTICE: _xx0, not _xxx //
			GetCircle().Radius._xx0() * Real::Two 
			);
	}
	else if ( IsCircleV() ) {
		return Rect3D( 
			GetCircleV().Pos - GetCircleV().Radius._xx0(),	// NOTICE: _xx0, not _xxx //
			GetCircleV().Radius._xx0() * Real::Two 
			);
	}
	else if ( IsSphere() ) {
		return Rect3D( 
			GetSphere().Pos - GetSphere().Radius._xxx(),
			GetSphere().Radius._xxx() * Real::Two 
			);
	}
	else if ( IsSphereV() ) {
		return Rect3D( 
			GetSphereV().Pos - GetSphereV().Radius._xxx(),
			GetSphereV().Radius._xxx() * Real::Two 
			);
	}
	else if ( IsHalfCircle() ) {
		return Rect3D( 
			GetHalfCircle().Pos - GetHalfCircle().Radius._xx0(),	// NOTICE: _xx0, not _xxx //
			GetHalfCircle().Radius._xx0() * Real::Two 
			);
	}
	else if ( IsHalfCircleV() ) {
		return Rect3D( 
			GetHalfCircleV().Pos - GetHalfCircleV().Radius._xx0(),	// NOTICE: _xx0, not _xxx //
			GetHalfCircleV().Radius._xx0() * Real::Two 
			);
	}
	else if ( IsHalfSphere() ) {
		return Rect3D( 
			GetHalfSphere().Pos - GetHalfSphere().Radius._xxx(),
			GetHalfSphere().Radius._xxx() * Real::Two 
			);
	}
	else if ( IsHalfSphereV() ) {
		return Rect3D( 
			GetHalfSphereV().Pos - GetHalfSphereV().Radius._xxx(),
			GetHalfSphereV().Radius._xxx() * Real::Two 
			);
	}
	else if ( IsCapsule() ) {
		Rect3D Ret(
			GetCapsule().PosA - GetCapsule().RadiusA._xx0(),
			GetCapsule().RadiusA._xx0() * Real::Two
			);
		Ret -= Rect3D( 
			GetCapsule().PosB - GetCapsule().RadiusB._xx0(),
			GetCapsule().RadiusB._xx0() * Real::Two 
			);
		return Ret;
	}
	else {
		return Rect3D( Vector3D::Zero, Vector3D::Zero );
	}		
}
// - ------------------------------------------------------------------------------------------ - //
const bool cBody::Check( const cBody& Vs ) const {
	if ( IsPoint() ) {
		if ( Vs.IsPoint() ) {
			return Test_Point_Vs_Point3D( GetPoint(), Vs.GetPoint() );
		}
		else if ( Vs.IsCircle() ) {
			return Test_Point_Vs_Sphere3D( GetPoint(), Vs.GetCircle().Pos, Vs.GetCircle().Radius );
		}
		else if ( Vs.IsCircleV() ) {
			return Test_Point_Vs_Sphere3D( GetPoint(), Vs.GetCircleV().Pos, Vs.GetCircleV().Radius );
		}
		else if ( Vs.IsSphere() ) {
			return Test_Point_Vs_Sphere3D( GetPoint(), Vs.GetSphere().Pos, Vs.GetSphere().Radius );
		}
		else if ( Vs.IsSphereV() ) {
			return Test_Point_Vs_Sphere3D( GetPoint(), Vs.GetSphereV().Pos, Vs.GetSphereV().Radius );
		}
		else if ( Vs.IsCapsule() ) {
			cBody_Sphere Me = Vs.GetCapsule().GetNearestSphere( GetPoint() );
			return Test_Point_Vs_Sphere3D( GetPoint(), Me.Pos, Me.Radius );
		}
	}
	else if ( IsCircle() ) {
		if ( Vs.IsPoint() ) {
			return Test_Point_Vs_Sphere3D( Vs.GetPoint(), GetCircle().Pos, GetCircle().Radius ); // * //
		}
		else if ( Vs.IsCircle() ) {
			return Test_Sphere_Vs_Sphere3D( GetCircle().Pos, GetCircle().Radius, Vs.GetCircle().Pos, Vs.GetCircle().Radius );
		}
		else if ( Vs.IsCircleV() ) {
			return Test_Sphere_Vs_Sphere3D( GetCircle().Pos, GetCircle().Radius, Vs.GetCircleV().Pos, Vs.GetCircleV().Radius );
		}
		else if ( Vs.IsSphere() ) {
			return Test_Sphere_Vs_Sphere3D( GetCircle().Pos, GetCircle().Radius, Vs.GetSphere().Pos, Vs.GetSphere().Radius );
		}
		else if ( Vs.IsSphereV() ) {
			return Test_Sphere_Vs_Sphere3D( GetCircle().Pos, GetCircle().Radius, Vs.GetSphereV().Pos, Vs.GetSphereV().Radius );
		}
		else if ( Vs.IsCapsule() ) {
			cBody_Sphere Me = Vs.GetCapsule().GetNearestSphere( GetCircle().Pos );
			return Test_Sphere_Vs_Sphere3D( GetCircle().Pos, GetCircle().Radius, Me.Pos, Me.Radius );
		}
	}
	else if ( IsCircleV() ) {
		if ( Vs.IsPoint() ) {
			return Test_Point_Vs_Sphere3D( Vs.GetPoint(), GetCircleV().Pos, GetCircleV().Radius ); // * //
		}
		else if ( Vs.IsCircle() ) {
			return Test_Sphere_Vs_Sphere3D( GetCircleV().Pos, GetCircleV().Radius, Vs.GetCircle().Pos, Vs.GetCircle().Radius );
		}
		else if ( Vs.IsCircleV() ) {
			return Test_Sphere_Vs_Sphere3D( GetCircleV().Pos, GetCircleV().Radius, Vs.GetCircleV().Pos, Vs.GetCircleV().Radius );
		}
		else if ( Vs.IsSphere() ) {
			return Test_Sphere_Vs_Sphere3D( GetCircleV().Pos, GetCircleV().Radius, Vs.GetSphere().Pos, Vs.GetSphere().Radius );
		}
		else if ( Vs.IsSphereV() ) {
			return Test_Sphere_Vs_Sphere3D( GetCircleV().Pos, GetCircleV().Radius, Vs.GetSphereV().Pos, Vs.GetSphereV().Radius );
		}
		else if ( Vs.IsCapsule() ) {
			cBody_Sphere Me = Vs.GetCapsule().GetNearestSphere( GetCircleV().Pos );
			return Test_Sphere_Vs_Sphere3D( GetCircleV().Pos, GetCircleV().Radius, Me.Pos, Me.Radius );
		}
	}
	else if ( IsSphere() ) {
		if ( Vs.IsPoint() ) {
			return Test_Point_Vs_Sphere3D( Vs.GetPoint(), GetSphere().Pos, GetSphere().Radius ); // * //
		}
		else if ( Vs.IsCircle() ) {
			return Test_Sphere_Vs_Sphere3D( GetSphere().Pos, GetSphere().Radius, Vs.GetCircle().Pos, Vs.GetCircle().Radius );
		}
		else if ( Vs.IsCircleV() ) {
			return Test_Sphere_Vs_Sphere3D( GetSphere().Pos, GetSphere().Radius, Vs.GetCircleV().Pos, Vs.GetCircleV().Radius );
		}
		else if ( Vs.IsSphere() ) {
			return Test_Sphere_Vs_Sphere3D( GetSphere().Pos, GetSphere().Radius, Vs.GetSphere().Pos, Vs.GetSphere().Radius );
		}
		else if ( Vs.IsSphereV() ) {
			return Test_Sphere_Vs_Sphere3D( GetSphere().Pos, GetSphere().Radius, Vs.GetSphereV().Pos, Vs.GetSphereV().Radius );
		}
		else if ( Vs.IsCapsule() ) {
			cBody_Sphere Me = Vs.GetCapsule().GetNearestSphere( GetSphere().Pos );
			return Test_Sphere_Vs_Sphere3D( GetSphere().Pos, GetSphere().Radius, Me.Pos, Me.Radius );
		}
	}
	else if ( IsSphereV() ) {
		if ( Vs.IsPoint() ) {
			return Test_Point_Vs_Sphere3D( Vs.GetPoint(), GetSphereV().Pos, GetSphereV().Radius ); // * //
		}
		else if ( Vs.IsCircle() ) {
			return Test_Sphere_Vs_Sphere3D( GetSphereV().Pos, GetSphereV().Radius, Vs.GetCircle().Pos, Vs.GetCircle().Radius );
		}
		else if ( Vs.IsCircleV() ) {
			return Test_Sphere_Vs_Sphere3D( GetSphereV().Pos, GetSphereV().Radius, Vs.GetCircleV().Pos, Vs.GetCircleV().Radius );
		}
		else if ( Vs.IsSphere() ) {
			return Test_Sphere_Vs_Sphere3D( GetSphereV().Pos, GetSphereV().Radius, Vs.GetSphere().Pos, Vs.GetSphere().Radius );
		}
		else if ( Vs.IsSphereV() ) {
			return Test_Sphere_Vs_Sphere3D( GetSphereV().Pos, GetSphereV().Radius, Vs.GetSphereV().Pos, Vs.GetSphereV().Radius );
		}
		else if ( Vs.IsCapsule() ) {
			cBody_Sphere Me = Vs.GetCapsule().GetNearestSphere( GetSphereV().Pos );
			return Test_Sphere_Vs_Sphere3D( GetSphereV().Pos, GetSphereV().Radius, Me.Pos, Me.Radius );
		}
	}
	else if ( IsCapsule() ) {
		if ( Vs.IsPoint() ) {
			cBody_Sphere Me = GetCapsule().GetNearestSphere( Vs.GetPoint() );
			return Test_Point_Vs_Sphere3D( Vs.GetPoint(), Me.Pos, Me.Radius ); // * //
		}
		else if ( Vs.IsCircle() ) {
			cBody_Sphere Me = GetCapsule().GetNearestSphere( Vs.GetCircle().Pos );
			return Test_Sphere_Vs_Sphere3D( Me.Pos, Me.Radius, Vs.GetCircle().Pos, Vs.GetCircle().Radius );
		}
		else if ( Vs.IsCircleV() ) {
			cBody_Sphere Me = GetCapsule().GetNearestSphere( Vs.GetCircleV().Pos );
//			Log( "IsCirc (%s) vs (%s)", Vs.GetCircleV().Pos.ToString(), Me.Pos.ToString() );
			bool Val = Test_Sphere_Vs_Sphere3D( Me.Pos, Me.Radius, Vs.GetCircleV().Pos, Vs.GetCircleV().Radius );
			if ( Val )
				Log( "Nert2" );
			return Val;
		}
		else if ( Vs.IsSphere() ) {
			cBody_Sphere Me = GetCapsule().GetNearestSphere( Vs.GetSphere().Pos );
			return Test_Sphere_Vs_Sphere3D( Me.Pos, Me.Radius, Vs.GetSphere().Pos, Vs.GetSphere().Radius );
		}
		else if ( Vs.IsSphereV() ) {
			cBody_Sphere Me = GetCapsule().GetNearestSphere( Vs.GetSphereV().Pos );
			return Test_Sphere_Vs_Sphere3D( Me.Pos, Me.Radius, Vs.GetSphereV().Pos, Vs.GetSphereV().Radius );
		}
//		else if ( Vs.IsCapsule() ) {
//			// Use Nearest Line Test //
//			cBody_Sphere Me = Vs.GetCapsule().GetNearestSphere( GetSphereV().Pos );
//			return Test_Sphere_Vs_Sphere3D( GetSphereV().Pos, GetSphereV().Radius, Me.Pos, Me.Radius );
//		}
	}
	return false;
}
// - ------------------------------------------------------------------------------------------ - //
void cBody::Solve( cBody* Vs ) {
	if ( IsCircleV() ) {
		if ( Vs->IsCircleV() ) {
			::Solve( GetCircleVPtr(), Vs->GetCircleVPtr() );
		}
		else if ( Vs->IsCircle() ) {
			::Solve( GetCircleVPtr(), Vs->GetCirclePtr() );
		}
		else if ( Vs->IsCapsule() ) {
			Log("Colve");
			cBody_Sphere Temp = Vs->GetCapsule().GetNearestSphere( GetCircle().Pos );
			::Solve( GetCircleVPtr(), &Temp );
		}
	}
	else if ( IsCircle() ) {
		if ( Vs->IsCircleV() ) {
			::Solve( Vs->GetCircleVPtr(), GetCirclePtr() );
		}
	}
	else if ( IsCapsule() ) {
		Log("preZolve");
		if ( Vs->IsCircleV() ) {
			Log("Zolve");
			cBody_Sphere Temp = GetCapsule().GetNearestSphere( Vs->GetCircle().Pos );
			::Solve( Vs->GetCircleVPtr(), &Temp );
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cBody::Step() {
	GetBasePtr()->Step();
}
// - ------------------------------------------------------------------------------------------ - //
void cBody::Draw( const Matrix4x4& Matrix ) {
	const GelColor PointColor = GEL_RGB_WHITE;
	const GelColor GeometryColor = GEL_RGB_YELLOW;

	if ( IsPoint() ) {
		const st32 VertCount = size_Vertex3D_RadiusRect();
		Vector3D Verts[ VertCount ];
		generate_Vertex3D_RadiusRect( Verts, GetPoint(), Real(1) );

		Render::Flat( GEL_LINE_LOOP, Matrix, PointColor, Verts, VertCount );
	}
	else if ( IsCircle() || IsCircleV() ) {
		// Debug //
		{
			const st32 VertCount = size_Vertex3D_Circle();
			Vector3D Verts[ VertCount ];
			generate_Vertex3D_Circle( Verts, GetCircle().Pos, GetCircle().Radius );
	
			Render::Flat( GEL_LINE_LOOP, Matrix, GeometryColor, Verts, VertCount );
		}
		// Normals //
		{
			const st32 VertCount = size_Vertex3D_CircleNormals();
			Vector3D Verts[ VertCount ];
			generate_Vertex3D_CircleNormals( Verts, GetCircle().Pos, GetCircle().Radius );
	
			Render::Flat( GEL_LINES, Matrix, GeometryColor, Verts, VertCount );
		}
	}
//	else if ( IsSphere() || IsSphereV() ) {
//		const st32 VertCount = size_Vertex3D_Sphere();
//		Vector3D Verts[ VertCount ];
//		generate_Vertex3D_Sphere( Verts, GetSphere().Pos, GetSphere().Radius );
//
//		Render::Flat( GEL_LINE_LOOP, Matrix, GeometryColor, Verts, VertCount );
//	}
	else if ( IsHalfCircle() || IsHalfCircleV() ) {
		const st32 VertCount = size_Vertex3D_HalfCircle();
		Vector3D Verts[ VertCount ];
		generate_Vertex3D_HalfCircle( Verts, GetHalfCircle().Pos, GetHalfCircle().Radius, GetHalfCircle().Normal );

		Render::Flat( GEL_LINE_LOOP, Matrix, GeometryColor, Verts, VertCount );
	}
	else if ( IsCapsule() ) {
		const st32 VertCount = size_Vertex3D_Capsule();
		Vector3D Verts[ VertCount ];
		generate_Vertex3D_Capsule( Verts, GetCapsule().PosA, GetCapsule().RadiusA, GetCapsule().PosB, GetCapsule().RadiusB );

		Render::Flat( GEL_LINE_LOOP, Matrix, GeometryColor, Verts, VertCount );
	}
}
// - ------------------------------------------------------------------------------------------ - //
