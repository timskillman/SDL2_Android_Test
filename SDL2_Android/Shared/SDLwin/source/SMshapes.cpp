#include "SMshapes.h"
#include <cmath>

#define PI 3.14159268f

namespace SMshapes {


	float length2D(vec2f v) { return sqrt(v.x*v.x + v.y*v.y); }

	float angleBetweenTwoVectors2D(vec2f v1, vec2f v2)
	{
		double prod = v1.x*v2.y - v1.y*v2.x;
		return std::fabs((prod < 0 ? -1.0f : 1.0f)*acosf((v1.x*v2.x + v1.y*v2.y) / (length2D(v1)*length2D(v2))));
	}

	//void loadTexture(CIwMaterial *Material, CIwTexture *Texture, const char* imageMap)
	//{
	//	Texture->LoadFromFile(imageMap);
	//	Texture->Upload();
	//	Material->SetTexture(Texture);
	//}

	//void calcUVsphere(vec3f center, std::vector<vec3f> &vecs, std::vector<vec2f> &uvs)
	//{
	//	//Note - there must be as many Vectors and UV coords
	//	for (size_t i = 0; i < uvs.size(); i++) {
	//		uvs[i] = (u3d::getEuler2(vecs[i]-center) / (2*PI)) + vec2f(0.5f,0.5f);
	//	}
	//}

	vec2f dot(vec2f p1, vec2f p2)
	{
		//returns a normalized dot product ...
		float a = p2.x - p1.x;
		float b = p1.y - p2.y;
		float s = sqrt(a*a + b*b);
		if (s > 0.0f) return vec2f(b / s, a / s);
		return vec2f(0.0f, 0.0f);
	}

	float cubeOffs[72] = { -1,1,-1, 1,1,-1, 1,-1,-1, -1,-1,-1,
		1,1,-1, 1,1,1, 1,-1,1, 1,-1,-1,
		1,1,1, -1,1,1, -1,-1,1, 1,-1,1,
		-1,1,1, -1,1,-1, -1,-1,-1, -1,-1,1,
		-1,-1,-1, 1,-1,-1, 1,-1,1, -1,-1,1,
		1,1,-1, -1,1,-1, -1,1,1, 1,1,1 };

	float cnorms[18] = { 0,0,-1.0f, 1.0f,0,0, 0,0,1.0f, -1.0f,0,0, 0,-1.0f,0, 0,1.0f,0 };

