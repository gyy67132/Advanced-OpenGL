#version 430 core

in vec2 TexCoords;

uniform sampler2D texture1; 

out vec4 FragColor;

void main()
{
	FragColor = texture(texture1, TexCoords);
}