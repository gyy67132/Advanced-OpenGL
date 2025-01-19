#version 400 core
layout(location=0) in vec3 vertex;
layout(location=2) in vec2 texcoord;
layout(location=3) in mat4 instanceMatrix;

uniform mat4 projection;
uniform mat4 view;

out	vec2 texCoords;


void main()
{
	gl_Position = projection * view * instanceMatrix * vec4(vertex, 1.0);
	texCoords = texcoord;
}