	SMmesh cuboid(vec3f pos, vec3f size, bool cstrip)
	{

		/*SMmesh model("Cuboid",CUBOID);

		float cx = 0.0f; float dx = 1.0f / 6.0f;
		for (size_t i = 0; i < 72; i += 3) {
			model.addVert(pos + vec3f(size.x*cubeOffs[i], size.y*cubeOffs[i + 1], size.z*cubeOffs[i + 2]));
			//model.addVert(pos + vec3f(size.x*cubeOffs[i + 3], size.y*cubeOffs[i + 4], size.z*cubeOffs[i + 5]));
			//model.addVert(pos + vec3f(size.x*cubeOffs[i + 6], size.y*cubeOffs[i + 7], size.z*cubeOffs[i + 8]));
			if (i < 18) {
				model.addNorm(cnorms[i], cnorms[i + 1], cnorms[i + 2]);
				model.addNorm(cnorms[i], cnorms[i + 1], cnorms[i + 2]);
				model.addNorm(cnorms[i], cnorms[i + 1], cnorms[i + 2]);
				model.addNorm(cnorms[i], cnorms[i + 1], cnorms[i + 2]);
				if (cstrip) {
					model.addUV(cx+dx, 0);
					model.addUV(cx, 0);
					model.addUV(cx, 1.0f);
					model.addUV(cx+dx, 1.0f);
					cx += dx;
				}
				else {
					model.addUV(1.0f, 0);
					model.addUV(0, 0);
					model.addUV(0, 1.0f);
					model.addUV(1.0f, 1.0f);
				}
			}
		}

		for (int i = 0; i < 24; i++) model.indices.push_back(i);

		model.indexes = model.indices.size();
		model.bbox.bboxFromVerts(model.verts);
		model.mode = IW_GX_QUAD_LIST;*/

		SMmesh model("Cuboid", CUBOID);

		float cx = 0.0f; float dx = 1.0f / 6.0f;
		for (int i = 0; i < 6; i++)
		{
			int iT12 = i * 12;
			model.addVert(pos + vec3f(size.x*cubeOffs[iT12], size.y*cubeOffs[iT12 + 1], size.z*cubeOffs[iT12 + 2])); // 1
			model.addVert(pos + vec3f(size.x*cubeOffs[iT12 + 3], size.y*cubeOffs[iT12 + 4], size.z*cubeOffs[iT12 + 5])); // 2
			model.addVert(pos + vec3f(size.x*cubeOffs[iT12 + 6], size.y*cubeOffs[iT12 + 7], size.z*cubeOffs[iT12 + 8])); // 3

			model.addVert(pos + vec3f(size.x*cubeOffs[iT12], size.y*cubeOffs[iT12 + 1], size.z*cubeOffs[iT12 + 2])); // 1
			model.addVert(pos + vec3f(size.x*cubeOffs[iT12 + 6], size.y*cubeOffs[iT12 + 7], size.z*cubeOffs[iT12 + 8])); // 3
			model.addVert(pos + vec3f(size.x*cubeOffs[iT12 + 9], size.y*cubeOffs[iT12 + 10], size.z*cubeOffs[iT12 + 11])); // 4

			for (int j = 0; j < 18; j+=3) model.addNorm(cnorms[j], cnorms[j+1], cnorms[j+2]);

			if (cstrip)
			{
				model.addUV(cx+dx, 0.0f);
				model.addUV(cx, 0.0f);
				model.addUV(cx, 1.0f);

				model.addUV(cx + dx, 0.0f);
				model.addUV(cx, 1.0f);
				model.addUV(cx + dx, 1.0f);

				cx += dx;
			}
			else
			{
				model.addUV(1.0f, 0.0f);
				model.addUV(0.0f, 0.0f);
				model.addUV(0.0f, 1.0f);

				model.addUV(1.0f, 0.0f);
				model.addUV(0.0f, 1.0f);
				model.addUV(1.0f, 1.0f);
			}
		}

		for (int i = 0; i < 36; i++) model.indices.push_back(i);

		model.indexes = model.indices.size();
		model.bbox.bboxFromVerts(model.verts);
		model.mode = GL_TRIANGLES;

		return model;
	}
	
	void calcPathNormals(std::vector<vec2f> &path, std::vector<vec2f> &normals, float creaseAngle, bool joined)
	{
		//Splits a path by creasAngle threshold
		//If the angle between two lines is greater than the creaseAngle, then split them.

		uint32_t sz = path.size();
		if (sz < 2) return;

		std::vector<vec2f> newPath;
		vec2f p1;
		vec2f p2 = path[0];
		vec2f p3 = path[1];
		vec2f norm;

		//work out first point in path
		newPath.push_back(p2);
		if (joined && sz>2) {
			p1 = path[sz - 2]; 
			if (angleBetweenTwoVectors2D(p2 - p1, p3 - p2) > 0.5f) {
				//normals.push_back(dot(p2, p1));
				//newPath.push_back(p2);
				normals.push_back(dot(p2, p3));
			}
			else {
				normals.push_back(dot(p1 - p2, p3 - p2));
			}
			p1 = path[0];
		}
		else
		{
			p1 = path[0];
			normals.push_back(dot(p2, p3));
		}
		

		//work out normals and points between end and last points
		if (sz > 2) {
			for (size_t i = 1; i < sz - 1; i++) {
				p2 = path[i]; p3 = path[i + 1];
				newPath.push_back(p2);
				if (angleBetweenTwoVectors2D(p2 - p1, p3 - p2) > 0.5f) {
					normals.push_back(dot(p1, p2));
					newPath.push_back(p2);
					normals.push_back(dot(p2, p3));
				}
				else {
					normals.push_back(dot(p1 - p2, p3 - p2));
				}
				p1 = p2;
			}

			//work out last point in path
			p2 = path[sz - 1];
			newPath.push_back(p2);

			if (joined) {
				p3 = path[1];
				if (angleBetweenTwoVectors2D(p2 - p1, p3 - p2) > 0.5f) {
					normals.push_back(dot(p1, p2));
					//newPath.push_back(p2);
					//normals.push_back(dot(p2, p3));
				}
				else {
					normals.push_back(dot(p1 - p2, p3 - p2));
				}
			}
			else
			{
				normals.push_back(normals[normals.size() - 1]);
			}
		}
		else
		{
			normals.push_back(normals[0]);
			newPath.push_back(p3);
		}

		path = newPath;
	}

