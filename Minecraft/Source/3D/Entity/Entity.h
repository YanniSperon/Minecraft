#pragma once

#include "3D/Object/MeshAnimatedObject3D.h"

#include <memory>

#include "Vendor/glm/glm.hpp"

namespace MC {
	class Entity : public MeshAnimatedObject3D {
	private:
		glm::vec3 m_HitboxMin;
		glm::vec3 m_HitboxMax;
		glm::vec3 m_Velocity;

		glm::vec3 m_TerminalVelocity;

		float m_StepHeight;

		float m_Gravity;
		bool m_IsAnimating;
	public:
		Entity(const std::string& meshPath, const std::string& shaderPath, const std::string& texturePath, int numberOfFrames, const glm::vec3& hitboxMin, const glm::vec3& hitboxMax, const glm::vec3& terminalVelocity);
		~Entity();

		virtual void Update(float deltaTime);

		void SetVelocity(glm::vec3 velocity);

		void SetGravity(float gravity);
		void SetIsAnimating(bool isAnimating);

		bool IsInside(const glm::vec3& translation, const glm::vec3& hitboxMin, const glm::vec3& hitboxMax);

		const glm::vec3& GetHitboxMin();
		const glm::vec3& GetHitboxMax();
		const glm::vec3& GetHalfWidth();
		const glm::vec3& GetHitboxCenterWithTranslation();
		const glm::vec3& GetVelocity();
		const glm::vec3& GetTerminalVelocity();
		float GetGravity();
		bool GetIsAnimating();

		static void ResolveCollision(Entity* first, Entity* second);
	};
}