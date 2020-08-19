#pragma once

#include "glew.h"
#include "3D/Vertex3D.h"

namespace MC {
	struct Mesh3D {

		Mesh3D()
			: vertices(nullptr), numVertices(0), indices(nullptr), numIndices(0), vramHandle(0)
		{

		}

		~Mesh3D()
		{
			delete[] vertices;
			delete[] indices;
			numVertices = numIndices = 0;
		}

		Vertex3D* vertices;
		GLuint numVertices;
		GLuint* indices;
		GLuint numIndices;
		GLuint vramHandle;

		GLsizeiptr VertexBufferSize() const {
			return numVertices * sizeof(Vertex3D);
		}

		GLsizeiptr IndexBufferSize() const {
			return numIndices * sizeof(GLuint);
		}
	};
}