	SMmesh lathe(std::string name, uint32_t id, vec3f pos, std::vector<vec2f> path, int sides, float rise, float coils, bool invert, float creaseAngle, vec2f prevPoint, vec2f lastPoint, uint32_t uvtype)
	{
		SMmesh model(name, id);

		size_t sz = path.size();
		if (sz < 2) return model;

		std::vector<vec2f> normals;
		calcPathNormals(path, normals, 60, true); // path[0] == path[sz - 1]);
		sz = path.size();

		//for (size_t i = 0; i < sz; i++) {
			//s3eDebugTracePrintf("Vertex = %f,%f, normal = %f,%f", path[i].x, path[i].y, normals[i].x, normals[i].y);
		//}

		int32_t rl = (int32_t)(sides*coils);
		float inv = (invert) ? -1.0f : 1.0f;
		int pn = 0;
		int pp = 0;
		float tcy = 0.0f;
		float tcx = 1.0f / (float)sides;
		float pr = (PI / (float)sides) * 2;
		float rdiv = rise / (float)rl;
		int ss = 0; int sl = 0;

		//Find min y / max y of path
		float miny = path[0].y; float maxy = miny;
		for (size_t p = 0; p < sz; p++) {
			if (path[p].y < miny) miny = path[p].y;
			if (path[p].y > maxy) maxy = path[p].y;
		}
		float cy = (maxy + miny) / 2;

		for (size_t p = 0; p < sz; p++) {

			//Calc verts and normals
			
			//s3eDebugTracePrintf("Vertex = %f,%f, normal = %f,%f", path[p].x, path[p].y, normals[p].x, normals[p].y);

			float risey = path[p].y;
			for (int r = 0; r < rl; r++) {
				float sinr = sin(pr*r*inv);
				float cosr = cos(pr*r*inv);
				model.addVert(pos + vec3f(path[p].x*sinr, risey, path[p].x*cosr));
				model.addNorm(sinr*normals[p].x, normals[p].y, cosr*normals[p].x);
				risey += rdiv;
			}

			//Apply UV mapping ...
			switch (uvtype)
			{
			case UVMAP_CYLINDER: //Cylinder UV mapping
				tcy = 1.0f - ((path[p].y - miny) / (maxy - miny));
				break;
			case UVMAP_SPHERE: //Spherical UV mapping
				tcy = atan2f(path[p].x, path[p].y - cy) / PI;
				if (tcy < 0.0f) tcy = 0.9999f;
				break;
			}
			for (int r = 0; r < rl; r++) model.addUV(tcx*r, tcy);

			model.addVert(pos + vec3f(0, path[p].y, path[p].x));
			model.addNorm(0, normals[p].y, normals[p].x);
			model.addUV(0.9999f, tcy);

			//Add indices ...
			if (p < sz - 1) {
				pn += (rl + 1);
				if ((path[p + 1] != path[p]) || p==(sz-2)) {
					for (int r = 0; r < rl; r++)
					{
						//GL_TRIANGLES
						model.indices.push_back(pp + r);
						model.indices.push_back(pp + r + 1);
						model.indices.push_back(pn + r);

						model.indices.push_back(pn + r);
						model.indices.push_back(pp + r + 1);
						model.indices.push_back(pn + r + 1);
						ss += 6;

						//Lines indexes ...
						model.indiceLines.push_back(pp + r);
						model.indiceLines.push_back(pp + r + 1);
						model.indiceLines.push_back(pp + r + 1);
						model.indiceLines.push_back(pn + r + 1);
						model.indiceLines.push_back(pn + r + 1);
						model.indiceLines.push_back(pn + r);
						model.indiceLines.push_back(pn + r);
						model.indiceLines.push_back(pp + r);

						sl += 8;
					}
					
				}
				pp += (rl + 1);
			}

		}

		/*
		vec2f opxy = path[sz - 2];
		if (lastPoint.x == 0.0f && lastPoint.y == 0.0f) lastPoint = opxy;
		if (prevPoint.x != 0.0f || prevPoint.y != 0.0f) opxy = prevPoint;

		for (int p = 0; p < sz; p++) {
			if (p == (sz - 1)) opxy = lastPoint;
			vec2f pxy = path[p];

			//float tcy = 1.0f - ((pxy.y - miny) / (maxy - miny));

			//Calculate normal between path points ...
			vec2f norm = dot(opxy, pxy);

			for (int r = 0; r < rl; r++) {
				float sinr = sin(pr*r*inv);
				float cosr = cos(pr*r*inv);
				model.addVert(pos + vec3f(pxy.x*sinr, pxy.y, pxy.x*cosr));
				model.addNorm(-sinr*norm.y, norm.x,-cosr*norm.y);
				pxy.y += rdiv;
			}

			//Apply UV mapping ...
			switch (uvtype)
			{
			case UVMAP_CYLINDER: //Cylinder UV mapping
				tcy = 1.0f - ((pxy.y - miny) / (maxy - miny));
				break;
			case UVMAP_SPHERE: //Spherical UV mapping
				tcy = std::atan2f(path[p].x, path[p].y - cy) / PI;
				if (tcy<0.0f) tcy = 0.9999f;
				break;
			}
			for (int r = 0; r < rl; r++) model.addUV(tcx*r, tcy);

			model.addVert(pos.x + 0, pos.y + pxy.y,pos.z + pxy.x);
			model.addNorm(0,norm.x,-norm.y);
			model.addUV(0.9999f,tcy);

			if (p < path.size() - 1) {
				pn += (rl + 1);
				for (int r = 0; r < rl; r++) 
				{
					//GL_TRIANGLES
					model.indices.push_back(pp + r);
					model.indices.push_back(pp + r + 1);
					model.indices.push_back(pn + r);
					model.indices.push_back(pn + r);
					model.indices.push_back(pp + r + 1);
					model.indices.push_back(pn + r + 1);
					ss += 6;

				}
				pp += (rl + 1);
				//for (int r = 0; r < rl; r++)
				//{
				//	//GL_TRIANGLE_STRIP
				//	model.indices.push_back(pp + r);
				//	model.indices.push_back(pn + r);
				//	ss += 2;
				//	model.indices.push_back(pp + sides);
				//	model.indices.push_back(pn + sides);
				//	ss += 2;
				//}

				opxy = pxy;
			}
		}
		*/

		model.indexes = ss; // model.indices.size();
		model.indexLines = sl;
		model.bbox.bboxFromVerts(model.verts);
		model.mode = GL_TRIANGLES;
		return model;
	}

