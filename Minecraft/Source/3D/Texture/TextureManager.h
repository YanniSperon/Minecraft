#pragma once

#include "3D/Texture/Texture.h"

#include <string>
#include <memory>
#include <unordered_map>

namespace MC {
	class TextureManager {
	private:
		std::unordered_map<std::string, std::shared_ptr<Texture>> m_Textures;

		bool m_ShouldCleanup;
	public:
		TextureManager();
		~TextureManager();

		std::shared_ptr<Texture> GetTexture(const std::string& name);

		void Cleanup();

		void MarkForCleanup();
	};
}