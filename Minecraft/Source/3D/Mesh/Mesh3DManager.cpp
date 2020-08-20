#include "Mesh3DManager.h"

MC::Mesh3DManager::Mesh3DManager()
{
	meshes = std::unordered_map<std::string, Mesh3D*>();
}

MC::Mesh3DManager::~Mesh3DManager()
{
	for (auto& it : meshes) {
		delete it.second;
	}
	meshes.clear();
}

MC::Mesh3D* MC::Mesh3DManager::GetMesh(const std::string& name)
{
	if (meshes.find(name) != meshes.end()) {
		return meshes[name];
	}
	else {
		meshes[name] = new Mesh3D(name, true);
		return meshes[name];
	}
}
