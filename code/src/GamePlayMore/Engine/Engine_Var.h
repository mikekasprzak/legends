// - ------------------------------------------------------------------------------------------ - //
#ifndef __PLAYMORE_ENGINE_VAR_H__
#define __PLAYMORE_ENGINE_VAR_H__
// - ------------------------------------------------------------------------------------------ - //
// This header gets around the circular references and adds all the var types to the Engine parts //
// - ------------------------------------------------------------------------------------------ - //
flex& cShared::Var4( const char* Name ) {
	// Check the Object //
	if ( Object ) {
		auto Itr = Object->OVar.Data.find( Name );
		if ( Itr != Object->OVar.Data.end() ) {
			return Itr->second;
		}
	}

	// Then Check the Template (though Object should contain a copy) //
	if ( Template ) {
		auto Itr = Template->TVar.Data.find( Name );
		if ( Itr != Template->TVar.Data.end() ) {
			return Itr->second;
		}
	}

	// Then Check the Scene //
	if ( Scene ) {
		auto Itr = Scene->SVar.Data.find( Name );
		if ( Itr != Scene->SVar.Data.end() ) {
			return Itr->second;
		}
	}

	// Finally Check the Project //
	if ( Project ) {
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
flex& cShared::Var4( const std::string& Name ) {
	return Var4( Name.c_str() );
}
// - ------------------------------------------------------------------------------------------ - //
flex& cShared::Var3( const char* Name ) {
	// Check the Object //
	if ( Object ) {
		auto Itr = Object->OVar.Data.find( Name );
		if ( Itr != Object->OVar.Data.end() ) {
			return Itr->second;
		}
	}

	// Then Check the Scene //
	if ( Scene ) {
		auto Itr = Scene->SVar.Data.find( Name );
		if ( Itr != Scene->SVar.Data.end() ) {
			return Itr->second;
		}
	}

	// Finally Check the Project //
	if ( Project ) {
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
flex& cShared::Var3( const std::string& Name ) {
	return Var3( Name.c_str() );
}
// - ------------------------------------------------------------------------------------------ - //
flex& cShared::Var2( const char* Name ) {
	// Check the Scene //
	if ( Scene ) {
		auto Itr = Scene->SVar.Data.find( Name );
		if ( Itr != Scene->SVar.Data.end() ) {
			return Itr->second;
		}
	}

	// Finally Check the Project //
	if ( Project ) {
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
flex& cShared::Var2( const std::string& Name ) {
	return Var2( Name.c_str() );
}
// - ------------------------------------------------------------------------------------------ - //
flex& cShared::TVar( const char* Name ) {
	return Template->TVar( Name );
}
flex& cShared::TVar( const std::string& Name ) {
	return Template->TVar( Name );
}
flex& cShared::OVar( const char* Name ) {
	return Object->OVar( Name );
}
flex& cShared::OVar( const std::string& Name ) {
	return Object->OVar( Name );
}
flex& cShared::SVar( const char* Name ) {
	return Scene->SVar( Name );
}
flex& cShared::SVar( const std::string& Name ) {
	return Scene->SVar( Name );
}
flex& cShared::PVar( const char* Name ) {
	return Project->PVar( Name );
}
flex& cShared::PVar( const std::string& Name ) {
	return Project->PVar( Name );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
flex& cTemplate::Var( const char* Name ) {
	return Shared.Var3( Name );
}
flex& cTemplate::Var( const std::string& Name ) {
	return Shared.Var3( Name );
}
// - ------------------------------------------------------------------------------------------ - //
flex& cTemplate::OVar( const char* Name ) {
	return Shared.OVar( Name );
}
flex& cTemplate::OVar( const std::string& Name ) {
	return Shared.OVar( Name );
}
flex& cTemplate::SVar( const char* Name ) {
	return Shared.SVar( Name );
}
flex& cTemplate::SVar( const std::string& Name ) {
	return Shared.SVar( Name );
}
flex& cTemplate::PVar( const char* Name ) {
	return Shared.PVar( Name );
}
flex& cTemplate::PVar( const std::string& Name ) {
	return Shared.PVar( Name );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
flex& cScene::Var( const char* Name ) {
	return Shared.Var2( Name );
}
flex& cScene::Var( const std::string& Name ) {
	return Shared.Var2( Name );
}
// - ------------------------------------------------------------------------------------------ - //
flex& cScene::PVar( const char* Name ) {
	return Shared.PVar( Name );
}
flex& cScene::PVar( const std::string& Name ) {
	return Shared.PVar( Name );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
flex& cProject::Var( const char* Name ) {
	return Shared.PVar( Name );
}
flex& cProject::Var( const std::string& Name ) {
	return Shared.PVar( Name );
}
// - ------------------------------------------------------------------------------------------ - //
#endif // __PLAYMORE_ENGINE_VAR_H__ //
// - ------------------------------------------------------------------------------------------ - //
