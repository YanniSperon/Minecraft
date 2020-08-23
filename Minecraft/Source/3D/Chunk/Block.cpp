#include "Block.h"

MC::Block::Block()
	: m_Material(Material::Air), m_Object3D(nullptr), m_Chunk(), m_SpotInChunk()
{
}

void MC::Block::SetMaterial(Material material)
{
	m_Material = material;
	switch (m_Material)
	{
	case MC::Material::Air:
		m_Object3D = nullptr;
		break;
	case MC::Material::Dirt:
		SetObject3D("Resources/Block.obj", "Resources/Basic", "Resources/Dirt.png");
		break;
	default:
		break;
	}
}

void MC::Block::SetPosition(const glm::vec3& translation)
{
	if (m_Object3D) {
		m_Object3D->SetTranslation(translation);
	}
}

bool MC::Block::IsTransparent()
{
	if (m_Material == Material::Air) {
		return true;
	}
	return false;
}

MC::Material MC::Block::GetMaterial()
{
	return m_Material;
}

void MC::Block::PlaceInChunk(const glm::ivec3& chunk, const glm::ivec3 spotInChunk)
{
	m_Chunk = chunk;
	m_SpotInChunk = spotInChunk;
	SetPosition(m_Chunk * 16 + m_SpotInChunk);
}

void MC::Block::SetObject3D(const std::string& meshPath, const std::string& shaderPath, const std::string& texturePath)
{
	m_Object3D = std::make_unique<Object3D>(meshPath, shaderPath, texturePath);
	m_Object3D->SetTranslation(m_Chunk * 16 + m_SpotInChunk);
}

void MC::Block::Draw(const glm::mat4& projection, const glm::mat4& view, const glm::mat4& offset)
{
	if (m_Object3D != nullptr) {
		m_Object3D->Draw(projection, view, offset);
	}
}
