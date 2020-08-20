#pragma once

#include "3D/Shader/Shader.h"

#include <string>
#include <unordered_map>

namespace MC {
	class ShaderManager {
	private:
		std::unordered_map<std::string, Shader*> shaders;
	public:
		ShaderManager();
		~ShaderManager();

		Shader* GetShader(const std::string& name);
	};
}