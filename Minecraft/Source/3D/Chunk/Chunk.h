#pragma once

#include <glew.h>
#include <string>

#include "Vendor/glm/glm.hpp"

namespace MC {
	class Chunk {
	private:
		Vertex3D* m_Vertices;
		GLuint m_NumVertices;
		GLuint* m_Indices;
		GLuint m_NumIndices;
		GLuint m_VRAMHandleVAO;
		GLuint m_VRAMHandleVBO;
		GLuint m_VRAMHandleIBO;

		bool m_FakeUser;
	public:
		Mesh3D(const std::string& pathToModel, bool shouldLoadToVRAM = true);
		~Mesh3D();

		void Bind();
		void Draw();

		GLsizeiptr VertexBufferSize();
		GLsizeiptr IndexBufferSize();

		void LoadToRAM(const std::string& path);
		void UnloadFromRAM();
		void LoadToVRAM();
		void UnloadFromVRAM();

		Vertex3D* GetVertices();
		GLuint GetNumVertices();
		GLuint* GetIndices();
		GLuint GetNumIndices();

		void SetHasFakeUser(bool fakeUser);
		bool GetHasFakeUser();

		static void Unbind();
	};
}