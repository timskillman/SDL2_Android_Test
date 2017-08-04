#pragma once

#include "SDLGL.h"
#include <vector>

using namespace SDLGL;

class SMmeshBasic {
public:
	/* Basic model with vertices, normals and indices only
	   Used for 3D elements such as gizmo's, handles etc..
	   where a bounding box, material or texture are
	   unneccessary
	   
	   SMmesh uses this parent class and extends it with
	   UV coords and a bounding box. */

	SMmeshBasic() : indexes(0)/*, mode(IW_GX_TRI_LIST)*/ {}
	~SMmeshBasic() {}

	void addVert(float x, float y, float z) { verts.push_back(vec3f(x, y, z)); }
	void addVert(vec3f v) { verts.push_back(v); }
	void addNorm(float x, float y, float z) { normals.push_back(vec3f(x, y, z)); }
	void addNorm(vec3f n) { normals.push_back(n); }

	void render();

	uint16_t mode;
	uint32_t indexes;
	std::vector<vec3f> verts;
	std::vector<vec3f> normals;
	std::vector<uint16_t> indices;
};

