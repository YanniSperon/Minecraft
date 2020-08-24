#pragma once

#include "Object3D.h"
#include "Timer.h"

#include <string>

namespace MC {
	class MeshAnimatedObject3D : public Object3D {
	protected:
		int m_CurrentFrame;
		int m_NumberOfFrames;

		Timer m_Timer;

		std::string m_Prefix;
		std::string m_Suffix;
	public:
		MeshAnimatedObject3D(const std::string& meshPath, const std::string& shaderPath, const std::string& texturePath, int numberOfFrames);
		~MeshAnimatedObject3D();

		virtual void Update(float deltaTime);

		static std::string GetPath(const std::string& prefix, const std::string& suffix, const std::string& currentFrameString);
		static std::string GetPrefix(const std::string& path);
		static std::string GetSuffix(const std::string& path);
	};
}