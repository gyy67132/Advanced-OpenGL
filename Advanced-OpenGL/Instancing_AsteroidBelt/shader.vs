#version 400 core
layout(location=0) in vec3 vertex;
layout(location=2) in vec2 texcoord;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out	vec2 texCoords;


void main()
{
	gl_Position = projection * view * model * vec4(vertex, 1.0);
	texCoords = texcoord;
}