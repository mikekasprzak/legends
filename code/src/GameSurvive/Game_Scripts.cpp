// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include "Game.h"
#include <Debug/GelDebug.h>

#include <AssetPool/AssetPool.h>

#include <squirrel.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cGame::InitScripts() {
	vm_ScriptsLoaded = false;

	// TODO: Compiled Version is ".nut.cnut", or ".nut.cnut.lzma"
	// Can probably make a call to the GelDirectory and get all the .nut files //
	
	Script.push_back( vmScript( "/Main.nut" ) );	
}
// - ------------------------------------------------------------------------------------------ - //
void cGame::LoadScripts() {
	Log( "+ Loading Scripts..." );

	for ( size_t idx = 0; idx < Script.size(); idx++ ) {
		Script[idx].Error = vm_CompileAndRun( AssetPool::Get( Script[idx].Handle ), Script[idx].FileName );
	}
	vm_ScriptsLoaded = true;

	Log( "- Done Loading Scripts." );
}
// - ------------------------------------------------------------------------------------------ - //
void cGame::ReloadScripts() {
	if ( vm_ScriptsLoaded ) {
		Log( "+ Scanning %i Scripts for changes...", Script.size() );

		for ( size_t idx = 0; idx < Script.size(); idx++ ) {
			if ( AssetPool::HasChanged( Script[idx].Handle ) ) {
				Log( "* Change detected in \"%s\". Reloading...", Script[idx].FileName );
				AssetPool::Reload( Script[idx].Handle );
				Script[idx].Error = vm_CompileAndRun( AssetPool::Get( Script[idx].Handle ), Script[idx].FileName );
			}
		}

		Log( "- Done Scanning Scripts." );
	}
	else {
		ELog( "Scipts haven't been loaded yet!" );
	}
}
// - ------------------------------------------------------------------------------------------ - //
bool cGame::ScriptErrors() {
	bool Error = false;

	if ( vm_ScriptsLoaded ) {				
		for ( size_t idx = 0; idx < Script.size(); idx++ ) {
			Error |= SQ_FAILED( Script[idx].Error );
		}
	}
	
	return Error;
}
// - ------------------------------------------------------------------------------------------ - //
