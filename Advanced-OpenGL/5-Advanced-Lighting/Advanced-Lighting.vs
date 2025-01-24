#version 430 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormals;
layout(location = 2) in vec2 aTexCoords;

out VS_OUT{
	vec2 TexCoords;
	vec3 Normals;
	vec3 FragPos;
}vs_out;


uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * vec4(aPos, 1.0);
	vs_out.TexCoords = aTexCoords;
	vs_out.Normals = aNormals;
	vs_out.FragPos = aPos;
}