#pragma once

#include <glew.h>
#include <string>

namespace MC {
	class Texture {
	private:
		GLuint m_ID;

		bool m_FakeUser;
	public:
		Texture(const std::string& name);
		~Texture();

		void LoadTexture(const std::string& name);

		void Bind();

		GLuint GetID();

		bool HasFakeUser();

		static void Unbind();
	};
}