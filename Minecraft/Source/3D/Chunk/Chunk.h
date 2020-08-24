#pragma once

#include "3D/Chunk/Block.h"

#include <glew.h>

#include <string>
#include <vector>
#include <memory>

#include "Vendor/glm/glm.hpp"


namespace MC {
	class Chunk {
	private:
		//std::vector<std::vector<std::vector<std::unique_ptr<Block>>>> m_Blocks;

		Block* m_Blocks;

		glm::ivec3 m_ChunkPosition;
	public:
		Chunk(const glm::ivec3& chunkPosition);
		~Chunk();

		void Draw(const glm::mat4& projection, const glm::mat4& view, const glm::mat4& offset, const glm::vec3& eyeHeight);

		//Block& GetBlock(int x, int y, int z);

		const glm::ivec3& GetPosition();

		Block* GetBlock(int x, int y, int z);
		//void SetBlock(int x, int y, int z, Block& block);
	};
}