#version 400 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in VS_OUT {
	vec2 texCoords;
}gs_in[];

out vec2 TexCoords;

uniform float time;

vec3 GetNormal()
{
	vec3 a = vec3(gl_in[0].gl_Position)  - vec3(gl_in[1].gl_Position);
	vec3 b = vec3(gl_in[2].gl_Position)  - vec3(gl_in[1].gl_Position);
	vec3 c = cross(a, b);
	return normalize(c);
}

vec4 explode(vec4 position, vec3 normal)
{
	float magnitude = 1.0;
	vec3 direction = normal * ((sin(time) + 1.0)/2.0) * magnitude;
	return position + vec4(direction, 0.0);
}

void main()
{
	vec3 Normal = GetNormal();

	gl_Position = explode(gl_in[0].gl_Position, Normal);
	TexCoords = gs_in[0].texCoords;
	EmitVertex();

	gl_Position = explode(gl_in[1].gl_Position, Normal);
	TexCoords = gs_in[1].texCoords;
	EmitVertex();

	gl_Position = explode(gl_in[2].gl_Position, Normal);
	TexCoords = gs_in[2].texCoords;
	EmitVertex();
	EndPrimitive();
}