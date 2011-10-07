// - ------------------------------------------------------------------------------------------ - //
#ifndef __MESH_PMEFILE_SIMPLESELFSHADOW_H__
#define __MESH_PMEFILE_SIMPLESELFSHADOW_H__
// - ------------------------------------------------------------------------------------------ - //
#include "PMEFile.h"
// - ------------------------------------------------------------------------------------------ - //
// - ------------------------------------------------------------------------------------------ - //
void SimpleSelfShadow( cPMEFile& Data ) {	
	for ( int MeshIndex = 0; MeshIndex < Data.Mesh.size(); MeshIndex++ ) {
		std::vector< cPMEVertex >& v = Data.Mesh[MeshIndex].Vertex;
		
		for ( int VertexIndex = 0; VertexIndex < v.size(); VertexIndex++ ) {
			// Local face storage //
			std::vector< cPMEFaceGroup::FaceType > Face;
				
			Log( "Vertex %i: %f %f %f", VertexIndex, v[ VertexIndex ].Pos.x, v[ VertexIndex ].Pos.y, v[ VertexIndex ].Pos.z );

				
			// Find all faces containing this vertex //
			for ( int FaceGroupIndex = 0; FaceGroupIndex < Data.Mesh[MeshIndex].FaceGroup.size(); FaceGroupIndex++ ) {
				for ( int FaceIndex = 0; FaceIndex < Data.Mesh[MeshIndex].FaceGroup[FaceGroupIndex].Face.size(); FaceIndex++ ) {
					cPMEFaceGroup::FaceType& ThisFace = Data.Mesh[MeshIndex].FaceGroup[FaceGroupIndex].Face[FaceIndex];
					if ( ThisFace.a == VertexIndex ) {
						Face.push_back( ThisFace );
					}
					else if ( ThisFace.b == VertexIndex ) {
						Face.push_back( ThisFace );
					}
					else if ( ThisFace.c == VertexIndex ) {
						Face.push_back( ThisFace );
					}
				}
			}
			
//			Log( "Faces Found: %i", Face.size() );


			std::vector< Vector3D > Normal;
			
			for ( int idx = 0; idx < Face.size(); idx++ ) {
				Normal.push_back( 
					(v[ Face[idx].b ].Pos - v[ Face[idx].a ].Pos) %
					(v[ Face[idx].c ].Pos - v[ Face[idx].b ].Pos)
					);
			}
			
			int Positive = 0;
			int Negative = 0;
			Real Accumulator = Real::Zero;
			
			for ( int idx = 0; idx < Normal.size(); idx++ ) {
				for ( int idx2 = idx+1; idx2 < Normal.size(); idx2++ ) {
					Real Dot( Normal[idx] * Normal[idx2] );
					Accumulator += Dot;

					if ( Dot >= Real::Zero ) {
						Positive++;
					}
					else {
						Negative++;
					}
				}
			}
			
			Log( "%i %i %f", Positive, Negative, Accumulator );
			
			int Value;
			if ( Positive > Negative ) {
				Value = 255;
			}
			else {
		//		Value = -Accumulator;
		//		if ( Value < 0 )
					Value = 0;
			}
			
			v[VertexIndex].Color = GEL_RGB( Value, Value, Value );

/*			
			// Center Vertex storage //
			std::vector< Vector3D > CenterVertex;
			
			// Calculate center points from the found faces //
			for ( int idx = 0; idx < Face.size(); idx++ ) {
				CenterVertex.push_back(
					( v[ Face[idx].a ].Pos + v[ Face[idx].b ].Pos + v[ Face[idx].c ].Pos ) / Real(3)
					);
			}
			
			// Cheat. If > 3 verts, do a cross product. //
			if ( CenterVertex >= 3 ) {
				// Cross product. Result is a normal to check vs. the vert //
				Vector3D Normal = 
					(CenterVertex[1] - CenterVertex[0]) %
					(CenterVertex[2] - CenterVertex[1]);
					
				
				
			}
			
			// Could technically calculate the vertex normal here too //
*/
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
#endif // __MESH_PMEFILE_SIMPLESELFSHADOW_H__ //
// - ------------------------------------------------------------------------------------------ - //
