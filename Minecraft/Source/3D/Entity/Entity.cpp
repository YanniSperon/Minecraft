#include "Entity.h"
#include "Console.h"

MC::Entity::Entity(const std::string& meshPath, const std::string& shaderPath, const std::string& texturePath, int numberOfFrames, const glm::vec3& hitboxMin, const glm::vec3& hitboxMax)
	: MeshAnimatedObject3D(meshPath, shaderPath, texturePath, numberOfFrames), m_HitboxMax(hitboxMax), m_HitboxMin(hitboxMin), m_Velocity(0.0f), m_Gravity(-9.80665), m_IsAnimating(false)
{
}

MC::Entity::~Entity()
{
}

void MC::Entity::Update(float deltaTime)
{
	if (m_IsAnimating) {
		Console::Info("Animating");
		MeshAnimatedObject3D::Update(deltaTime);
	}
	m_Translation.x += m_Velocity.x * deltaTime;
	m_Translation.y += m_Velocity.y * deltaTime + 0.5f * m_Gravity * deltaTime * deltaTime;
	m_Translation.z += m_Velocity.z * deltaTime;

	m_Velocity.y += m_Gravity * deltaTime;
}

void MC::Entity::SetVelocity(glm::vec3 velocity)
{
	m_Velocity = velocity;
}

void MC::Entity::SetGravity(float gravity)
{
	m_Gravity = gravity;
}

void MC::Entity::SetIsAnimating(bool isAnimating)
{
	m_IsAnimating = isAnimating;
}

bool MC::Entity::IsInside(const glm::vec3& translation, const glm::vec3& hitboxMin, const glm::vec3& hitboxMax)
{
	if (m_HitboxMin.x + m_Translation.x < hitboxMax.x + translation.x &&
		m_HitboxMax.x + m_Translation.x > hitboxMin.x + translation.x &&
		m_HitboxMin.y + m_Translation.y < hitboxMax.y + translation.y &&
		m_HitboxMax.y + m_Translation.y > hitboxMin.y + translation.y &&
		m_HitboxMin.z + m_Translation.z < hitboxMax.z + translation.z &&
		m_HitboxMax.z + m_Translation.z > hitboxMin.z + translation.z) {
		return true;
	}
	else {
		return false;
	}

}
