#include "Chunk.h"

MC::Chunk::Chunk(const glm::ivec3& chunkPosition)
	: m_Blocks(), m_ChunkPosition(chunkPosition)
{
	m_Blocks.resize(16);
	for (int x = 0; x < 16; x++) {
		m_Blocks[x].resize(64);
		for (int y = 0; y < 64; y++) {
			m_Blocks[x][y].resize(16);
			for (int z = 0; z < 16; z++) {
				m_Blocks[x][y][z] = std::make_unique<Block>();
				m_Blocks[x][y][z]->PlaceInChunk(chunkPosition, glm::ivec3(x, y, z));
			}
		}
	}
}

MC::Chunk::~Chunk()
{

}

void MC::Chunk::Draw(const glm::mat4& projection, const glm::mat4& view, const glm::mat4& offset)
{
	for (int x = 0; x < 16; x++) {
		for (int y = 0; y < 64; y++) {
			for (int z = 0; z < 16; z++) {
				if ((x == 0 || x == 15) || (y == 0 || y == 63) || (z == 0 || z == 15)) {
					m_Blocks[x][y][z]->Draw(projection, view, offset);

				}
				else {
					if (m_Blocks[x + 1][y][z]->IsTransparent() || 
						m_Blocks[x][y + 1][z]->IsTransparent() ||
						m_Blocks[x][y][z + 1]->IsTransparent() ||
						m_Blocks[x - 1][y][z]->IsTransparent() ||
						m_Blocks[x][y - 1][z]->IsTransparent() ||
						m_Blocks[x][y][z - 1]->IsTransparent()) {
						m_Blocks[x][y][z]->Draw(projection, view, offset);
					}
				}
				//if (m_Blocks[x][y][z]->GetMaterial() != Material::Air) {
				//}
			}
		}
	}
}

MC::Block& MC::Chunk::GetBlock(int x, int y, int z)
{
	return *m_Blocks[x][y][z];
}
