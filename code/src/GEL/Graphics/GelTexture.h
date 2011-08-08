// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_GRAPHICS_GELTEXTURE_H__
#define __GEL_GRAPHICS_GELTEXTURE_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Core/DataBlock.h>
#include <Graphics/GelTexture_NativeHandle.h>
// - ------------------------------------------------------------------------------------------ - //
class GelTexture {
	// The Texture system supports a policy of freeing extra data upon start //
	static bool FreePolicy_Processed;
	static bool FreePolicy_UnProcessed;
public:
	static void SetFreePolicy( const bool, const bool );
	
public:
	GelTexture_NativeHandle Handle;			// Texture is in VRAM //
	
	enum GelTexture_AssetType {
		GEL_ASSET_NULL = 0,
		
		GEL_ASSET_RAW = 1,
		GEL_ASSET_LZMA,
		GEL_ASSET_GZIP,
		GEL_ASSET_BZIP2,
		
		GEL_ASSET_PVR,
		GEL_ASSET_DXT,
		GEL_ASSET_PNG,
		GEL_ASSET_TGA,
		
		GEL_ASSET_HAS_INFO		= 0x10000,
		GEL_ASSET_SHARES_DATA	= 0x20000,
	};
	
	struct GelTexture_Asset {
		union {
			struct {
				int Type:16;				// The type of the Asset //
				bool HasInfo:1;				// Has info about the contents //
				bool SharesData:1;			// Shares data with the other asset //
			};
			GelTexture_AssetType AssetType;	// Whole type of the asset //
		};
		DataBlock* Data;					// Data pointer //
		
		GelTexture_Asset() :
			Type( 0 ),
			Data( 0 )
		{
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
