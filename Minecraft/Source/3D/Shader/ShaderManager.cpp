#include "ShaderManager.h"

MC::ShaderManager::ShaderManager()
{
	m_Shaders = std::unordered_map<std::string, std::shared_ptr<Shader>>();
}

MC::ShaderManager::~ShaderManager()
{
	m_Shaders.clear();
}

std::shared_ptr<MC::Shader> MC::ShaderManager::GetShader(const std::string& name)
{
	if (m_Shaders.find(name) != m_Shaders.end()) {
		return m_Shaders[name];
	}
	else {
		m_Shaders[name] = std::make_shared<Shader>(name);
		return m_Shaders[name];
	}
}

void MC::ShaderManager::Cleanup()
{
	if (m_ShouldCleanup) {
		auto it = m_Shaders.begin();
		while (it != m_Shaders.end()) {
			if (it->second.unique() && !it->second->HasFakeUser()) {
				it = m_Shaders.erase(it);
			}
			else {
				it++;
			}
		}
		m_ShouldCleanup = false;
	}
}

void MC::ShaderManager::MarkForCleanup()
{
	m_ShouldCleanup = true;
}
