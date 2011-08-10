// - ------------------------------------------------------------------------------------------ - //
#include <Debug/Log.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Graphics/GraphicsDraw.h>
// - ------------------------------------------------------------------------------------------ - //
extern void CallExp();
void CallExp() {
	Log( "+ Beginning Experiments...\n" );

#ifdef USES_PAWN
	extern void CallExp_Pawn();
	CallExp_Pawn();
#endif // USES_PAWN //
	
#ifdef USES_WINDOWS		
	extern void CallExp_GelDate();
	CallExp_GelDate();
#endif // USES_WINDOWS //

	extern void CallExp_cJSON();
	CallExp_cJSON();

	extern void CallExp_TinyXML();
	CallExp_TinyXML();
	
	extern void CallExp_Bullet();
	CallExp_Bullet();

	extern void CallExp_AssImp();
	CallExp_AssImp();

	extern void CallExp_Squirrel();
	CallExp_Squirrel();


	Log("+ Now Testing BMFont\n");
	{
		BMFont* MyFont = new_read_BMFont( "Content/Misc/CourierNew.fnt" );
		
		// TODO: Do stuff with a font //
		
		delete_BMFont( MyFont );


		BMFont* MyFont2 = new_read_BMFont( "Content/Misc/Fontin.fnt" );
		
		// TODO: Do stuff with a font //
		
		delete_BMFont( MyFont2 );

		BMFont* MyFont3 = new_read_BMFont( "Content/Misc/Arial.fnt" );
		
		// TODO: Do stuff with a font //
		
		delete_BMFont( MyFont3 );

	}
	Log("- Done Testing BMFont\n");
	Log("\n");

/*	
	//Grid2D<GType>* MyGrid = load_Grid2D<GType>( "Content/Misc/TestFile.tga" );

	Grid2D<GType>* MyGrid = load_Grid2D<GType>( "Content/Misc/Room01.tga" );

//	save_BMP_Grid2D<GType>( MyGrid, "Content/Misc/Horse.bmp" );
//	save_TGA_Grid2D<GType>( MyGrid, "Content/Misc/Horse.tga" );
	
	new_Optimized_TriangleStrips( MyGrid, &Vert, &Index, Vector3D(128,128,64) );
	
	delete_Grid2D( MyGrid );
*/	
//	Log( "%i %i %i %i %i/n", MaxValue<int>(), MaxValue<short>(), MaxValue<char>(), MaxValue<unsigned char>(), MaxValue<unsigned short>() );

	Log( "- Done Experiments.\n" );	
}
