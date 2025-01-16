#version 430 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormals;

out vec3 mvPos;
out vec3 Normals;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0);
	Normals = mat3(transpose(inverse(model))) * aNormals;
	mvPos = vec3(model * vec4(aPos, 1.0));
}