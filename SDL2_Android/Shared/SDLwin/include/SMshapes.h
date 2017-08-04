#pragma once

#include "SDLGL.h"
#include "SMmesh.h"
#include <vector>
#include <string>

#define SM_SIDES 24

namespace SMshapes {
	//void loadTexture(SMmaterial * Material, SMtexture * Texture, const char* imageMap);
	//void calcUVsphere(vec3f center, std::vector<vec3f> &vecs, std::vector<vec2f> &uvs);

	/* Class that creates all 3D objects
	*/
	enum {
		CUBOID, CYLINDER, SPHERE, SPRING, CONE, TCONE, WEDGE, EXTRUDE, LATHE, TUBE, TORUS, POLYGONS, S3D_FILE, STL_FILE, OBJ_FILE, THREEMF_FILE, PLY_FILE
	};

	enum { UVMAP_CYLINDER, UVMAP_SPHERE };

	SMmesh cuboid(vec3f pos, vec3f size, bool cstrip = false);
	SMmesh lathe(std::string name, uint32_t id, vec3f pos, std::vector<vec2f> path, int sides= SM_SIDES, 
		float rise=0.0f, float coils=1.0f, bool invert = false, float creaseAngle = 60.0f, vec2f prevPoint = vec2f(0,0), 
		vec2f lastPoint = vec2f(0, 0), uint32_t uvtype = UVMAP_CYLINDER);
	SMmesh sphere(vec3f pos, float radius, float hemi=0.0f, int slices= SM_SIDES, int sides = SM_SIDES, bool invert = false);
	SMmesh torus(vec3f pos, float radius, float ringradius, int ringrots=12, int sides = SM_SIDES);
	SMmesh spring(vec3f pos, float radius, float height, int coils, float coilradius, int ringrots=12, int sides = SM_SIDES);
	SMmesh cone(vec3f pos, float radius, float height, int sides = SM_SIDES);
	SMmesh tcone(vec3f pos, float botradius, float topradius, float height, int sides = SM_SIDES);
	SMmesh cylinder(vec3f pos, float radius, float height, int sides = SM_SIDES);
	SMmesh tube(vec3f pos, float innerradius, float outerradius, float height, int sides = SM_SIDES);
	//SMmesh capsule(vec3f pos, float radius, float midlength = 2.0f, int slices = SM_SIDES, int sides = SM_SIDES);
	//SMmesh extrude(vec3f pos, std::vector<vec2f> extrusion, std::vector<vec2f> bevel, float depth = 1.0f, uint16_t divs = 1);
	//SMenvCube environCube(float size, const char* imageMap[]);
}