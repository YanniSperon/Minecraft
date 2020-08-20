#include "Mesh3D.h"
#include "Console.h"

#include <glew.h>
#include <vector>

#include <string>
#include <vector>
#include <fstream>
#include <strstream>

MC::Mesh3D::Mesh3D()
	: vertices(nullptr), numVertices(0), indices(nullptr), numIndices(0), vramHandleVBO(0), vramHandleIBO(0)
{

}

MC::Mesh3D::Mesh3D(const std::string& pathToModel, bool shouldLoadToVRAM)
	: vertices(nullptr), numVertices(0), indices(nullptr), numIndices(0), vramHandleVBO(0), vramHandleIBO(0)
{
	LoadToRAM(pathToModel);
	if (shouldLoadToVRAM) {
		LoadToVRAM();
	}
}

MC::Mesh3D::~Mesh3D()
{
	
	// add delete the vram reference if it exists

}

GLsizeiptr MC::Mesh3D::VertexBufferSize()
{
	return numVertices * sizeof(Vertex3D);
}

GLsizeiptr MC::Mesh3D::IndexBufferSize()
{
	return numIndices * sizeof(GLuint);
}

void MC::Mesh3D::LoadToRAM(const std::string& path) {
	std::vector<Vertex3D> tempVertices;
	std::vector<GLuint> tempIndices;
	std::vector<glm::vec2> tempTex;
	std::vector<glm::vec3> tempNormals;

	std::ifstream file(path);

	if (!file.is_open()) {
		Console::Error("Invalid file - does not exist! \"%s\"", path.c_str());
	}

	while (!file.eof())
	{
		char line[128];
		file.getline(line, 128);

		std::strstream s;
		s << line;

		char junk;
		char slash = '/';

		if (line[0] == 'v' && line[1] == ' ')
		{
			glm::vec3 v;
			s >> junk >> v.x >> v.y >> v.z;
			Vertex3D vert;
			vert.position = v;
			tempVertices.push_back(vert);
		}
		else if (line[0] == 'v' && line[1] == 'n') {
			glm::vec3 v;
			s >> junk >> junk >> v.x >> v.y >> v.z;
			tempNormals.push_back(v);
		}
		else if (line[0] == 'f' && line[1] == ' ')
		{
			unsigned int f[3];
			unsigned int uv[3];
			unsigned int n[3];

			s >> junk >> f[0] >> slash >> uv[0] >> slash >> n[0] >> f[1] >> slash >> uv[1] >> slash >> n[1] >> f[2] >> slash >> uv[2] >> slash >> n[2];
			tempIndices.push_back(f[0] - 1);
			tempIndices.push_back(f[1] - 1);
			tempIndices.push_back(f[2] - 1);
			tempVertices.at(f[0] - 1).texCoord = glm::vec2(tempTex.at(uv[0] - 1).x, tempTex.at(uv[0] - 1).y);
			tempVertices.at(f[1] - 1).texCoord = glm::vec2(tempTex.at(uv[1] - 1).x, tempTex.at(uv[1] - 1).y);
			tempVertices.at(f[2] - 1).texCoord = glm::vec2(tempTex.at(uv[2] - 1).x, tempTex.at(uv[2] - 1).y);
			tempVertices.at(f[0] - 1).normal = tempNormals.at(n[0] - 1);
			tempVertices.at(f[1] - 1).normal = tempNormals.at(n[1] - 1);
			tempVertices.at(f[2] - 1).normal = tempNormals.at(n[2] - 1);
		}
		else if (line[0] == 'v' && line[1] == 't') {
			float one;
			float two;
			std::string name;
			s >> name;
			s >> one;
			s >> two;
			glm::vec2 uv;
			uv.x = one;
			uv.y = two;
			tempTex.push_back(uv);
		}
	}

	vertices = new Vertex3D[tempVertices.size()];
	for (unsigned int i = 0; i < tempVertices.size(); i++) {
		vertices[i] = tempVertices[i];
	}

	indices = new GLuint[tempIndices.size()];
	for (unsigned int i = 0; i < tempIndices.size(); i++) {
		indices[i] = tempIndices[i];
	}
}

void MC::Mesh3D::UnloadFromRAM()
{
	delete[] vertices;
	delete[] indices;
}

void MC::Mesh3D::LoadToVRAM()
{
	UnloadFromVRAM();
	
	glGenBuffers(1, &vramHandleVBO);
	glBindBuffer(GL_ARRAY_BUFFER, vramHandleVBO);
	glBufferData(GL_ARRAY_BUFFER, VertexBufferSize(), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (char*)(sizeof(float) * 3));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (char*)(sizeof(float) * 5));

	glGenBuffers(1, &vramHandleIBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vramHandleIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, IndexBufferSize(), indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glFinish();
}

void MC::Mesh3D::UnloadFromVRAM()
{
	if (vramHandleVBO != 0) {
		glDeleteBuffers(1, &vramHandleVBO);
		glDeleteBuffers(1, &vramHandleIBO);

		vramHandleVBO = 0;
		vramHandleIBO = 0;
	}
}
