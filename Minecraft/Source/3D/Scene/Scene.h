#pragma once

#include "3D/Scene/Camera.h"
#include "3D/Object/Object3D.h"

#include <memory>
#include <vector>
#include <string>

namespace MC {
	class Scene {
	private:
		std::vector<std::unique_ptr<Object3D>> m_Object3Ds;
		std::vector<std::unique_ptr<Camera>> m_Cameras;
		int m_CurrentCamera;

		bool m_ShouldRecalculateGeometryNumbers;
		int m_NumberOfVertices;
		int m_NumberOfIndices;
	public:
		Scene();
		~Scene();

		void Draw();

		void AddObject3D(const std::string& meshPath, const std::string& shaderPath, const std::string& texturePath);
		void AddCamera();

		void RemoveObject3D(int index);
		void RemoveCamera(int index);
		void RemoveFirstObject3D();
		void RemoveFirstCamera();
		void RemoveLastObject3D();
		void RemoveLastCamera();

		Object3D& GetLastObject3D();
		Camera& GetLastCamera();

		std::vector<std::unique_ptr<Object3D>>& GetObject3Ds();
		std::vector<std::unique_ptr<Camera>>& GetCameras();

		Object3D& GetObject3D(int index);
		Camera& GetCamera(int index);

		Camera& GetCurrentCamera();
		void SetCurrentCamera(int currentCamera);

		int GetNumberOfObject3Ds();
		int GetNumberOfCameras();

		int GetNumberOfVertices();
		int GetNumberOfIndices();
	};
}