#include "Object3D.h"
#include "Global.h"
#include "Console.h"

#include "Vendor/glm/gtc/matrix_transform.hpp"
#include "Vendor/glm/gtx/euler_angles.hpp"

MC::Object3D::Object3D(const std::string& meshPath, const std::string& shaderPath, const std::string& texturePath)
	: m_Mesh(Global::GetMesh3DManager().GetMesh(meshPath)), m_Shader(Global::GetShaderManager().GetShader(shaderPath)), m_Texture(Global::GetTextureManager().GetTexture(texturePath)), m_Translation(0.0f), m_Rotation(0.0f), m_Scale(1.0f)
{

}

MC::Object3D::~Object3D()
{
	Global::GetMesh3DManager().MarkForCleanup();
	Global::GetShaderManager().MarkForCleanup();
	Global::GetTextureManager().MarkForCleanup();
}

const glm::vec3& MC::Object3D::GetTranslation()
{
	return m_Translation;
}

const glm::vec3& MC::Object3D::GetRotation()
{
	return m_Rotation;
}

const glm::vec3& MC::Object3D::GetScale()
{
	return m_Scale;
}

const std::shared_ptr<MC::Mesh3D>& MC::Object3D::GetMesh()
{
	return m_Mesh;
}

const std::shared_ptr<MC::Shader>& MC::Object3D::GetShader()
{
	return m_Shader;
}

const std::shared_ptr<MC::Texture>& MC::Object3D::GetTexture()
{
	return m_Texture;
}

void MC::Object3D::SetTranslation(const glm::vec3& translation)
{
	m_Translation = translation;
}

void MC::Object3D::SetRotation(const glm::vec3& rotation)
{
	m_Rotation = rotation;
}

void MC::Object3D::SetScale(const glm::vec3& scale)
{
	m_Scale = scale;
}

void MC::Object3D::AddTranslation(const glm::vec3& translation)
{
	m_Translation += translation;
}

void MC::Object3D::AddRotation(const glm::vec3& rotation)
{
	m_Rotation += rotation;
}

void MC::Object3D::AddScale(const glm::vec3& scale)
{
	m_Scale += scale;
}

glm::mat4 MC::Object3D::GetTransformationMatrix()
{
	return glm::translate(glm::mat4(1.0f), m_Translation) * glm::yawPitchRoll(glm::radians(m_Rotation.x), glm::radians(m_Rotation.y), glm::radians(m_Rotation.z)) * glm::scale(glm::mat4(1.0f), m_Scale);
}

void MC::Object3D::Bind()
{
	m_Shader->Bind();
	m_Texture->Bind();
	m_Mesh->Bind();
}

void MC::Object3D::Draw(const glm::mat4& projection, const glm::mat4& view, const glm::mat4& modelOffset)
{
	Bind();
	m_Shader->SetMat4("P", projection);
	m_Shader->SetMat4("V", view);
	m_Shader->SetMat4("M", modelOffset * GetTransformationMatrix());
	m_Mesh->Draw();
}
