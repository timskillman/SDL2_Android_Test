#pragma once

#include "Vectorf.h"
#include <vector>

class SMbbox3d {
public:
	SMbbox3d();
	SMbbox3d(vec3f origin, vec3f size);
	~SMbbox3d();

	void init();
	void update(vec3f point);
	void update(SMbbox3d box, matrix3f* mtx);
	void update(SMbbox3d box);
	void set(SMbbox3d box, matrix3f* mtx);
	void bboxFromVerts(std::vector<float> &verts);
	void bboxFromVerts(std::vector<vec3f> &verts);
	void bboxFromTVerts(std::vector<vec3f> &verts, matrix3f* mtx);
	void radiusFromVerts(std::vector<vec3f> &verts, vec3f centre);
	float radiusFromTVerts(std::vector<vec3f> &verts, vec3f centre, matrix3f* mtx);
	SMbbox3d bboxFromTVerts(matrix3f* mtx);
	float width() { return max.x - min.x; }
	float depth() { return max.z - min.z; }
	float height() { return max.y - min.y; }
	vec3f center() { return (min+max)/2.0f; }
	vec3f size() { return vec3f(max.x - min.x, max.y - min.y, max.z - min.z); }
	void translate(vec3f t);
	void moveto(vec3f p);
	bool unset() { return (min.x > max.x); }
	
	bool pointInside(vec3f p) { 
		return ((p.x > min.x && p.x < max.x) && (p.y > min.y && p.y < max.y) && (p.z > min.z && p.z < max.z)); }
	bool pointInsideXZ(vec3f p) { 
		return ((p.x > min.x && p.x < max.x) && (p.z > min.z && p.z < max.z)); }

	vec3f min;
	vec3f max;
	float radius;
};