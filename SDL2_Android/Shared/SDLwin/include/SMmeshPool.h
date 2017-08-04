#pragma once
#include "Vectorf.h"
#include "SMmaterial.h"
#include "SMtexture.h"
#include "SMmesh.h"
#include <vector>
#include <string>
#include <memory>

class SMmeshPool {
public:
	SMmeshPool() {}
	~SMmeshPool() {}

	void appendMesh(SMmesh &mesh) { models.push_back(mesh); }
	size_t meshCount() { return models.size(); }

	int32_t loadTexture(std::string path, std::string name);  //loads a texture and returns a texture reference to the textures array (else -1 if failed)

	std::string getTexturePath(int32_t ref) {
		if (ref >= 0 && ref <= (int32_t)textures.size()) return textureName[ref]; else return "";
	}

	SMtexture* getTexture(int32_t ref) {
		if (ref >= 0 && ref <= (int32_t)textures.size()) return textures[ref].get(); else return nullptr;
	}

	SMmaterial* getMaterial(int32_t ref) {
		if (ref >= 0 && ref <= (int32_t)materials.size()) return materials[ref].get(); else return nullptr;
	}

	void clearAll()
	{
		models.clear();
		materials.clear();
		textures.clear();
		texturePath.clear();
		textureName.clear();
	}

	std::vector<SMmesh> models;
	std::vector<std::shared_ptr<SMmaterial>> materials;
	std::vector<std::shared_ptr<SMtexture>> textures;
	std::vector<std::string> texturePath;
	std::vector<std::string> textureName;
};
