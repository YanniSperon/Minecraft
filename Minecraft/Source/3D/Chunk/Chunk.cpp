#include "Chunk.h"
#include "Global.h"
#include "Console.h"
#include "3D/Scene/Scene.h"

MC::Chunk::Chunk(const glm::ivec3& chunkPosition)
	: m_ChunkPosition(chunkPosition), m_Blocks(new Block[16 * 256 * 16]())
{
	for (int x = 0; x < 16; x++) {
		for (int y = 0; y < 256; y++) {
			for (int z = 0; z < 16; z++) {
				GetBlock(x, y, z)->PlaceInChunk(chunkPosition, glm::ivec3(x, y, z));
			}
		}
	}
}

MC::Chunk::~Chunk()
{
	delete[] m_Blocks;
}

void MC::Chunk::Draw(const glm::mat4& projection, const glm::mat4& view, const glm::mat4& offset, const glm::vec3& eyeHeight)
{
	Scene& currentScene = Global::GetWindow().GetCurrentScene();
	Chunk* chunkToPosX = currentScene.GetChunkAt(m_ChunkPosition.x + 1, m_ChunkPosition.y, m_ChunkPosition.z);
	Chunk* chunkToNegX = currentScene.GetChunkAt(m_ChunkPosition.x - 1, m_ChunkPosition.y, m_ChunkPosition.z);
	Chunk* chunkToPosZ = currentScene.GetChunkAt(m_ChunkPosition.x, m_ChunkPosition.y, m_ChunkPosition.z + 1);
	Chunk* chunkToNegZ = currentScene.GetChunkAt(m_ChunkPosition.x, m_ChunkPosition.y, m_ChunkPosition.z - 1);
	bool isVisible = false;
	for (int x = 0; x < 16; x++) {
		for (int y = 0; y < 256; y++) {
			for (int z = 0; z < 16; z++) {
				if (!GetBlock(x, y, z)->IsTransparent()) {
					if (x == 0) {
						if ((chunkToNegX != nullptr && chunkToNegX->GetBlock(15, y, z)->IsTransparent()) || GetBlock(x + 1, y, z)->IsTransparent()) {
							isVisible = true;
						}
					}
					else if (x == 15) {
						if ((chunkToPosX != nullptr && chunkToPosX->GetBlock(0, y, z)->IsTransparent()) || GetBlock(x - 1, y, z)->IsTransparent()) {
							isVisible = true;
						}
					}
					else if (GetBlock(x + 1, y, z)->IsTransparent() || GetBlock(x - 1, y, z)->IsTransparent()) {
						isVisible = true;
					}

					if (z == 0) {
						if ((chunkToNegZ != nullptr && chunkToNegZ->GetBlock(x, y, 15)->IsTransparent()) || GetBlock(x, y, z + 1)->IsTransparent()) {
							isVisible = true;
						}
					}
					else if (z == 15) {
						if ((chunkToPosZ != nullptr && chunkToPosZ->GetBlock(x, y, 0)->IsTransparent()) || GetBlock(x, y, z - 1)->IsTransparent()) {
							isVisible = true;
						}
					}
					else if (GetBlock(x, y, z + 1)->IsTransparent() || GetBlock(x, y, z - 1)->IsTransparent()) {
						isVisible = true;
					}

					if (y == 0) {
						if (GetBlock(x, y + 1, z)->IsTransparent()) {
							isVisible = true;
						}
						else if (eyeHeight.y < 1.0f) {
							isVisible = true;
						}
					}
					else if (y == 255) {
						if (eyeHeight.y > (float)y - 1.0f) {
							isVisible = true;
						}
						else if (GetBlock(x, y - 1, z)->IsTransparent()) {
							isVisible = true;
						}
					}
					else if (GetBlock(x, y + 1, z)->IsTransparent()) {
						if (GetBlock(x, y - 1, z)->IsTransparent()) {
							isVisible = true;
						}
						else if (eyeHeight.y > (float)y - 1.0f) {
							isVisible = true;
						}
					}
					else if (GetBlock(x, y - 1, z)->IsTransparent() && eyeHeight.y < (float)y + 1.0f) {
						isVisible = true;
					}

					if (isVisible) {
						GetBlock(x, y, z)->Draw(projection, view, offset);
					}
					isVisible = false;
				}
			}
		}
	}
}

const glm::ivec3& MC::Chunk::GetPosition()
{
	return m_ChunkPosition;
}

MC::Block* MC::Chunk::GetBlock(int x, int y, int z)
{
	return m_Blocks + x*256*16 + 16*y + z;
}
