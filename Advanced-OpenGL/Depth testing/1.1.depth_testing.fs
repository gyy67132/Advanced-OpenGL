#version 430 core

in vec2 TexCoords;

uniform sampler2D texture1; 

out vec4 FragColor;

void main()
{
	//FragColor = texture(texture1, TexCoords);
	FragColor = vec4(vec3(gl_FragCoord.z),1.0);
}