#pragma once

#include "3D/Shader/Shader.h"

#include <string>
#include <memory>
#include <unordered_map>

namespace MC {
	class ShaderManager {
	private:
		std::unordered_map<std::string, std::shared_ptr<Shader>> m_Shaders;

		bool m_ShouldCleanup;
	public:
		ShaderManager();
		~ShaderManager();

		std::shared_ptr<Shader> GetShader(const std::string& name);
		
		std::unordered_map<std::string, std::shared_ptr<Shader>>& GetManagedShaders();

		void Cleanup();

		void MarkForCleanup();
	};
}