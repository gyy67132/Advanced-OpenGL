#version 430 core

in vec3 mvPos;
in vec3 Normals;

uniform samplerCube skyboxTexture; 
uniform vec3 eye;

out vec4 FragColor;

void main()
{
	vec3 eyeDir = normalize(eye - mvPos);
	//vec3 reflectDir = reflect(-eyeDir, normalize(Normals));

	vec3 refractDir = refract(-eyeDir, normalize(Normals), 1.0/1.52 );

	FragColor = vec4(texture(skyboxTexture, refractDir).rgb, 1.0);
}