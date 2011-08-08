// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_GRAPHICS_GELTEXTURE_H__
#define __GEL_GRAPHICS_GELTEXTURE_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Core/DataBlock.h>
#include <Core/GelAsset.h>
#include <Graphics/GelTexture_NativeHandle.h>
// - ------------------------------------------------------------------------------------------ - //
class GelTexture {
	// The Texture system supports a policy of freeing extra data upon start //
	static bool FreePolicy_Processed;
	static bool FreePolicy_UnProcessed;
	
	static int AllocCount;
	static int AllocSum;
public:
	static void Init( const bool = false, const bool = false );
	static void Exit();
	static void SetFreePolicy( const bool = false, const bool = false );
	
public:
	GelTexture_NativeHandle Handle;			// Texture is in VRAM //
	
	struct GelTexture_Asset {
		GelAssetType Asset;
		union {
			DataBlock* Data;					// Data pointer //
			void* RawPointer;
		};
		
		GelTexture_Asset() {
			Asset.BitMask = GEL_ASSET_NULL;
			Data = 0;
		}
	};
	
	GelTexture_Asset Processed;				// Processed Data Ready to be Transfered //
	GelTexture_Asset UnProcessed;			// Unprocessed Data (may be compressed) //


	// TODO: Load policy above for whether to throw away current texture or not //

	struct GelTexture_Detail {
		int Width, Height;
	};			
	GelTexture_Detail Detail;



public:
	GelTexture() :
		Handle( 0 )
	{
	}
	GelTexture( const char* _FileName ) :
		Handle( 0 )
	{
		Load( _FileName );
	}
	GelTexture( DataBlock* InData ) :
		Handle( 0 )
	{
		Load( InData );
	}

	~GelTexture() {
		Free();
	}
	
	// Defined in Native/PLATFORM/GelTexture.cpp
public:
	void Bind( const int Channel = 0 );
	
private:
	bool Process();
	bool Cache();

	void FreeUnProcessed();
	void FreeProcessed();
	void FreeHandle();

	void FreePolicy();						// Execute the free policy //

public:
	bool Cache( DataBlock* InData );
	bool Cache( const char* _FileName );
	
	bool Load();
	bool Load( DataBlock* InData );
	bool Load( const char* _FileName );
	
	void Free();
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_GRAPHICS_GELTEXTURE_H__ //
// - ------------------------------------------------------------------------------------------ - //
