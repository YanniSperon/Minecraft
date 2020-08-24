#include "Entity.h"
#include "Console.h"

MC::Entity::Entity(const std::string& meshPath, const std::string& shaderPath, const std::string& texturePath, int numberOfFrames, const glm::vec3& hitboxMin, const glm::vec3& hitboxMax, const glm::vec3& terminalVelocity)
	: MeshAnimatedObject3D(meshPath, shaderPath, texturePath, numberOfFrames), m_HitboxMax(hitboxMax), m_HitboxMin(hitboxMin), m_Velocity(0.0f), m_Gravity(-9.80665), m_IsAnimating(false), m_TerminalVelocity(terminalVelocity), m_StepHeight(0.6f)
{
}

MC::Entity::~Entity()
{
}

void MC::Entity::Update(float deltaTime)
{
	if (m_IsAnimating) {
		MeshAnimatedObject3D::Update(deltaTime);
	}
	m_Translation.x += m_Velocity.x * deltaTime;
	m_Translation.y += m_Velocity.y * deltaTime + 0.5f * m_Gravity * deltaTime * deltaTime;
	m_Translation.z += m_Velocity.z * deltaTime;

	m_Velocity.y += m_Gravity * deltaTime;

	glm::vec3 absVel = glm::abs(m_Velocity);

	if (absVel.x > m_TerminalVelocity.x) {
		m_Velocity.x = (m_Velocity.x / absVel.x) * m_TerminalVelocity.x;
	}
	if (absVel.y > m_TerminalVelocity.y) {
		m_Velocity.y = (m_Velocity.y / absVel.y) * m_TerminalVelocity.y;
	}
	if (absVel.z > m_TerminalVelocity.z) {
		m_Velocity.z = (m_Velocity.z / absVel.z) * m_TerminalVelocity.z;
	}
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

const glm::vec3& MC::Entity::GetHitboxMin()
{
	return m_HitboxMin;
}

const glm::vec3& MC::Entity::GetHitboxMax()
{
	return m_HitboxMax;
}

const glm::vec3& MC::Entity::GetHalfWidth()
{
	return (glm::abs(m_HitboxMin) + glm::abs(m_HitboxMax)) / 2.0f;
}

const glm::vec3& MC::Entity::GetHitboxCenterWithTranslation()
{
	return ((m_HitboxMin + m_HitboxMax) / 2.0f) + m_Translation;
}

const glm::vec3& MC::Entity::GetVelocity()
{
	return m_Velocity;
}

const glm::vec3& MC::Entity::GetTerminalVelocity()
{
	return m_TerminalVelocity;
}

float MC::Entity::GetGravity()
{
	return m_Gravity;
}

bool MC::Entity::GetIsAnimating()
{
	return m_IsAnimating;
}

void MC::Entity::ResolveCollision(Entity* first, Entity* second)
{
	// boxs for both entities
	// (-1, -1, -1) min
	// (1 , 1, 1) max
	// first entity position = (-0.5, 0.25, 1.1)
	// second entity position = (-1, 0.9, 0.8)
	// half width first = (1, 1, 1)
	// half width second = (1, 1, 1)

	// distance between centers = (-0.5, 0.65, -0.3)
	glm::vec3 distanceBetweenCenters = second->GetHitboxCenterWithTranslation() - first->GetHitboxCenterWithTranslation();
	// minimum colliding distance = (2, 2, 2)
	glm::vec3 minimumCollidingDistance = first->GetHalfWidth() + second->GetHalfWidth();

	// distance between centers abs = (0.5, 0.65, 0.3)
	// minimum colliding distance (2, 2, 2)
	if (fabsf(distanceBetweenCenters.x) >= minimumCollidingDistance.x ||
		fabsf(distanceBetweenCenters.y) >= minimumCollidingDistance.y ||
		fabsf(distanceBetweenCenters.z) >= minimumCollidingDistance.z) {
		// Not colliding
	}
	else {
		glm::vec3 penetration = glm::vec3(0.0f);
		// distance between centers = (-0.5, 0.65, -0.3)
		// minimum colliding distance = (2, 2, 2)
		if (distanceBetweenCenters.x > 0.0f) {
			penetration.x = minimumCollidingDistance.x - distanceBetweenCenters.x;
		}
		else {
			penetration.x = -minimumCollidingDistance.x - distanceBetweenCenters.x;
		}

		if (distanceBetweenCenters.y > 0.0f) {
			penetration.y = minimumCollidingDistance.y - distanceBetweenCenters.y;
		}
		else {
			penetration.y = -minimumCollidingDistance.y - distanceBetweenCenters.y;
		}

		if (distanceBetweenCenters.z > 0.0f) {
			penetration.z = minimumCollidingDistance.z - distanceBetweenCenters.z;
		}
		else {
			penetration.z = -minimumCollidingDistance.z - distanceBetweenCenters.z;
		}
		// penetration = (2.5, 1.35, 1.7)
		////glm::vec3 penetration = minimumCollidingDistance - distanceBetweenCenters;
	}
}
