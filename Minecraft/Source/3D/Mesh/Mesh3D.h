#pragma once

#include "3D/Vertex3D.h"

#include <glew.h>
#include <string>

namespace MC {
	class Mesh3D{
	private:
		Vertex3D* vertices;
		GLuint numVertices;
		GLuint* indices;
		GLuint numIndices;
		GLuint vramHandleVBO;
		GLuint vramHandleIBO;
	public:
		Mesh3D();
		Mesh3D(const std::string& pathToModel, bool shouldLoadToVRAM);
		~Mesh3D();

		GLsizeiptr VertexBufferSize();
		GLsizeiptr IndexBufferSize();

		void LoadToRAM(const std::string& path);
		void UnloadFromRAM();
		void LoadToVRAM();
		void UnloadFromVRAM();
	};
}