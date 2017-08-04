#pragma once

#include "SMmeshBasic.h"
#include "SMbbox3d.h"
#include "SMmaterial.h"
//#include "touchObject.h"
//#include "utils3d.h"
#include <string>

class SMmesh : public SMmeshBasic
{
public:

	SMmesh();
	SMmesh(std::string name, uint32_t id);
	~SMmesh();

	enum ID_TYPES {
		CUBOID, CYLINDER, SPHERE, SPRING, CONE, TCONE, WEDGE, EXTRUDE, LATHE, TUBE, TORUS, POLYGONS, S3D_FILE, STL_FILE, OBJ_FILE, THREEMF_FILE, PLY_FILE
	};

/// FUNCTIONS ...

	void render(uint16_t renderMode = GL_TRIANGLES); //bool renderMaterials=false, CIwMaterial* meshmaterial = nullptr,
	void setMaterial(SMmaterial* meshmaterial);
	void addUV(float x, float y) { uvs.push_back(vec2f(x, y)); }
	void addUV(vec2f uv) { uvs.push_back(uv); }
	void reset() {
		verts.clear(); uvs.clear(); normals.clear(); colours.clear(); indices.clear(); indiceLines.clear();
		indexes = 0; indexLines = 0; name = ""; bbox.init(); modelId = 0; //material.reset(new CIwMaterial);
	}

	void exportOBJ(std::ostream& outFile, int32_t& lastIndex, matrix3f &parent_matrix, int32_t modelRef, bool print);
	void translate(vec3f t);
	//bool touchMesh(vec2f &tp, touchObject &tco, matrix3f &pmatrix, matrix3f &scene_matrix, float psp);


//// VARIABLES ...

	std::string name;
	uint32_t modelId;
	SMbbox3d bbox;

	SMmaterial material;

	std::vector<vec2f> uvs;
	std::vector<uint32_t> colours;

	std::vector<uint16_t> indiceLines;	//For line rendering (these are quite different from triangle indices)
	uint32_t indexLines;

private:

	void init(std::string _name, uint32_t id);

};
