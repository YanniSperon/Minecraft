#include "MeshAnimatedObject3D.h"
#include "Global.h"

MC::MeshAnimatedObject3D::MeshAnimatedObject3D(const std::string& meshPath, const std::string& shaderPath, const std::string& texturePath, int numberOfFrames)
	: Object3D(MeshAnimatedObject3D::GetPrefix(meshPath) + std::to_string(0) + MeshAnimatedObject3D::GetSuffix(meshPath), shaderPath, texturePath), m_CurrentFrame(0), m_NumberOfFrames(numberOfFrames), m_Timer(24), m_Prefix(MeshAnimatedObject3D::GetPrefix(meshPath)), m_Suffix(MeshAnimatedObject3D::GetSuffix(meshPath))
{
	Global::GetMesh3DManager().GetMesh(m_Prefix + std::to_string(0) + m_Suffix)->SetHasFakeUser(true);
	for (int i = 1; i < m_NumberOfFrames; i++) {
		Global::GetMesh3DManager().GetMesh(m_Prefix + std::to_string(i) + m_Suffix)->SetHasFakeUser(true);
	}
}

MC::MeshAnimatedObject3D::~MeshAnimatedObject3D()
{
	//for (int i = 0; i < m_NumberOfFrames; i++) {
	//	Global::GetMesh3DManager().GetMesh(m_Mesh->GetPath() + std::to_string(i))->SetHasFakeUser(false);
	//}
}

void MC::MeshAnimatedObject3D::Update(float deltaTime)
{
	m_Timer.Update(deltaTime);
	if (m_Timer.IsFinished()) {
		m_CurrentFrame += 1;
		if (m_CurrentFrame == m_NumberOfFrames) {
			m_CurrentFrame = 0;
		}
		m_Mesh = Global::GetMesh3DManager().GetMesh(m_Prefix + std::to_string(m_CurrentFrame) + m_Suffix);
		m_Timer.Reset();
	}
}

std::string MC::MeshAnimatedObject3D::GetPrefix(const std::string& path)
{
	return path.substr(0, path.find('.'));
}

std::string MC::MeshAnimatedObject3D::GetSuffix(const std::string& path)
{
	return path.substr(path.find('.'));
}