	SMmesh sphere(vec3f pos, float radius, float hemi, int slices, int sides, bool invert)
	{
		std::vector<vec2f> path;
		float st = (PI*(1.0f - hemi)) / (float)slices;
		float inv = invert ? -1.0f : 1.0f;
		for (int r = 0; r < (slices + 1); r++) {
			path.push_back(vec2f(radius*-sin(r*st)*inv, radius*-cos(r*st)));
		}
		return lathe("Sphere",SPHERE,pos, path, sides, 0.0f, 1.0f, false, 90, vec2f(1, path[0].y), vec2f(-1, path[path.size() - 1].y),UVMAP_SPHERE);
	}

	SMmesh torus(vec3f pos, float radius, float ringradius, int ringrots, int sides)
	{
		std::vector<vec2f> path;
		float st = (PI *2.f) / (float)ringrots;
		for (int r = 0; r < (ringrots + 1); r++) {
			path.push_back(vec2f(radius + ringradius*sin(r*st), ringradius*cos(r*st)));
		}
		return lathe("Torus",TORUS,pos, path, sides, 0.0f, 1.0f, true);
	}

	SMmesh spring(vec3f pos, float radius, float length, int coils, float coilradius, int ringrots, int sides)
	{
		std::vector<vec2f> path;
		//float rise = length / coils;
		float st = (PI * 2.f) / (float)ringrots;
		for (int r = 0; r < (ringrots + 1); r++) {
			path.push_back(vec2f(radius + coilradius*sin(r*st), coilradius*cos(r*st)));
		}
		return lathe("Spring",SPRING,pos, path, sides, length, (float)coils);
	}

