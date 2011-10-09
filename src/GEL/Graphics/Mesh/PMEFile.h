// - ------------------------------------------------------------------------------------------ - //
#ifndef __GLGraphics_PMEFile_H__
#define __GLGraphics_PMEFile_H__
// - ------------------------------------------------------------------------------------------ - //
#include <vector>
#include <string>

#include <Debug/GelDebug.h>

#include <Types/UVSet.h>
#include <Types/ABCSet.h>
#include <Math/Vector.h>

#include <Graphics/GelUV.h>
#include <Graphics/GelColor.h>

#include <AssetPool/AssetPool.h>

// - ------------------------------------------------------------------------------------------ - //
class cPMEMaterial {
public:
	// Material Name (NOT texture name) //
	std::string Name;
	
	// Image FileName of our material - TODO: Array //
	std::string ImageFileName;
	
	GelAssetHandle Texture;
};
// - ------------------------------------------------------------------------------------------ - //
class cPMEVertex {
public:
	typedef UVSet<GelUV> tUVType;
	
	Vector3D Pos;
	Vector3D Normal;
	tUVType UV;
	GelColor Color;
};
// - ------------------------------------------------------------------------------------------ - //
class cPMEFaceGroup {
public:
	typedef ABCSet<unsigned short> FaceType;
	
	int Material;
	std::vector< FaceType > Face;
};
// - ------------------------------------------------------------------------------------------ - //
class cPMEMesh {
public:
	// Mesh Name //
	std::string Name;
	
	// Materials //
	std::vector<cPMEMaterial> Material;

	std::vector<cPMEVertex> Vertex;
	std::vector<cPMEFaceGroup> FaceGroup;
};
// - ------------------------------------------------------------------------------------------ - //
class cPMEFile {
public:
	std::string FileName;

	std::vector<cPMEMesh> Mesh;
public:
	cPMEFile()
	{
	}
	
	cPMEFile( const char* _FileName ) :
		FileName( _FileName )
	{
		TextLoad();
	}

public:	
	void TextLoad();
	void TextSave();
	
	void Import( const char* _FileName );
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GLGraphics_PMEFile_H__ //
// - ------------------------------------------------------------------------------------------ - //
