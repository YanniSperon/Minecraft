#include "TextureManager.h"
#include "Console.h"

MC::TextureManager::TextureManager()
{
	m_Textures = std::unordered_map<std::string, std::shared_ptr<Texture>>();
}

MC::TextureManager::~TextureManager()
{
	m_Textures.clear();
}

std::shared_ptr<MC::Texture> MC::TextureManager::GetTexture(const std::string& name)
{
	if (m_Textures.find(name) != m_Textures.end()) {
		return m_Textures[name];
	}
	else {
		m_Textures[name] = std::make_shared<Texture>(name);
		return m_Textures[name];
	}
}

std::unordered_map<std::string, std::shared_ptr<MC::Texture>>& MC::TextureManager::GetManagedTextures()
{
	return m_Textures;
}

void MC::TextureManager::Cleanup()
{
	if (m_ShouldCleanup) {
		Texture::Unbind();
		auto it = m_Textures.begin();
		while (it != m_Textures.end()) {
			if (it->second.unique() && !it->second->GetHasFakeUser()) {
				it = m_Textures.erase(it);
			}
			else {
				it++;
			}
		}
		m_ShouldCleanup = false;
	}
}

void MC::TextureManager::MarkForCleanup()
{
	m_ShouldCleanup = true;
}
