#pragma once

#include "Vendor/glm/glm.hpp"
#include "3D/Object/Object3D.h"

#include <memory>

namespace MC {
	class Camera {
	private:
		float m_FOV;
		float m_NearPlane;
		float m_FarPlane;

		float m_MovementSpeed;

		float m_OldMouseX;
		float m_OldMouseY;

		glm::vec3 m_Translation;
		glm::vec3 m_Rotation;

		bool m_WasUsedYet;

		std::unique_ptr<Object3D> m_Skybox;
	public:
		Camera();

		void SetFOV(float FOV);
		void SetNearPlane(float nearPlane);
		void SetFarPlane(float farPlane);
		void SetMovementSpeed(float movementSpeed);
		void SetOldMouseX(float x);
		void SetOldMouseY(float y);
		void SetTranslation(const glm::vec3& translation);
		void SetUpDirection(const glm::vec3& upDirection);
		void SetWasUsedYet(bool wasUsedYet);
		void SetSkybox(std::unique_ptr<Object3D> skybox);

		const float GetFOV();
		const float GetNearPlane();
		const float GetFarPlane();
		const float GetMovementSpeed();
		const float GetOldMouseX();
		const float GetOldMouseY();
		const glm::vec3& GetTranslation();
		const glm::vec3& GetRotation();
		const bool GetWasUsedYet();
		Object3D& GetSkybox();
		glm::vec3 GetUpDirection();
		glm::vec3 GetForwardDirection();
		glm::mat4 GetProjectionMatrix();
		glm::mat4 GetViewMatrix();

		void LookAt(glm::vec3 position);
		void LookAtMouse(float sensitivity, float xPos, float yPos);

		void MoveForward(float deltaTime);
		void MoveBackward(float deltaTime);
		void StrafeLeft(float deltaTime);
		void StrafeRight(float deltaTime);
		void MoveUp(float deltaTime);
		void MoveDown(float deltaTime);

		void SetRotation(const glm::vec3& rotation);

		void AddRotation(const glm::vec3& rotation);

		void DrawSkybox(const glm::mat4& projection, const glm::mat4& view, const glm::mat4& modelOffset);
	};
}