#include "MeshAnimatedObject3D.h"
#include "Global.h"
#include "Console.h"

MC::MeshAnimatedObject3D::MeshAnimatedObject3D(const std::string& meshPath, const std::string& shaderPath, const std::string& texturePath, int numberOfFrames)
	: Object3D(MeshAnimatedObject3D::GetPrefix(MeshAnimatedObject3D::GetPath(MeshAnimatedObject3D::GetPrefix(meshPath), MeshAnimatedObject3D::GetSuffix(meshPath), std::to_string(0))) + MeshAnimatedObject3D::GetSuffix(meshPath), shaderPath, texturePath), m_CurrentFrame(0), m_NumberOfFrames(numberOfFrames), m_Timer(24), m_Prefix(MeshAnimatedObject3D::GetPrefix(meshPath)), m_Suffix(MeshAnimatedObject3D::GetSuffix(meshPath))
{
	Global::GetMesh3DManager().GetMesh(MeshAnimatedObject3D::GetPath(m_Prefix, m_Suffix, std::to_string(0)))->SetHasFakeUser(true);
	for (int i = 1; i < m_NumberOfFrames; i++) {
		Global::GetMesh3DManager().GetMesh(MeshAnimatedObject3D::GetPath(m_Prefix, m_Suffix, std::to_string(i)))->SetHasFakeUser(true);
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
	Console::Info("Updating animation");
	m_Timer.Update(deltaTime);
	if (m_Timer.IsFinished()) {
		Console::Info("Timer finished advancing animation");
		m_CurrentFrame += 1;
		if (m_CurrentFrame == m_NumberOfFrames) {
			m_CurrentFrame = 0;
		}
		m_Mesh = Global::GetMesh3DManager().GetMesh(MeshAnimatedObject3D::GetPath(m_Prefix, m_Suffix, std::to_string(m_CurrentFrame)));
		m_Timer.Reset();
	}
}

std::string MC::MeshAnimatedObject3D::GetPath(const std::string& prefix, const std::string& suffix, const std::string& currentFrameString)
{
	return prefix + std::string("_") + std::string(6 - currentFrameString.length(), '0') + currentFrameString + suffix;
}

std::string MC::MeshAnimatedObject3D::GetPrefix(const std::string& path)
{
	return path.substr(0, path.find('.'));
}

std::string MC::MeshAnimatedObject3D::GetSuffix(const std::string& path)
{
	return path.substr(path.find('.'));
}
