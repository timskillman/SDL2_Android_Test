#include "SMbbox3d.h"
#include <cmath>

void SMbbox3d::init()
{
	min = vec3f(1e8, 1e8, 1e8);
	max = vec3f(-1e8, -1e8, -1e8);
	radius = 0;
}

SMbbox3d::SMbbox3d() //, bmat(nullptr)
{
	init();
}

SMbbox3d::SMbbox3d(vec3f _min, vec3f _max) : min(_min), max(_max) //, bmat(nullptr)
{
	init();
}

SMbbox3d::~SMbbox3d()
{
	//if (bmat) delete bmat;
}

void SMbbox3d::update(vec3f point) 
{
	if (point.x < min.x) min.x = point.x;
	if (point.x > max.x) max.x = point.x;
	if (point.y < min.y) min.y = point.y;
	if (point.y > max.y) max.y = point.y;
	if (point.z < min.z) min.z = point.z;
	if (point.z > max.z) max.z = point.z;

	//approximate radius from bbox ..
	vec3f d = max - center();
	float r = sqrtf(d.x*d.x + d.y*d.y + d.z*d.z);
	if (r > radius) radius = r;
}

void SMbbox3d::update(SMbbox3d box, matrix3f* mtx)
{
	update(mtx->TransformVec(vec3f(box.min.x, box.min.y, box.min.z)));
	update(mtx->TransformVec(vec3f(box.max.x, box.min.y, box.min.z)));
	update(mtx->TransformVec(vec3f(box.max.x, box.max.y, box.min.z)));
	update(mtx->TransformVec(vec3f(box.min.x, box.max.y, box.min.z)));
	update(mtx->TransformVec(vec3f(box.min.x, box.min.y, box.max.z)));
	update(mtx->TransformVec(vec3f(box.max.x, box.min.y, box.max.z)));
	update(mtx->TransformVec(vec3f(box.max.x, box.max.y, box.max.z)));
	update(mtx->TransformVec(vec3f(box.min.x, box.max.y, box.max.z)));
}

void SMbbox3d::update(SMbbox3d box)
{
	update(vec3f(box.min.x, box.min.y, box.min.z));
	update(vec3f(box.max.x, box.min.y, box.min.z));
	update(vec3f(box.max.x, box.max.y, box.min.z));
	update(vec3f(box.min.x, box.max.y, box.min.z));
	update(vec3f(box.min.x, box.min.y, box.max.z));
	update(vec3f(box.max.x, box.min.y, box.max.z));
	update(vec3f(box.max.x, box.max.y, box.max.z));
	update(vec3f(box.min.x, box.max.y, box.max.z));
}

void SMbbox3d::set(SMbbox3d box, matrix3f* mtx)
{
	init();
	update(box, mtx);
}

void SMbbox3d::bboxFromVerts(std::vector<float> &verts)
{
	min.x = verts[0]; max.x = min.x;
	min.y = verts[1]; max.y = min.y;
	min.z = verts[2]; max.z = min.z;

	//TODO: This should strictly determine bounds by vertices 'used' in the scene according to polygon indices.
	for (size_t i = 0; i < verts.size(); i += 3) {
		if (verts[i] < min.x) min.x = verts[i]; else if (verts[i] > max.x) max.x = verts[i];
		if (verts[i + 1] < min.y) min.y = verts[i + 1]; else if (verts[i + 1] > max.y) max.y = verts[i + 1];
		if (verts[i + 2] < min.z) min.z = verts[i + 2]; else if (verts[i + 2] > max.z) max.z = verts[i + 2];
	}
}

void SMbbox3d::radiusFromVerts(std::vector<vec3f> &verts, vec3f centre)
{
	//Works out the bounding radius of the vertices
	radius = 0;
	//TODO: This should strictly determine bounds by vertices 'used' in the scene according to polygon indices.
	for (size_t i = 0; i < verts.size(); i++) {
		vec3f d = verts[i] - centre;
		float r = sqrtf(d.x*d.x + d.y*d.y + d.z*d.z);
		if (r > radius) radius = r;
	}
}

void SMbbox3d::bboxFromVerts(std::vector<vec3f> &verts)
{
	min = verts[0];
	max = verts[0];

	//TODO: This should strictly determine bounds by vertices 'used' in the scene according to polygon indices.
	for (size_t i = 0; i < verts.size(); i++) {
		if (verts[i].x < min.x) min.x = verts[i].x; else if (verts[i].x > max.x) max.x = verts[i].x;
		if (verts[i].y < min.y) min.y = verts[i].y; else if (verts[i].y > max.y) max.y = verts[i].y;
		if (verts[i].z < min.z) min.z = verts[i].z; else if (verts[i].z > max.z) max.z = verts[i].z;
	}

	radiusFromVerts(verts, center());
}


float SMbbox3d::radiusFromTVerts(std::vector<vec3f> &verts, vec3f centre, matrix3f* mtx)
{
	//Works out the bounding radius of the vertices
	float rad = 0;
	//TODO: This should strictly determine bounds by vertices 'used' in the scene according to polygon indices.
	for (size_t i = 0; i < verts.size(); i++) {
		vec3f d = mtx->TransformVec(verts[i]) - centre;
		float r = sqrtf(d.x*d.x + d.y*d.y + d.z*d.z);
		if (r > rad) rad = r;
	}
	return rad;
}

SMbbox3d SMbbox3d::bboxFromTVerts(matrix3f* mtx)
{
	//Transforms a bounding box with a matrix
	SMbbox3d tbox;
	tbox.update(*this);
	return tbox;
}

void SMbbox3d::bboxFromTVerts(std::vector<vec3f> &verts, matrix3f* mtx)
{
	min = mtx->TransformVec(verts[0]);
	max = mtx->TransformVec(verts[0]);

	//TODO: This should strictly determine bounds by vertices 'used' in the scene according to polygon indices.
	for (size_t i = 0; i < verts.size(); i++) {
		vec3f tvec = mtx->TransformVec(verts[i]);
		if (tvec.x < min.x) min.x = tvec.x; else if (tvec.x > max.x) max.x = tvec.x;
		if (tvec.y < min.y) min.y = tvec.y; else if (tvec.y > max.y) max.y = tvec.y;
		if (tvec.z < min.z) min.z = tvec.z; else if (tvec.z > max.z) max.z = tvec.z;
	}

	radius = radiusFromTVerts(verts, center(), mtx);
}


void SMbbox3d::translate(vec3f t)
{
	min += t; max += t;
}

void SMbbox3d::moveto(vec3f p)
{
	vec3f bc = center();
	min = (min-bc)+p; 
	max = (max-bc)+p;
}