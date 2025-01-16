#version 430 core

in vec2 TexCoords;

uniform sampler2D texture1; 

out vec4 FragColor;

const float offset = 1.0/300.0;

void main()
{
	FragColor = texture(texture1, TexCoords);
}