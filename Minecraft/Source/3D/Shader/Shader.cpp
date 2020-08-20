#include "Shader.h"
#include "Console.h"

#include <string>
#include <fstream>
#include <sstream>

MC::Shader::Shader(const std::string& name)
    : ID(0)
{
    LoadShader((name + std::string(".geom")).c_str(), (name + std::string(".frag")).c_str());
}

MC::Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
    : ID(0)
{
    LoadShader(vertexPath.c_str(), fragmentPath.c_str());
}

MC::Shader::~Shader()
{
    glDeleteProgram(ID);
}

void MC::Shader::LoadShader(const char* vertexShaderPath, const char* fragmentShaderPath)
{
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    try
    {
        // open files
        vShaderFile.open(vertexShaderPath);
        fShaderFile.open(fragmentShaderPath);
        std::stringstream vShaderStream;
        std::stringstream fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        vShaderFile.close();
        fShaderFile.close();
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        Console::Error("Shader Files \"%s\" And \"%s\" Not Successfully Loaded", vertexShaderPath, fragmentShaderPath);
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    unsigned int vertex, fragment;
    int success;
    char infoLog[512];

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        Console::Error("Vertex Shader Failed Compilation \"%s\"", infoLog);
    };

    fragment = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        Console::Error("Fragment Shader Failed Compilation \"%s\"", infoLog);
    };

    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        Console::Error("Vertex and Fragment Shader Linking Failed \"%s\"", infoLog);
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void MC::Shader::Bind()
{
    glUseProgram(ID);
}

void MC::Shader::SetBool(const std::string& name, bool value)
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void MC::Shader::SetInt(const std::string& name, int value)
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void MC::Shader::SetFloat(const std::string& name, float value)
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void MC::Shader::Set2Float(const std::string& name, float x, float y)
{
    glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
}

void MC::Shader::Set3Float(const std::string& name, float x, float y, float z)
{
    glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}

void MC::Shader::Set4Float(const std::string& name, float x, float y, float z, float w)
{
    glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
}

void MC::Shader::SetVec2(const std::string& name, const glm::vec2& value)
{
    glUniform2f(glGetUniformLocation(ID, name.c_str()), value.x, value.y);
}

void MC::Shader::SetVec3(const std::string& name, const glm::vec3& value)
{
    glUniform3f(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z);
}

void MC::Shader::SetVec4(const std::string& name, const glm::vec4& value)
{
    glUniform4f(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z, value.w);
}

GLuint MC::Shader::GetID()
{
    return ID;
}

void MC::Shader::Unbind()
{
    glUseProgram(0);
}
