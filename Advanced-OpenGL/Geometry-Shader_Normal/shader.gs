#version 400 core

layout(triangles) in;
layout(line_strip, max_vertices = 6) out;

in VS_OUT {
	vec3 Normals;
}gs_in[];

uniform mat4 projection;

void gelerateLine(int index)
{
	gl_Position = projection * gl_in[index].gl_Position;
	EmitVertex();
	gl_Position = projection * (gl_in[index].gl_Position + vec4(gs_in[index].Normals * 0.2, 0.0));
	EmitVertex();
	EndPrimitive();
}

void main()
{
	gelerateLine(0);
	gelerateLine(1);
	gelerateLine(2);
}