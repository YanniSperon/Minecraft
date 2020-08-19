#include "MeshManager.h"

MC::MeshManager::MeshManager()
{
	meshes = std::unordered_map<std::string, Mesh3D*>();
}

MC::MeshManager::~MeshManager()
{
	for (auto& it : meshes) {
		delete it.second;
	}
	meshes.clear();
}

MC::Mesh3D* MC::MeshManager::GetMesh(const std::string& name)
{
	return nullptr;
}
