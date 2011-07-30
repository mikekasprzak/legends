// - ------------------------------------------------------------------------------------------ - //
#ifndef __GLGraphics_PMEFile_H__
#define __GLGraphics_PMEFile_H__
// - ------------------------------------------------------------------------------------------ - //
#include <vector>
#include <string>

#include <Debug/Log.h>

#include <Types/UVSet.h>
#include <Types/ABCSet.h>
#include <Math/Vector.h>

#include <Graphics/UV.h>
#include <Graphics/Color.h>
// - ------------------------------------------------------------------------------------------ - //
class cPMEMaterial {
public:
	// Material Name //
	std::string Name;
	
	// Image FileName of our material - TODO: Array //
	std::string ImageFileName;
};
// - ------------------------------------------------------------------------------------------ - //
class cPMEVertex {
public:
	typedef UVSet<UVType> tUVType;
	
	Vector3D Pos;
	Vector3D Normal;
	tUVType UV;
	ColorType Color;
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
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GLGraphics_PMEFile_H__ //
// - ------------------------------------------------------------------------------------------ - //
