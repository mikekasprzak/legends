// - ------------------------------------------------------------------------------------------ - //
#include "RenderObject.h"
#include "PMEFile.h"
#include <Util/String/String.h>

#include <AssetPool/AssetPool.h>
// - ------------------------------------------------------------------------------------------ - //
cRenderObject LoadPME( const cPMEFile& PME ) {
	cRenderObject Obj;
	
	// Materials //
	{
		// Count Materials //
		size_t MaterialCount = 0;
		for ( size_t idx = 0; idx < PME.Mesh.size(); idx++ ) {
			MaterialCount += PME.Mesh[idx].Material.size();
		}
		
//		printf("Material Count: %i\n", MaterialCount);
		
		Obj.Material = new_GelArray<cROMaterial>(MaterialCount);
		size_t CurrentMaterial = 0;
		for ( size_t idx = 0; idx < PME.Mesh.size(); idx++ ) {
			for ( size_t idx2 = 0; idx2 < PME.Mesh[idx].Material.size(); idx2++ ) {
				std::string File = String::BaseName( String::SystemSlash( PME.Mesh[idx].Material[idx2].ImageFileName ));
				
				Obj.Material->Data[CurrentMaterial].Texture = AssetPool::Load( File.c_str() );
				
				CurrentMaterial++;
			}
		}
	}

	// Vertices //
	{
		// Count Vertices //
		size_t VertexCount = 0;
		for ( size_t idx = 0; idx < PME.Mesh.size(); idx++ ) {
			VertexCount += PME.Mesh[idx].Vertex.size();
		}

		Obj.Vertex = new_GelArray<cROVertex>(VertexCount);
		size_t VertexOffset = 0;
		for ( size_t idx = 0; idx < PME.Mesh.size(); idx++ ) {
			for ( size_t idx2 = 0; idx2 < PME.Mesh[idx].Vertex.size(); idx2++ ) {
				cROVertex& ROVert = Obj.Vertex->Data[VertexOffset + idx2];
				const cPMEVertex& PMEVert = PME.Mesh[idx].Vertex[idx2];
				
				// Broken up per component, in case the vertex types are actually different //
				ROVert.Pos.x = PMEVert.Pos.x;
				ROVert.Pos.y = PMEVert.Pos.y;
				ROVert.Pos.z = PMEVert.Pos.z;
                
				ROVert.Normal.x = PMEVert.Normal.x;
				ROVert.Normal.y = PMEVert.Normal.y;
				ROVert.Normal.z = PMEVert.Normal.z;
                
                ROVert.UV.u = PMEVert.UV.u;
				ROVert.UV.v = PMEVert.UV.v;
                
                ROVert.Color = PMEVert.Color;
			}
			VertexOffset += PME.Mesh[idx].Vertex.size();
		}
	}

	// FaceGroups //
	{
		// Count Vertices //
		size_t FaceGroupCount = 0;
		for ( size_t idx = 0; idx < PME.Mesh.size(); idx++ ) {
			FaceGroupCount += PME.Mesh[idx].FaceGroup.size();
		}
		
		Obj.FaceGroup = new_GelArray<cROFaceGroup>(FaceGroupCount);
		size_t MaterialOffset = 0;
		size_t FaceGroupOffset = 0;
		for ( size_t idx = 0; idx < PME.Mesh.size(); idx++ ) {
			for ( size_t idx2 = 0; idx2 < PME.Mesh[idx].FaceGroup.size(); idx2++ ) {
				cROFaceGroup& ROFaceGroup = Obj.FaceGroup->Data[FaceGroupOffset + idx2];
				const cPMEFaceGroup& PMEFaceGroup = PME.Mesh[idx].FaceGroup[idx2];
				
				ROFaceGroup.MaterialIndex = MaterialOffset + PMEFaceGroup.Material;
				
				ROFaceGroup.Face = new_GelArray<cROFaceGroup::IndexType>(PMEFaceGroup.Face.size()*3);
				for ( size_t idx3 = 0; idx3 < PMEFaceGroup.Face.size(); idx3++ ) {
					// Broken up per component, in case the FaceGroup types are actually different //
					ROFaceGroup.Face->Data[(idx3*3)+0] = PMEFaceGroup.Face[idx3].a;
					ROFaceGroup.Face->Data[(idx3*3)+1] = PMEFaceGroup.Face[idx3].b;
					ROFaceGroup.Face->Data[(idx3*3)+2] = PMEFaceGroup.Face[idx3].c;					
				}
			}
			FaceGroupOffset += PME.Mesh[idx].FaceGroup.size();
			MaterialOffset += PME.Mesh[idx].Material.size();
		}		
	}
	
	return Obj;
}
// - ------------------------------------------------------------------------------------------ - //
