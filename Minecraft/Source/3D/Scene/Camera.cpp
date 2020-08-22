#include "Camera.h"
#include "Global.h"
#include "Console.h"

#include "Vendor/glm/gtc/matrix_transform.hpp"
#include "Vendor/glm/gtx/euler_angles.hpp"
#include "Vendor/glm/gtx/rotate_vector.hpp"

MC::Camera::Camera()
	: m_FOV(Global::GetConfig().GetFOV()), m_NearPlane(0.1f), m_FarPlane(100.0f), m_MovementSpeed(5.0f), m_OldMouseX(0.0f), m_OldMouseY(0.0f), m_Translation(0.0f), m_Rotation(-90.0f, 0.0f, 0.0f), m_WasUsedYet(false)
{

}

void MC::Camera::SetFOV(float FOV)
{
	m_FOV = FOV;
}

void MC::Camera::SetNearPlane(float nearPlane)
{
	m_NearPlane = nearPlane;
}

void MC::Camera::SetFarPlane(float farPlane)
{
	m_FarPlane = farPlane;
}

void MC::Camera::SetMovementSpeed(float movementSpeed)
{
	m_MovementSpeed = movementSpeed;
}

void MC::Camera::SetOldMouseX(float x)
{
	m_OldMouseX = x;
}

void MC::Camera::SetOldMouseY(float y)
{
	m_OldMouseY = y;
}

void MC::Camera::SetTranslation(const glm::vec3& translation)
{
	m_Translation = translation;
}

void MC::Camera::SetUpDirection(const glm::vec3& upDirection)
{
	m_Rotation.z = glm::degrees(glm::acos(glm::dot(glm::vec3(0.0f, 1.0f, 0.0f), upDirection)));
}

void MC::Camera::SetWasUsedYet(bool wasUsedYet)
{
	m_WasUsedYet = wasUsedYet;
}

const float MC::Camera::GetFOV()
{
	return m_FOV;
}

const float MC::Camera::GetNearPlane()
{
	return m_NearPlane;
}

const float MC::Camera::GetFarPlane()
{
	return m_FarPlane;
}

const float MC::Camera::GetMovementSpeed()
{
	return m_MovementSpeed;
}

const float MC::Camera::GetOldMouseX()
{
	return m_OldMouseX;
}

const float MC::Camera::GetOldMouseY()
{
	return m_OldMouseY;
}

const glm::vec3& MC::Camera::GetTranslation()
{
	return m_Translation;
}

const glm::vec3& MC::Camera::GetRotation()
{
	return m_Rotation;
}

glm::vec3 MC::Camera::GetUpDirection()
{
	return glm::rotateZ(glm::vec3(0.0f, 1.0f, 0.0f), glm::radians(-m_Rotation.z));
}

const bool MC::Camera::GetWasUsedYet()
{
	return m_WasUsedYet;
}

glm::vec3 MC::Camera::GetForwardDirection()
{
	return glm::normalize(glm::vec3(glm::cos(glm::radians(m_Rotation.x)) * glm::cos(glm::radians(m_Rotation.y)), glm::sin(glm::radians(m_Rotation.y)), glm::sin(glm::radians(m_Rotation.x)) * glm::cos(glm::radians(m_Rotation.y))));
}

glm::mat4 MC::Camera::GetProjectionMatrix()
{
	return glm::perspective(glm::radians(m_FOV), (float)Global::GetWindow().GetWidth() / (float)Global::GetWindow().GetHeight(), m_NearPlane, m_FarPlane);
}

glm::mat4 MC::Camera::GetViewMatrix()
{
	return glm::lookAt(m_Translation, m_Translation + GetForwardDirection(), GetUpDirection());
}

void MC::Camera::LookAt(glm::vec3 position)
{
	glm::vec3 newDirection = glm::normalize(m_Translation - position);

	m_Rotation.x = glm::degrees(atan2(newDirection.z, newDirection.x)) + 180.0f;
	m_Rotation.y = glm::degrees(-glm::asin(newDirection.y));
}

void MC::Camera::LookAtMouse(float sensitivity, float xPos, float yPos)
{
	if (!m_WasUsedYet) {
		m_OldMouseX = xPos;
		m_OldMouseY = yPos;
		m_WasUsedYet = true;
	}
	float xOffset = xPos - m_OldMouseX;
	float yOffset = m_OldMouseY - yPos;
	m_OldMouseX = xPos;
	m_OldMouseY = yPos;
	m_Rotation.x += xOffset * sensitivity;
	m_Rotation.y += yOffset * sensitivity;

	if (m_Rotation.y > 89.0f) {
		m_Rotation.y = 89.0f;
	}
	if (m_Rotation.y < -89.0f) {
		m_Rotation.y = -89.0f;
	}
}

void MC::Camera::MoveForward(float deltaTime)
{
	glm::vec3 forwardDirection = GetForwardDirection();
	glm::vec2 normalizedViewDirection = glm::normalize(glm::vec2(forwardDirection.x, forwardDirection.z));
	m_Translation.x += m_MovementSpeed * normalizedViewDirection.x * deltaTime;
	m_Translation.z += m_MovementSpeed * normalizedViewDirection.y * deltaTime;
}

void MC::Camera::MoveBackward(float deltaTime)
{
	glm::vec3 forwardDirection = GetForwardDirection();
	glm::vec2 normalizedViewDirection = glm::normalize(glm::vec2(forwardDirection.x, forwardDirection.z));
	m_Translation.x += -m_MovementSpeed * normalizedViewDirection.x * deltaTime;
	m_Translation.z += -m_MovementSpeed * normalizedViewDirection.y * deltaTime;
}

void MC::Camera::StrafeLeft(float deltaTime)
{
	glm::vec3 forwardDirection = GetForwardDirection();
	glm::vec3 strafeDirection = glm::cross(forwardDirection, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::vec2 normalizedStrafeDirection = glm::normalize(glm::vec2(strafeDirection.x, strafeDirection.z));
	m_Translation.x += -m_MovementSpeed * normalizedStrafeDirection.x * deltaTime;
	m_Translation.z += -m_MovementSpeed * normalizedStrafeDirection.y * deltaTime;
}

void MC::Camera::StrafeRight(float deltaTime)
{
	glm::vec3 forwardDirection = GetForwardDirection();
	glm::vec3 strafeDirection = glm::cross(forwardDirection, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::vec2 normalizedStrafeDirection = glm::normalize(glm::vec2(strafeDirection.x, strafeDirection.z));
	m_Translation.x += m_MovementSpeed * normalizedStrafeDirection.x * deltaTime;
	m_Translation.z += m_MovementSpeed * normalizedStrafeDirection.y * deltaTime;
}

void MC::Camera::MoveUp(float deltaTime)
{
	m_Translation += m_MovementSpeed * glm::vec3(0.0f, 1.0f, 0.0f) * deltaTime;
}

void MC::Camera::MoveDown(float deltaTime)
{
	m_Translation += -m_MovementSpeed * glm::vec3(0.0f, 1.0f, 0.0f) * deltaTime;
}

void MC::Camera::SetRotation(const glm::vec3& rotation)
{
	m_Rotation = rotation;
}

void MC::Camera::AddRotation(const glm::vec3& rotation)
{
	m_Rotation += rotation;
}
