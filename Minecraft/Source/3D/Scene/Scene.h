#pragma once

#include "3D/Scene/Camera.h"
#include "3D/Chunk/Chunk.h"

#include <memory>
#include <vector>
#include <string>

namespace MC {
	class Scene {
	private:
		std::vector<std::unique_ptr<Chunk>> m_Chunks;
		std::vector<std::unique_ptr<Camera>> m_Cameras;
		int m_CurrentCamera;

		bool m_ShouldRecalculateGeometryNumbers;
		int m_NumberOfVertices;
		int m_NumberOfIndices;
	public:
		Scene();
		~Scene();

		void Draw();

		void AddChunk(const glm::ivec3& position);
		void AddCamera();

		void RemoveChunk(int index);
		void RemoveCamera(int index);
		void RemoveFirstChunk();
		void RemoveFirstCamera();
		void RemoveLastChunk();
		void RemoveLastCamera();

		Chunk& GetLastChunk();
		Camera& GetLastCamera();

		std::vector<std::unique_ptr<Chunk>>& GetChunks();
		std::vector<std::unique_ptr<Camera>>& GetCameras();

		Chunk& GetChunk(int index);
		Camera& GetCamera(int index);

		Camera& GetCurrentCamera();
		void SetCurrentCamera(int currentCamera);

		//int GetNumberOfObject3Ds();
		//int GetNumberOfCameras();
		//
		//int GetNumberOfVertices();
		//int GetNumberOfIndices();
	};
}