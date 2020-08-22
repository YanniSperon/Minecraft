#pragma once

#include "3D/Mesh/Mesh3D.h"
#include "3D/Texture/Texture.h"
#include "3D/Shader/Shader.h"

#include <memory>

#include "Vendor/glm/glm.hpp"

namespace MC {
	class Object3D {
	private:
		std::shared_ptr<Mesh3D> m_Mesh;
		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<Texture> m_Texture;

		glm::vec3 m_Translation;
		glm::vec3 m_Rotation;
		glm::vec3 m_Scale;
	public:
		Object3D(const std::string& meshPath, const std::string& shaderPath, const std::string& texturePath);
		~Object3D();

		const glm::vec3& GetTranslation();
		const glm::vec3& GetRotation();
		const glm::vec3& GetScale();

		Mesh3D& GetMesh();
		Shader& GetShader();
		Texture& GetTexture();

		void SetTranslation(const glm::vec3& translation);
		void SetRotation(const glm::vec3& rotation);
		void SetScale(const glm::vec3& scale);

		void AddTranslation(const glm::vec3& translation);
		void AddRotation(const glm::vec3& rotation);
		void AddScale(const glm::vec3& scale);

		glm::mat4 GetTransformationMatrix();

		void Bind();

		void Draw(const glm::mat4& projection, const glm::mat4& view, const glm::mat4& modelOffset);
	};
}