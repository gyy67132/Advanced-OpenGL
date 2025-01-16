#version 430 core

in vec2 TexCoords;

uniform sampler2D texture1; 

out vec4 FragColor;

const float offset = 1.0/300.0;

void main()
{
	//FragColor = texture(texture1, TexCoords);
	//反相
	//FragColor = vec4(vec3(1.0 - texture(texture1, TexCoords).rgb), 1.0);

	//灰度
	//FragColor = texture(texture1, TexCoords);
	//float average = (FragColor.r + FragColor.g + FragColor.b)/3.0;
	//float average = 0.2126*FragColor.r + 0.7152*FragColor.g + 0.0722*FragColor.b;
	//FragColor = vec4(vec3(average), 1.0);

	//卷积核

	vec2 offsets[] = {
		vec2(-offset,offset),
		vec2(0,offset),
		vec2(offset,offset),

		vec2(-offset,0),
		vec2(0,0),
		vec2(offset,0),

		vec2(-offset,-offset),
		vec2(0,-offset),
		vec2(offset,-offset)
	};

	vec3 sampleTex[9];
	for(unsigned int i = 0; i < 9; i++)
	{
		sampleTex[i] = vec3(texture(texture1, TexCoords.st + offsets[i]));
	}

	vec3 color = vec3(0);
	//锐化
	//float kernel[] = {
	//	-1,-1,-1,
	//	-1,9,-1,
	//	-1,-1,-1
	//};
	//模糊
	//float kernel[] = {
	//	1.0 / 16, 2.0 / 16, 1.0 / 16,
	//	2.0 / 16, 4.0 / 16, 2.0 / 16,
	//	1.0 / 16, 2.0 / 16, 1.0 / 16
	//};
	//边缘检测
	float kernel[] = {
		1,1,1,
		1,-8,1,
		1,1,1
	};
	for(unsigned int i = 0; i < 9; i++)
	{
		color += sampleTex[i] * kernel[i];
	}

	FragColor = vec4(color, 1.0);
}