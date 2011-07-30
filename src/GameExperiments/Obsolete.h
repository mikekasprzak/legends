/*
	// Rings //
	{
		Real Near = 100;
		Real Length = 800;
		
		Real Far = Near + Length;
		Real PlanePos = 0.25;
		
		Real CameraPos = Near + ((Far - Near) * PlanePos);

		CameraMatrix = Look * Matrix4x4::TranslationMatrix( -Vector3D( 0, 0, -CameraPos ) );
		ViewMatrix = Calc_Frustum_PerspectiveProjection( 
			ActualScreen::Width / RefScreen::Scalar,
			ActualScreen::Height / RefScreen::Scalar,
			Real( Near ),
			Real( Far ),
			Real( PlanePos )
			);
	
	//	gelLoadMatrix( SpinMatrix * CameraMatrix * ViewMatrix );
		gelLoadMatrix( ViewMatrix );
		gelMultMatrix( CameraMatrix );
		gelMultMatrix( SpinMatrix );
		gelDrawCircle( Vector2D(0,0), Real(200), RGB_RED );
	}
	
	// -- //

	CameraMatrix = Look * Matrix4x4::TranslationMatrix( -Vector3D( 0, 0, -400 ) );
	ViewMatrix = Calc_Frustum_PerspectiveProjection( 
		ActualScreen::Width / RefScreen::Scalar,
		ActualScreen::Height / RefScreen::Scalar,
		Real( 100 ),
		Real( 700 ),
		Real( 0.5 )
		);

	gelLoadMatrix( SpinMatrix * CameraMatrix * ViewMatrix );
	gelDrawCircle( Vector2D(0,0), Real(200), RGB_ORANGE );

	// -- //

	CameraMatrix = Look * Matrix4x4::TranslationMatrix( -Vector3D( 0, 0, -1400 ) );
	ViewMatrix = Calc_Frustum_PerspectiveProjection( 
		ActualScreen::Width / RefScreen::Scalar,
		ActualScreen::Height / RefScreen::Scalar,
		Real( 1000 ),
		Real( 1800 ),
		Real( 0.5 )
		);

	gelLoadMatrix( SpinMatrix * CameraMatrix * ViewMatrix );
	gelDrawCircle( Vector2D(0,0), Real(200), RGB_YELLOW );

	// -- //

	CameraMatrix = Look * Matrix4x4::TranslationMatrix( -Vector3D( 0, 0, -400 ) );
	ViewMatrix = Calc_Frustum_OrthoProjection( 
		ActualScreen::Width / RefScreen::Scalar,
		ActualScreen::Height / RefScreen::Scalar,
		Real( 100 ),
		Real( 700 )
		);

	gelLoadMatrix( SpinMatrix * CameraMatrix * ViewMatrix );
	gelDrawCircle( Vector2D(0,0), Real(200), RGB_PINK );
*/
/*
	// Waveform Stepping Draw Tests //
	{
		Real Near = 100;
		Real Length = 800;
		
		Real Far = Near + Length;
		Real PlanePos = 0.50;
		
		Real CameraPos = Near + ((Far - Near) * PlanePos);
	
		CameraMatrix = Matrix4x4::TranslationMatrix( -Vector3D( 0, 0, -CameraPos ) );
		ViewMatrix = Calc_Frustum_PerspectiveProjection( 
			ActualScreen::Width / RefScreen::Scalar,
			ActualScreen::Height / RefScreen::Scalar,
			Real( Near ),
			Real( Far ),
			Real( PlanePos )
			);
	
		gelLoadMatrix( ViewMatrix );
		gelMultMatrix( CameraMatrix );
//		gelMultMatrix( SpinMatrix );
		
		Vector3D PointA(-150,0,0);
		Vector3D PointB(150,0,0);
		Vector3D CenterPoint(0,100,0);
		Vector3D CenterPoint2(200,-100,0);
		
//		Vector3D TangentA(2,0.5,0);
//		Vector3D TangentB(0,-0.5,0);
		Vector3D TangentA(300,300,0);
		Vector3D TangentB(300,300,0);
		
		Vector3D PointAOut(-200,1150,0);
		Vector3D PointBOut(200,-1150,0);
		
		static int Stepper = 0;
		Stepper++;
		
		const int PointCount = 32;
		Vector3D Points[PointCount];
		for ( int idx = 0; idx < PointCount; idx++ ) {
			Real Time = Real(idx)/Real(PointCount-1);
			Real Step = Real(Stepper) / Real(100);

//			Points[idx] = Calc_LinearCurve(PointA,PointB,Time); 
//			Points[idx] = PointA + ((idx&1?TangentA:TangentB) * Real(idx * idx) );
//			Points[idx] = Calc_HermiteCurve(PointA,PointB,TangentA,TangentB,Time); 
//			Points[idx] = Calc_CatmullRomCurve(PointAOut,PointA,PointB,PointBOut,Time); 
//			Points[idx] = Calc_RoundedCatmullRomCurve(PointAOut,PointA,PointB,PointBOut,Time); 
//			Points[idx] = Calc_KBSplineCurve(PointAOut,PointA,PointB,PointBOut,Time); 
//			Points[idx] = Calc_BezierCurve(PointA,CenterPoint,PointB,Time); 
//			Points[idx] = Calc_BezierCurve(PointA,CenterPoint,CenterPoint2,PointB,Time); 
//			Points[idx] = Calc_BSplineCurve(PointA,CenterPoint,CenterPoint2,PointB,Time); 
			Points[idx] = PointA + (Vector3D(0,100,0) * ((Time+Step)*Real(1)).Square(.25).Expand()) + (Vector3D(200,0,0)*Time);
//			Points[idx] = PointA + (Vector3D(0,100,0) * (Time*Real(2)).EaseIn().SmoothStep().Expand()) + (Vector3D(200,0,0)*Time);
//			Points[idx] = PointA + (Vector3D(0,100,0) * (Time*Real(2)).SmoothStep().SmoothStep().Expand()) + (Vector3D(200,0,0)*Time);
		}
		
		gelDrawLineStrip( Points, PointCount, RGB_GREEN );
//		gelDrawCircle( PointA, Real(2), RGB_WHITE );
//		gelDrawCircle( PointB, Real(2), RGB_WHITE );
//		gelDrawCircle( CenterPoint, Real(2), RGB_WHITE );
//		gelDrawCircle( CenterPoint2, Real(2), RGB_WHITE );
	}
	*/
	// -- //