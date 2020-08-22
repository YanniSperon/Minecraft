#include "Mesh3D.h"
#include "Console.h"

#include <glew.h>
#include <vector>

#include <string>
#include <vector>
#include <fstream>
#include <strstream>

MC::Mesh3D::Mesh3D(const std::string& pathToModel, bool shouldLoadToVRAM)
	: m_Vertices(nullptr), m_NumVertices(0), m_Indices(nullptr), m_NumIndices(0), m_VRAMHandleVBO(0), m_VRAMHandleIBO(0), m_FakeUser(false)
{
	LoadToRAM(pathToModel);
	if (shouldLoadToVRAM) {
		LoadToVRAM();
	}
}

MC::Mesh3D::~Mesh3D()
{
	UnloadFromRAM();
	UnloadFromVRAM();
	Console::Warning("Deleted mesh");
}

void MC::Mesh3D::Bind()
{
	glBindVertexArray(m_VRAMHandleVAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_VRAMHandleIBO);
}

void MC::Mesh3D::Draw()
{
	glDrawElements(GL_TRIANGLES, m_NumIndices, GL_UNSIGNED_INT, 0);
}

GLsizeiptr MC::Mesh3D::VertexBufferSize()
{
	return m_NumVertices * sizeof(Vertex3D);
}

GLsizeiptr MC::Mesh3D::IndexBufferSize()
{
	return m_NumVertices * sizeof(GLuint);
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

	m_NumVertices = tempVertices.size();
	m_Vertices = new Vertex3D[m_NumVertices];
	for (unsigned int i = 0; i < m_NumVertices; i++) {
		m_Vertices[i] = tempVertices[i];
	}

	m_NumIndices = tempIndices.size();
	m_Indices = new GLuint[m_NumIndices];
	for (unsigned int i = 0; i < m_NumIndices; i++) {
		m_Indices[i] = tempIndices[i];
	}
}

void MC::Mesh3D::UnloadFromRAM()
{
	delete[] m_Vertices;
	delete[] m_Indices;
	m_Vertices = nullptr;
	m_Indices = nullptr;
}

void MC::Mesh3D::LoadToVRAM()
{
	UnloadFromVRAM();
	
	glGenVertexArrays(1, &m_VRAMHandleVAO);
	glBindVertexArray(m_VRAMHandleVAO);

	glGenBuffers(1, &m_VRAMHandleVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VRAMHandleVBO);
	glBufferData(GL_ARRAY_BUFFER, VertexBufferSize(), m_Vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (char*)(sizeof(float) * 3));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (char*)(sizeof(float) * 6));

	glGenBuffers(1, &m_VRAMHandleIBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_VRAMHandleIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, IndexBufferSize(), m_Indices, GL_STATIC_DRAW);

	glFinish();
}

void MC::Mesh3D::UnloadFromVRAM()
{
	if (m_VRAMHandleVBO != 0) {
		glDeleteBuffers(1, &m_VRAMHandleVBO);
		glDeleteBuffers(1, &m_VRAMHandleIBO);
		glDeleteVertexArrays(1, &m_VRAMHandleVAO);

		m_VRAMHandleVBO = 0;
		m_VRAMHandleIBO = 0;
	}
}

MC::Vertex3D* MC::Mesh3D::GetVertices()
{
	return m_Vertices;
}

GLuint MC::Mesh3D::GetNumVertices()
{
	return m_NumVertices;
}

GLuint* MC::Mesh3D::GetIndices()
{
	return m_Indices;
}

GLuint MC::Mesh3D::GetNumIndices()
{
	return m_NumIndices;
}

void MC::Mesh3D::SetHasFakeUser(bool fakeUser)
{
	m_FakeUser = fakeUser;
}

bool MC::Mesh3D::GetHasFakeUser()
{
	return m_FakeUser;
}

void MC::Mesh3D::Unbind()
{
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
