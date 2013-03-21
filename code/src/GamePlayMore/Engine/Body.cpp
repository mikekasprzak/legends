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
	}
	return false;
}
// - ------------------------------------------------------------------------------------------ - //
void cBody::Solve( cBody* Vs ) {
	if ( IsCircleV() ) {
		if ( Vs->IsCircleV() ) {
			cBody_SphereV* A = GetCircleVPtr();
			cBody_SphereV* B = Vs->GetCircleVPtr();
			
			::Solve( A, B );
			
//			
//			Vector3D Line = B->Pos - A->Pos;
//			Real Length = Line.NormalizeRet();
//			
//			Real RadiusSum = A->Radius + B->Radius;
//									
//			Real Diff = RadiusSum - Length;			
//
//			// TODO: Fix this code so that Penetrations after a collision work correctly. //
//			//       If I don't do this, then objects solved without enough relaxation steps //
//			//       will exhibit the bug I'm trying to avoid by doing this test. //
//			if ( Diff > Real(0.1f) ) {
//				// Take Velocities before we move Pos so we don't accidentially accumulate more force //
//				Vector3D VelocityA = A->GetVelocity();
//				Vector3D VelocityB = B->GetVelocity();
//				
//				// 50% solving, which is less error prone than using the mass here (use it later instead) //
//				Diff *= Real::Half;
//				A->Pos -= Line * Diff;
//				B->Pos += Line * Diff;
//	
//				Real ContactA = dot(VelocityA,Line);
//				Real ContactB = dot(VelocityB,-Line);
//
////				Log( "%f, %f, %f vs %f, %f, %f -- %f %f (%f) [%.2f %.2f]", 
////					VelocityA.x.ToFloat(), VelocityA.y.ToFloat(), VelocityA.z.ToFloat(), 
////					VelocityB.x.ToFloat(), VelocityB.y.ToFloat(), VelocityB.z.ToFloat(), 
////					Length.ToFloat(), RadiusSum.ToFloat(), (RadiusSum-Length).ToFloat(),
////					ContactA.ToFloat(), ContactB.ToFloat() );
//
//				Vector3D ImpactA = Line * ContactA;
//				Vector3D ImpactB = -Line * ContactB;
//				
//				// When Velocity and Line are Parallel, the cross is 0 so Tangents cancel out // 
//				Vector3D TangentA = cross(cross(VelocityA,Line),Line).Normal();
//				Vector3D TangentB = cross(cross(VelocityB,-Line),-Line).Normal();
//								
//				Real MassSum = (A->Mass+B->Mass);
//	
//				Vector3D MomentumA = (A->Mass*ImpactA);
//				Vector3D MomentumB = (B->Mass*ImpactB);
//				Vector3D Momentum = MomentumA + MomentumB;
//	
//				Real Restitution = Real::Max( A->Restitution, B->Restitution );
//				Real Friction = Real::Sqrt( A->Friction * B->Friction );
//				
//				Vector3D ContactVelocityA = ((Restitution*B->Mass*(ImpactB-ImpactA)+Momentum)/MassSum) * Friction;
//				Vector3D ContactVelocityB = ((Restitution*A->Mass*(ImpactA-ImpactB)+Momentum)/MassSum) * Friction;
//	
//				Vector3D TangentVelocityA = TangentA * dot(VelocityA,TangentA);
//				Vector3D TangentVelocityB = TangentB * dot(VelocityB,TangentB);
//
//				A->Old = A->Pos - (TangentVelocityA+ContactVelocityA);
//				B->Old = B->Pos - (TangentVelocityB+ContactVelocityB);
//	
////				Log( "%f, %f, %f !! %f, %f, %f", 
////					A->GetVelocity().x.ToFloat(), A->GetVelocity().y.ToFloat(), A->GetVelocity().z.ToFloat(),
////					B->GetVelocity().x.ToFloat(), B->GetVelocity().y.ToFloat(), B->GetVelocity().z.ToFloat() );
//			}
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
