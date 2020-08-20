#pragma once

#include <glew.h>
#include <string>

#include "Vendor/glm/glm.hpp"

namespace MC {
	class Shader {
	private:
		GLuint m_ID;

		bool m_FakeUser;
	public:
		Shader(const std::string& name);
		~Shader();

		void LoadShader(const char* geometryShaderPath, const char* fragmentShaderPath);

		void Bind();

		void SetBool(const std::string& name, bool value);
		void SetInt(const std::string& name, int value);

		void SetFloat(const std::string& name, float value);
		void Set2Float(const std::string& name, float x, float y);
		void Set3Float(const std::string& name, float x, float y, float z);
		void Set4Float(const std::string& name, float x, float y, float z, float w);

		void SetVec2(const std::string& name, const glm::vec2& value);
		void SetVec3(const std::string& name, const glm::vec3& value);
		void SetVec4(const std::string& name, const glm::vec4& value);

		void SetMat2(const std::string& name, const glm::mat2& value);
		void SetMat3(const std::string& name, const glm::mat3& value);
		void SetMat4(const std::string& name, const glm::mat4& value);

		GLuint GetID();

		bool HasFakeUser();

		static void Unbind();
	};
}