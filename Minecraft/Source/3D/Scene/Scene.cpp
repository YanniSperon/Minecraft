#include "Scene.h"
#include "Console.h"

MC::Scene::Scene()
	: m_Chunks(), m_Cameras(), m_CurrentCamera(0), m_ShouldRecalculateGeometryNumbers(false), m_NumberOfVertices(0), m_NumberOfIndices(0)
{
	m_Cameras.push_back(std::make_unique<Camera>());
}

MC::Scene::~Scene()
{
}

void MC::Scene::Draw()
{
	Camera& currentCamera = GetCurrentCamera();
	glm::mat4 projection = currentCamera.GetProjectionMatrix();
	glm::vec3 eyeHeight = currentCamera.GetTranslation();
	glm::mat4 view = currentCamera.GetViewMatrix();
	glm::mat4 offset = glm::mat4(1.0f);
	currentCamera.DrawSkybox(projection, view, offset);
	for (int i = 0; i < m_Chunks.size(); i++) {
		m_Chunks[i]->Draw(projection, view, offset, eyeHeight);
	}
	for (int i = 0; i < m_Entities.size(); i++) {
		m_Entities[i]->Draw(projection, view, offset);
	}
	Shader::Unbind();
}

void MC::Scene::Update(float deltaTime)
{
	for (int i = 0; i < m_Entities.size(); i++) {
		m_Entities[i]->Update(deltaTime);
	}
}

void MC::Scene::AddChunk(const glm::ivec3& position)
{
	m_Chunks.push_back(std::make_unique<Chunk>(position));
	m_ShouldRecalculateGeometryNumbers = true;
}

void MC::Scene::AddCamera()
{
	m_Cameras.push_back(std::make_unique<Camera>());
}

void MC::Scene::AddEntity(const std::string& meshPath, const std::string& shaderPath, const std::string& texturePath, int numberOfFrames, const glm::vec3& hitboxMin, const glm::vec3& hitboxMax, const glm::vec3& terminalVelocity)
{
	m_Entities.push_back(std::make_unique<Entity>(meshPath, shaderPath, texturePath, numberOfFrames, hitboxMin, hitboxMax, terminalVelocity));
	m_ShouldRecalculateGeometryNumbers = true;
}

void MC::Scene::RemoveChunk(int index)
{
	if (m_Chunks.size() < index && index > 0) {
		m_Chunks.erase(m_Chunks.begin() + index);
		m_ShouldRecalculateGeometryNumbers = true;
	}
}

void MC::Scene::RemoveCamera(int index)
{
	if (m_Cameras.size() > 1 && m_Cameras.size() < index && index > 0) {
		m_Cameras.erase(m_Cameras.begin() + index);
		if (m_CurrentCamera == index) {
			if (index <= 1) {
				m_CurrentCamera = 0;
			}
			else {
				m_CurrentCamera = index - 1;
			}
		}
		else {
			m_CurrentCamera -= 1;
		}
	}
}

void MC::Scene::RemoveFirstChunk()
{
	if (m_Chunks.size() > 0) {
		m_Chunks.erase(m_Chunks.begin());
		m_ShouldRecalculateGeometryNumbers = true;
	}
}

void MC::Scene::RemoveFirstCamera()
{
	if (m_Cameras.size() > 1) {
		m_Cameras.erase(m_Cameras.begin());
		m_CurrentCamera = 0;
	}
}

void MC::Scene::RemoveLastChunk()
{
	if (m_Chunks.size() > 0) {
		m_Chunks.pop_back();
		m_ShouldRecalculateGeometryNumbers = true;
	}
}

void MC::Scene::RemoveLastCamera()
{
	if (m_Cameras.size() > 1) {
		m_Cameras.pop_back();
		if (!(m_CurrentCamera < m_Cameras.size())) {
			m_CurrentCamera = m_Cameras.size() - 1;
		}
	}
}

// Only use this when you are certain the scene has at least one object
MC::Chunk& MC::Scene::GetLastChunk()
{
	return *m_Chunks.back();
}

MC::Camera& MC::Scene::GetLastCamera()
{
	return *m_Cameras.back();
}

MC::Entity& MC::Scene::GetLastEntity()
{
	return *m_Entities.back();
}

std::vector<std::unique_ptr<MC::Chunk>>& MC::Scene::GetChunks()
{
	return m_Chunks;
}

std::vector<std::unique_ptr<MC::Camera>>& MC::Scene::GetCameras()
{
	return m_Cameras;
}

std::vector<std::unique_ptr<MC::Entity>>& MC::Scene::GetEntity()
{
	return m_Entities;
}

// Only use this when you are certain the index is valid
MC::Chunk& MC::Scene::GetChunk(int index)
{
	return *m_Chunks[index];
}

// Only use this when you are certain the index is valid
MC::Camera& MC::Scene::GetCamera(int index)
{
	return *m_Cameras[index];
}

MC::Entity& MC::Scene::GetEntity(int index)
{
	return *m_Entities[index];
}

MC::Chunk* MC::Scene::GetChunkAt(const glm::ivec3& position)
{
	for (int i = 0; i < m_Chunks.size(); i++) {
		if (m_Chunks[i]->GetPosition() == position) {
			return m_Chunks[i].get();
		}
	}
	return nullptr;
}

MC::Chunk* MC::Scene::GetChunkAt(int x, int y, int z)
{
	for (int i = 0; i < m_Chunks.size(); i++) {
		if (m_Chunks[i]->GetPosition() == glm::ivec3(x, y, z)) {
			return m_Chunks[i].get();
		}
	}
	return nullptr;
}

MC::Camera& MC::Scene::GetCurrentCamera()
{
	return *m_Cameras[m_CurrentCamera];
}

void MC::Scene::SetCurrentCamera(int currentCamera)
{
	if (currentCamera >= 0 && currentCamera < m_Cameras.size()) {
		m_CurrentCamera = currentCamera;
	}
}

//int MC::Scene::GetNumberOfObject3Ds()
//{
//	return m_Object3Ds.size();
//}
//
//int MC::Scene::GetNumberOfCameras()
//{
//	return m_Cameras.size();
//}
//
//int MC::Scene::GetNumberOfVertices()
//{
//	if (m_ShouldRecalculateGeometryNumbers) {
//		m_NumberOfVertices = 0;
//		m_NumberOfIndices = 0;
//		for (int i = 0; i < m_Object3Ds.size(); i++) {
//			m_NumberOfVertices += m_Object3Ds[i]->GetMesh().GetNumVertices();
//			m_NumberOfIndices += m_Object3Ds[i]->GetMesh().GetNumIndices();
//		}
//		m_ShouldRecalculateGeometryNumbers = false;
//	}
//	return m_NumberOfVertices;
//}
//
//int MC::Scene::GetNumberOfIndices()
//{
//	if (m_ShouldRecalculateGeometryNumbers) {
//		m_NumberOfVertices = 0;
//		m_NumberOfIndices = 0;
//		for (int i = 0; i < m_Object3Ds.size(); i++) {
//			m_NumberOfVertices += m_Object3Ds[i]->GetMesh().GetNumVertices();
//			m_NumberOfIndices += m_Object3Ds[i]->GetMesh().GetNumIndices();
//		}
//		m_ShouldRecalculateGeometryNumbers = false;
//	}
//	return m_NumberOfIndices;
//}
