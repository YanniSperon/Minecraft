#pragma once

#include "3D/Object/Object3D.h"

#include <string>
#include <memory>

#include "Vendor/glm/glm.hpp"

namespace MC {
	enum class Material {
		Air, Dirt
	};

	class Block {
	private:
		Material m_Material;
		std::unique_ptr<Object3D> m_Object3D;

		glm::ivec3 m_Chunk;
		glm::ivec3 m_SpotInChunk;

		void SetObject3D(const std::string& meshPath, const std::string& shaderPath, const std::string& texturePath);
	public:
		Block();

		void SetMaterial(Material material);
		void SetPosition(const glm::vec3& translation);

		bool IsTransparent();

		Material GetMaterial();

		void PlaceInChunk(const glm::ivec3& chunk, const glm::ivec3 spotInChunk);

		void Draw(const glm::mat4& projection, const glm::mat4& view, const glm::mat4& offset);
	};
}