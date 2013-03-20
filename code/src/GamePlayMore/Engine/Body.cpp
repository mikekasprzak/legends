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
			
			Vector3D Line = B->Pos - A->Pos;
			Real Length = Line.NormalizeRet();
			
			Real RadiusSum = A->Radius + B->Radius;
			
			Vector3D VelocityA = A->GetVelocity();
			Vector3D VelocityB = B->GetVelocity();
			
			Vector3D ForceA;
			Vector3D ForceB;
			
			Log( "%f, %f, %f vs %f, %f, %f", VelocityA.x.ToFloat(), VelocityA.y.ToFloat(), VelocityA.z.ToFloat(), VelocityB.x.ToFloat(), VelocityB.y.ToFloat(), VelocityB.z.ToFloat() );
			
			Real Diff = RadiusSum - Length;			
			Real InvMassSum = (A->InvMass + B->InvMass);	// Mass=1 is 1+1 = 2 | Mass=2 is 2+2 (.5+.5) = 4 (1) //
			Diff /= Length * InvMassSum;	// Thus Length/2, Length/1 //
			
			// *** STEP 1: Move Objects out of each other (Penetration) *** //
			A->Pos -= A->InvMass * Line * Diff;		// Scale up by the fraction size (1, .5)
			B->Pos += B->InvMass * Line * Diff;
			
			// *** STEP 2: Restore Energy (Velocity) lost through fixing the penetration //
			A->Old = A->Pos - VelocityA;
			B->Old = B->Pos - VelocityB;
			
			Real MagnitudeA = VelocityA.NormalizeRet();
			Real MagnitudeB = VelocityB.NormalizeRet();		

			Real Impact = dot( VelocityA, VelocityB );

			// *** STEP 4: Determine Collision Type (Opposing vs Not Opposing) *** //
			// Non-standard Collision (Not Opposing) //
			if ( Impact > Real::Zero ) {
				Real ImpactA = dot( VelocityA, Line );

				if ( ImpactA > Real::Zero ) {
					Real MotionA = dot( VelocityA, VelocityB * MagnitudeB );
						
					if ( MotionA < MagnitudeA ) {
						ImpactA *= MagnitudeA - MotionA;
	
						Real ScaleA = Real::One;
						Real MassRatioA = A->GetMass() * B->InvMass;// div B->GetMass();
									
						if ( MassRatioA > Real::One ) {	// Division By Zero Safe //
							ScaleA /= MassRatioA;
						}
						
						// *** STEP 4: Add Forces from A (Optional) *** //
//						B->AddForce( Line * ImpactA * MassRatioA * ScaleA );
//						A->AddForce( -VelocityA * ImpactA * ScaleA );
						ForceB += Line * ImpactA * MassRatioA * ScaleA;
						ForceA += -VelocityA * ImpactA * ScaleA;
					}
				}

				Real ImpactB = dot( VelocityB, -Line );

				if ( ImpactB > Real::Zero ) {
					Real MotionB = dot( VelocityB, VelocityA * MagnitudeA );
		
					if ( MotionB < MagnitudeB ) {
						ImpactB *= MagnitudeB - MotionB;
	
						Real ScaleB = Real::One;
						Real MassRatioB = B->GetMass() * A->InvMass;// div A->GetMass();
									
						if ( MassRatioB > Real::One ) {	// Division By Zero Safe //
							ScaleB /= MassRatioB;
						}
			
						// *** STEP 5: Add Forces from B (Optional) *** //
//						A->AddForce( -Line * ImpactB * MassRatioB * ScaleB );
//						B->AddForce( -VelocityB * ImpactB * ScaleB );
						ForceA += -Line * ImpactB * MassRatioB * ScaleB;
						ForceB += -VelocityB * ImpactB * ScaleB;
					}
				}
			}
			// Standard Collision (Both traveling towards each other (Opposing)) //
			else {
				Real ImpactA = dot( VelocityA, Line );
				{
					ImpactA *= MagnitudeA;
	
					Real ScaleA = Real::One;
					Real MassRatioA = A->GetMass() * B->InvMass;// div B->GetMass();
								
					if ( MassRatioA > Real::One )
					{	// Division By Zero Safe //
						ScaleA /= MassRatioA;
					}
					
					// *** STEP 4: Add Forces from A *** //
//					B->AddForce( Line * ImpactA * MassRatioA * ScaleA );
//					A->AddForce( -VelocityA * ImpactA * ScaleA );
					ForceB += Line * ImpactA * MassRatioA * ScaleA;
					ForceA += -VelocityA * ImpactA * ScaleA;
				}

				Real ImpactB = dot( VelocityB, -Line );
				{
					ImpactB *= MagnitudeB;
	
					Real ScaleB = Real::One;
					Real MassRatioB = B->GetMass() * A->InvMass;// div B->GetMass();
								
					if ( MassRatioB > Real::One )
					{	// Division By Zero Safe //
						ScaleB /= MassRatioB;
					}
					
					// *** STEP 5: Add Forces from B *** //
//					A->AddForce( -Line * ImpactB * MassRatioB * ScaleB );
//					B->AddForce( -VelocityB * ImpactB * ScaleB );
					ForceA += -Line * ImpactB * MassRatioB * ScaleB;
					ForceB += -VelocityB * ImpactB * ScaleB;
				}
			}
			
			// *** STEP 6: Resolve Friction *** //
			
			// TODO: Don't store accumulated forces? Apply directly, but keep copies here.
			// Then friction is a matter of scaling the modified velocity //
			
			// Blah //
			VelocityA = A->GetVelocity();
			VelocityB = B->GetVelocity();
			
			// Whoa... So "sqrt(0.8*0.8) == 0.8" and "sqrt(1.2*1.2) == 1.2". //
			// It's a bit duh, but any two numbers squared, then rooted is the same //
			// Also, if you keep squaring a number, it gradually makes its way towards 1.0 //
			// Negatives don't sqrt. sqrt(0) is 0 (like 0*anything). sqrt(1) is 1. //
			Real FrictionMix = Real::Sqrt(A->GetFriction() * B->GetFriction());//Real::Sqrt( A->InvFriction * B->InvFriction );
			
			A->Old = A->Pos - (VelocityA + ForceA) * FrictionMix;
			B->Old = B->Pos - (VelocityB + ForceB) * FrictionMix;

			Log( "%f, %f, %f !! %f, %f, %f", A->GetVelocity().x.ToFloat(), A->GetVelocity().y.ToFloat(), A->GetVelocity().z.ToFloat(), B->GetVelocity().x.ToFloat(), B->GetVelocity().y.ToFloat(), B->GetVelocity().z.ToFloat() );
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
