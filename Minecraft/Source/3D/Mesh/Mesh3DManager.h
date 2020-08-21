#pragma once

#include "3D/Mesh/Mesh3D.h"

#include <string>
#include <memory>
#include <unordered_map>

namespace MC {
	class Mesh3DManager {
	private:
		std::unordered_map<std::string, std::shared_ptr<Mesh3D>> m_Meshes;

		bool m_ShouldCleanup;
	public:
		Mesh3DManager();
		~Mesh3DManager();

		std::shared_ptr<Mesh3D> GetMesh(const std::string& name);

		std::unordered_map<std::string, std::shared_ptr<Mesh3D>>& GetManagedMesh3Ds();

		void Cleanup();

		void MarkForCleanup();
	};
}