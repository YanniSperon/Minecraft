#include "Mesh3DManager.h"
#include "Console.h"

MC::Mesh3DManager::Mesh3DManager()
{
	m_Meshes = std::unordered_map<std::string, std::shared_ptr<Mesh3D>>();
}

MC::Mesh3DManager::~Mesh3DManager()
{
	m_Meshes.clear();
}

std::shared_ptr<MC::Mesh3D> MC::Mesh3DManager::GetMesh(const std::string& name)
{
	if (m_Meshes.find(name) != m_Meshes.end()) {
		return m_Meshes[name];
	}
	else {
		m_Meshes[name] = std::make_shared<Mesh3D>(name, true);
		return m_Meshes[name];
	}
}

std::unordered_map<std::string, std::shared_ptr<MC::Mesh3D>>& MC::Mesh3DManager::GetManagedMesh3Ds()
{
	return m_Meshes;
}

void MC::Mesh3DManager::Cleanup()
{
	if (m_ShouldCleanup) {
		auto it = m_Meshes.begin();
		while (it != m_Meshes.end()) {
			if (it->second.unique() && !it->second->GetHasFakeUser()) {
				it = m_Meshes.erase(it);
			}
			else {
				it++;
			}
		}
		m_ShouldCleanup = false;
	}
}

void MC::Mesh3DManager::MarkForCleanup()
{
	m_ShouldCleanup = true;
}
