#pragma once

#include "3D/Mesh/Mesh3D.h"

#include <string>
#include <unordered_map>

namespace MC {
	class Mesh3DManager {
	private:
		std::unordered_map<std::string, Mesh3D*> meshes;
	public:
		Mesh3DManager();
		~Mesh3DManager();

		Mesh3D* GetMesh(const std::string& name);
	};
}