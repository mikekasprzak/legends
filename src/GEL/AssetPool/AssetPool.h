// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_ASSETPOOL_AssetPool_H__
#define __GEL_ASSETPOOL_AssetPool_H__
// - ------------------------------------------------------------------------------------------ - //
#include "GelAssetHandle.h"
// - ------------------------------------------------------------------------------------------ - //
namespace AssetPool {
	void Init( const char* BaseDirectory );
	void Exit();
	void AddDirectory( const char* Directory );
	
	GelAssetHandle Find( const char* FileName );
	
	GelAssetHandle Load( const char* FileName );
	void Set( const GelAssetHandle Asset );
	void Free( const GelAssetHandle Asset );

//	void ReleaseTextures();
//	void ReloadTextures();
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_ASSETPOOL_AssetPool_H__ //
// - ------------------------------------------------------------------------------------------ - //
