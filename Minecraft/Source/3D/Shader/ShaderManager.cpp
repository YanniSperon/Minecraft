#include "ShaderManager.h"

MC::ShaderManager::ShaderManager()
{
	shaders = std::unordered_map<std::string, Shader*>();
}

MC::ShaderManager::~ShaderManager()
{
	for (auto& it : shaders) {
		delete it.second;
	}
	shaders.clear();
}

MC::Shader* MC::ShaderManager::GetShader(const std::string& name)
{
	if (shaders.find(name) != shaders.end()) {
		return shaders[name];
	}
	else {
		shaders[name] = new Shader(name);
		return shaders[name];
	}
}
