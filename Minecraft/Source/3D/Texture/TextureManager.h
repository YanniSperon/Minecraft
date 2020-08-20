#pragma once

#include "3D/Texture/Texture.h"

#include <string>
#include <unordered_map>

namespace MC {
	class TextureManager {
	private:
		std::unordered_map<std::string, Texture*> textures;
	public:
		TextureManager();
		~TextureManager();

		Texture* GetTexture(const std::string& name);
	};
}