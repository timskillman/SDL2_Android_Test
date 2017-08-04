#include "SMmesh.h"
#include <fstream>

void SMmesh::init(std::string _name, uint32_t id)
{
	name = _name;
	modelId = id;
}

SMmesh::SMmesh()
{
	init("", 0);
}

SMmesh::SMmesh(std::string _name, uint32_t id)
{
	init(_name, id);
}

SMmesh::~SMmesh()
{
}

void SMmesh::render(uint16_t renderMode) //bool renderMaterials, SMmaterial* meshmaterial,
{
	if (indexes > 0) {
		if (uvs.size() > 0) SetUVStream(&uvs.front()); else SetUVStream(NULL);
		if (normals.size() > 0) SetNormStream(&normals.front()); else SetNormStream(NULL);
		if (colours.size() > 0) SetColStream(&colours.front()); else SetColStream(NULL);

		SetVertStream(&verts.front());
		if (renderMode == GL_LINES)
		{
			if (indiceLines.size() == 0) {
				for (uint16_t i = 0; i < indexes; i += 3) {
					indiceLines.push_back(i); indiceLines.push_back(i + 1);
					indiceLines.push_back(i + 1); indiceLines.push_back(i + 2);
					indiceLines.push_back(i + 2); indiceLines.push_back(i);
				}
				indexLines = indexes * 2;
			}
			DrawPrims(renderMode, &indiceLines.front(), indexLines);
		}
		else
			DrawPrims(renderMode, &indices.front(), indexes);
	}
}

//#define TVERTS2DMAX 64000
//static vec2f temp_verts2D[TVERTS2DMAX];
//
//bool SMmesh::touchMesh(vec2f &tp, touchObject &touchOb, matrix3f &pmatrix, matrix3f &scene_matrix, float psp)
//{
//	//Checks if a 2D screen point is touching a triangle of this mesh by transforming the mesh vertices into visible space
//
//	matrix3f smat = pmatrix * scene_matrix;
//
//	//Convert mesh vertices into screen coords using current matrix ...
//	//This is faster than constantly converting shared vertices which must all be parsed in order to Z-check the result!
//	if (verts.size() > TVERTS2DMAX)
//		return false; //should return an error!
//	for (size_t i = 0; i < verts.size(); i++)
//		temp_verts2D[i] = u3d::point3Dto2D(verts[i], psp, smat);
//
//	//
//	float lastz = 10000000;
//	uint32_t tc = 0; uint32_t tb = 0;
//	uint32_t i1 = 0; uint32_t i3 = 2;
//	if (psp > 0) { i1 = 2; i3 = 0; } //flip triangles if scene is rendered in a negative plane
//	for (size_t i = 0; i < verts.size(); i += 3) {
//
//		SR3Dtri2 tri(temp_verts2D[i + i1], temp_verts2D[i + 1], temp_verts2D[i + i3]);
//
//		//Check that triangle bbox is touching point ...
//		if (tri.pointOutsideBounds(tp.x, tp.y)) continue;
//
//		tb++;
//
//		//Check if point inside triangle ..
//		if (tri.windingIsClockwise()) {
//			if (tri.pointInsideTriangle(tp)) {
//
//				vec3f t1 = smat.TransformVec(verts[i]);
//				vec3f t2 = smat.TransformVec(verts[i + 1]);
//				vec3f t3 = smat.TransformVec(verts[i + 2]);
//				float avz = (t1.z + t2.z + t3.z) / 3.f;
//				if (avz < lastz) {
//					touchOb.xy = tp;
//					touchOb.triRef = i;
//					//Store locally transformed triangle vertices ...
//					touchOb.tri3D = SR3Dtri3(pmatrix.TransformVec(verts[i]), pmatrix.TransformVec(verts[i + 1]), pmatrix.TransformVec(verts[i + 2]));
//					touchOb.norm = touchOb.tri3D.unitNormal();
//					touchOb.tri2D = SR3Dtri2(temp_verts2D[i], temp_verts2D[i + 1], temp_verts2D[i + 2]);
//					touchOb.calculateIntersection();
//					lastz = avz;
//					tc++;
//				}
//			}
//		}
//	}
//	//IwTrace(TRITOUCH, ("Triangles touched = %d, %d",tc,tb));
//
//	return touchOb.triRef >= 0;
//}


void SMmesh::translate(vec3f t)
{
	for (size_t i=0; i<verts.size(); i++) verts[i] += t;
}

