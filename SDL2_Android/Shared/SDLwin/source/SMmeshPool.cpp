#include "SMmeshPool.h"

int32_t SMmeshPool::loadTexture(std::string path, std::string name) {

	for (size_t i = 0; i < textures.size(); i++)
		if ((name== textureName[i]) && (path == texturePath[i])) return i;

	std::shared_ptr<SMmaterial> Material;
	Material.reset(new SMmaterial());
	Material->SetColAmbient(0xffffff);
	std::shared_ptr<SMtexture> Texture;
	Texture.reset(new SMtexture());
	std::string filename = path + "/" + name;
	SDL_Log("Loading texture '%s'", filename.c_str());

	Texture->LoadFromFile(filename.c_str());
	if (Texture.get() != nullptr) {
		Material->SetTexture(Texture.get());
		Texture->Upload();
		textures.push_back(Texture);
		materials.push_back(Material);
		texturePath.push_back(path);
		textureName.push_back(name);
		return textures.size() - 1;
	}

	return -1;
}
