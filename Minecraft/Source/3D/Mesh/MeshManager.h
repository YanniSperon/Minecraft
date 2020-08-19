#pragma once

#include "3D/Mesh/Mesh3D.h"

#include <string>
#include <unordered_map>

namespace MC {
	class MeshManager {
	private:
		std::unordered_map<std::string, Mesh3D*> meshes;
	public:
		MeshManager();
		~MeshManager();

		Mesh3D* GetMesh(const std::string& name);
	};
}