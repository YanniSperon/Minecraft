#version 460

layout (location = 0) in vec3 in_VertexPosition;
layout (location = 1) in vec3 in_VertexNormal;
layout (location = 2) in vec2 in_VertexTexCoord;
layour (location = 3) in mat4 in_InstanceMatrix;

layout (std140) uniform ubo_Matrices
{
	mat4 P;
	mat4 V;
};

//uniform mat4 M;

out vec2 s_TexCoord;

void main()
{
	s_TexCoord = in_VertexTexCoord;
	gl_Position = P * V * in_InstanceMatrix * vec4(in_VertexPosition, 1.0);
}