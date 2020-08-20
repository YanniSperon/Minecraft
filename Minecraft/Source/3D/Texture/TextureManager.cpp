#include "TextureManager.h"

MC::TextureManager::TextureManager()
{
	textures = std::unordered_map<std::string, Texture*>();
}

MC::TextureManager::~TextureManager()
{
	for (auto& it : textures) {
		delete it.second;
	}
	textures.clear();
}

MC::Texture* MC::TextureManager::GetTexture(const std::string& name)
{
	if (textures.find(name) != textures.end()) {
		return textures[name];
	}
	else {
		textures[name] = new Texture(name);
		return textures[name];
	}
}