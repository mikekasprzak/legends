// - ------------------------------------------------------------------------------------------ - //
#ifndef __PLAYMORE_ENGINE_VAR_H__
#define __PLAYMORE_ENGINE_VAR_H__
// - ------------------------------------------------------------------------------------------ - //
// This header gets around the circular references and adds all the var types to the Engine parts //
// - ------------------------------------------------------------------------------------------ - //
flex& cShared::Var( const char* Name ) {
	// Check Object First //
	{
		auto Itr = Object->OVar.Data.find( Name );
		if ( Itr != Object->OVar.Data.end() ) {
			return Itr->second;
		}
	}

//	// Then Check the Template (though Object should contain a copy) //
//	{
//		auto Itr = Template->TVar.Data.find( Name );
//		if ( Itr != Template->TVar.Data.end() ) {
//			return Itr->second;
//		}
//	}

	// Then Check the Scene //
	{
		auto Itr = Scene->SVar.Data.find( Name );
		if ( Itr != Scene->SVar.Data.end() ) {
			return Itr->second;
		}
	}

	// Finally Check the Project //
	{
		auto Itr = Project->PVar.Data.find( Name );
		if ( Itr != Project->PVar.Data.end() ) {
			return Itr->second;
		}
	}

	// That all. If we got here, we failed to find one //
	{
		Log( "! ERROR: Invalid Var \"%s\"", Name );
		static flex Dummy;
		return Dummy;
	}
}
flex& cShared::Var( const std::string& Name ) {
	return Var( Name.c_str() );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
flex& cTemplate::Var( const char* Name ) {
	return Shared.Var( Name );
}
flex& cTemplate::Var( const std::string& Name ) {
	return Shared.Var( Name );
}
// - ------------------------------------------------------------------------------------------ - //
#endif // __PLAYMORE_ENGINE_VAR_H__ //
// - ------------------------------------------------------------------------------------------ - //
