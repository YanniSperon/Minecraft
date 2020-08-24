#pragma once

#include "3D/Scene/Camera.h"
#include "3D/Chunk/Chunk.h"
#include "3D/Entity/Entity.h"

#include <memory>
#include <vector>
#include <string>

#include "Vendor/glm/glm.hpp"

namespace MC {
	class Scene {
	private:
		std::vector<std::unique_ptr<Chunk>> m_Chunks;
		std::vector<std::unique_ptr<Camera>> m_Cameras;
		std::vector<std::unique_ptr<Entity>> m_Entities;
		int m_CurrentCamera;

		bool m_ShouldRecalculateGeometryNumbers;
		int m_NumberOfVertices;
		int m_NumberOfIndices;
	public:
		Scene();
		~Scene();

		void Draw();

		void Update(float deltaTime);

		void AddChunk(const glm::ivec3& position);
		void AddCamera();
		void AddEntity(const std::string& meshPath, const std::string& shaderPath, const std::string& texturePath, int numberOfFrames, const glm::vec3& hitboxMin, const glm::vec3& hitboxMax, const glm::vec3& terminalVelocity);

		void RemoveChunk(int index);
		void RemoveCamera(int index);
		void RemoveFirstChunk();
		void RemoveFirstCamera();
		void RemoveLastChunk();
		void RemoveLastCamera();

		Chunk& GetLastChunk();
		Camera& GetLastCamera();
		Entity& GetLastEntity();

		std::vector<std::unique_ptr<Chunk>>& GetChunks();
		std::vector<std::unique_ptr<Camera>>& GetCameras();
		std::vector<std::unique_ptr<Entity>>& GetEntity();

		Chunk& GetChunk(int index);
		Camera& GetCamera(int index);
		Entity& GetEntity(int index);

		Chunk* GetChunkAt(const glm::ivec3& position);
		Chunk* GetChunkAt(int x, int y, int z);

		Camera& GetCurrentCamera();
		void SetCurrentCamera(int currentCamera);

		//int GetNumberOfObject3Ds();
		//int GetNumberOfCameras();
		//
		//int GetNumberOfVertices();
		//int GetNumberOfIndices();
	};
}