	SMmesh cone(vec3f pos, float radius, float height, int sides)
	{
		std::vector<vec2f> path;
		path.push_back(vec2f(0, height));
		path.push_back(vec2f(radius, 0));
		path.push_back(vec2f(0, 0));
		return lathe("Cone",CONE,pos, path, sides, 0.0f, 1.0f, true, 60.0f, vec2f(-radius, height*2), vec2f(-radius, 0));
	}

	SMmesh tcone(vec3f pos, float botradius, float topradius, float height, int sides)
	{
		std::vector<vec2f> path;
		path.push_back(vec2f(0, height));
		path.push_back(vec2f(topradius, height));
		path.push_back(vec2f(botradius, 0));
		path.push_back(vec2f(0, 0));
		return lathe("Truncated Cone", TCONE, pos, path, sides, 0.0f, 1.0f, true, 60.0f, vec2f(-1.0f,height));
	}

	SMmesh cylinder(vec3f pos, float radius, float height, int sides)
	{
		std::vector<vec2f> path;
		path.push_back(vec2f(0, height));
		path.push_back(vec2f(radius, height));
		path.push_back(vec2f(radius, 0));
		path.push_back(vec2f(0, 0));
		return lathe("Cylinder", CYLINDER, pos, path, sides, 0.0f, 1.0f, true, 60.0f, vec2f(-1.0f, height));
	}

	SMmesh tube(vec3f pos, float radius1, float radius2, float height, int sides)
	{
		std::vector<vec2f> path;
		path.push_back(vec2f(radius1, height));
		path.push_back(vec2f(radius2, height));
		path.push_back(vec2f(radius2, 0));
		path.push_back(vec2f(radius1, 0));
		path.push_back(vec2f(radius1, height));
		return lathe("Tube",TUBE,pos, path, sides, 0.0f, 1.0f, true);
	}

	//SR3DenvCube environCube(float size, const char* imageMap[])
	//{
	//	SR3DenvCube ecube;
	//	ecube.ecube = cuboid(vec3f(0, 0, 0), vec3f(size,size,size));

	//	loadTexture(ecube.Front, ecube.TFront, imageMap[0]);
	//	loadTexture(ecube.Right, ecube.TRight, imageMap[1]);
	//	loadTexture(ecube.Back, ecube.TBack, imageMap[2]);
	//	loadTexture(ecube.Left, ecube.TLeft, imageMap[3]);
	//	loadTexture(ecube.Bottom, ecube.TBottom, imageMap[4]);
	//	loadTexture(ecube.Top, ecube.TTop, imageMap[5]);

	//	return ecube;
	//}

}
