#version 400 core
layout(location = 0) in vec3 vertex;
layout(location = 1) in vec3 normals;

uniform mat4 view;
uniform mat4 model;

out VS_OUT{
	vec3 Normals;
}vs_out;

void main()
{
	gl_Position =  view * model *vec4(vertex, 1.0);
	vs_out.Normals = normalize(mat3(transpose(inverse(view * model))) * normals);
}