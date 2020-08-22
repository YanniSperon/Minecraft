#include "Scene.h"

MC::Scene::Scene()
	: m_CurrentCamera(0), m_ShouldRecalculateGeometryNumbers(false), m_NumberOfVertices(0), m_NumberOfIndices(0)
{
	m_Object3Ds = std::vector<std::unique_ptr<Object3D>>();
	m_Cameras = std::vector<std::unique_ptr<Camera>>();
	m_Cameras.push_back(std::make_unique<Camera>());
}

MC::Scene::~Scene()
{
	m_Object3Ds.clear();
	m_Cameras.clear();
}

void MC::Scene::Draw()
{
	Camera& currentCamera = GetCurrentCamera();
	glm::mat4 projection = currentCamera.GetProjectionMatrix();
	glm::mat4 view = currentCamera.GetViewMatrix();
	glm::mat4 offset = glm::mat4(1.0f);
	for (int i = 0; i < m_Object3Ds.size(); i++) {
		m_Object3Ds[i]->Draw(projection, view, offset);
	}
}

void MC::Scene::AddObject3D(const std::string& meshPath, const std::string& shaderPath, const std::string& texturePath)
{
	m_Object3Ds.push_back(std::move(std::make_unique<Object3D>(meshPath, shaderPath, texturePath)));
	m_ShouldRecalculateGeometryNumbers = true;
}

void MC::Scene::AddCamera()
{
	m_Cameras.push_back(std::move(std::make_unique<Camera>()));
}

void MC::Scene::RemoveObject3D(int index)
{
	if (m_Object3Ds.size() < index && index > 0) {
		m_Object3Ds.erase(m_Object3Ds.begin() + index);
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

void MC::Scene::RemoveFirstObject3D()
{
	if (m_Object3Ds.size() > 0) {
		m_Object3Ds.erase(m_Object3Ds.begin());
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

void MC::Scene::RemoveLastObject3D()
{
	if (m_Object3Ds.size() > 0) {
		m_Object3Ds.pop_back();
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
MC::Object3D& MC::Scene::GetLastObject3D()
{
	return *m_Object3Ds.back();
}

MC::Camera& MC::Scene::GetLastCamera()
{
	return *m_Cameras.back();
}

std::vector<std::unique_ptr<MC::Object3D>>& MC::Scene::GetObject3Ds()
{
	return m_Object3Ds;
}

std::vector<std::unique_ptr<MC::Camera>>& MC::Scene::GetCameras()
{
	return m_Cameras;
}

// Only use this when you are certain the index is valid
MC::Object3D& MC::Scene::GetObject3D(int index)
{
	return *m_Object3Ds[index];
}

// Only use this when you are certain the index is valid
MC::Camera& MC::Scene::GetCamera(int index)
{
	return *m_Cameras[index];
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

int MC::Scene::GetNumberOfObject3Ds()
{
	return m_Object3Ds.size();
}

int MC::Scene::GetNumberOfCameras()
{
	return m_Cameras.size();
}

int MC::Scene::GetNumberOfVertices()
{
	if (m_ShouldRecalculateGeometryNumbers) {
		m_NumberOfVertices = 0;
		m_NumberOfIndices = 0;
		for (int i = 0; i < m_Object3Ds.size(); i++) {
			m_NumberOfVertices += m_Object3Ds[i]->GetMesh().GetNumVertices();
			m_NumberOfIndices += m_Object3Ds[i]->GetMesh().GetNumIndices();
		}
		m_ShouldRecalculateGeometryNumbers = false;
	}
	return m_NumberOfVertices;
}

int MC::Scene::GetNumberOfIndices()
{
	if (m_ShouldRecalculateGeometryNumbers) {
		m_NumberOfVertices = 0;
		m_NumberOfIndices = 0;
		for (int i = 0; i < m_Object3Ds.size(); i++) {
			m_NumberOfVertices += m_Object3Ds[i]->GetMesh().GetNumVertices();
			m_NumberOfIndices += m_Object3Ds[i]->GetMesh().GetNumIndices();
		}
		m_ShouldRecalculateGeometryNumbers = false;
	}
	return m_NumberOfIndices;
}
