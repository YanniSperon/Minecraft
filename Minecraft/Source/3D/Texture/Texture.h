#pragma once

#include <glew.h>
#include <string>

namespace MC {
	class Texture {
	private:
		GLuint ID;
	public:
		Texture(const std::string& name);
		~Texture();

		void LoadTexture(const std::string& name);

		void Bind();

		GLuint GetID();

		static void Unbind();
	};
}