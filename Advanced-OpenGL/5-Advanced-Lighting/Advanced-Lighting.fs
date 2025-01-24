#version 430 core

in VS_OUT{
	vec2 TexCoords;
	vec3 Normals;
	vec3 FragPos;
}vs_in;

uniform sampler2D texture1; 
uniform vec3 lightPos;
uniform vec3 viewPos;

out vec4 FragColor;

uniform bool Blinn;

void main()
{
	
	vec3 color = texture(texture1, vs_in.TexCoords).rgb;

	vec3 ambient = color * 0.05;

	vec3 lightDir = normalize(lightPos - vs_in.FragPos);
	vec3 normal = normalize(vs_in.Normals);
	float diff = max(dot(lightDir,normal), 0.0);
	vec3 diffuse = diff * color;

	float spec = 0.0;
	vec3 viewDir = normalize(viewPos - vs_in.FragPos);
	if(Blinn){
		vec3 halfDir = normalize(viewDir + lightDir);
		spec = pow(max(dot(halfDir, normal ), 0.0), 16.0);
	}
	else{
		vec3 reflectDir = reflect(-lightDir, normal);
		spec = pow(max(dot(reflectDir, viewDir ), 0.0), 8.0);
	}
	
	vec3 specular = spec * vec3(0.5);

	FragColor = vec4(ambient + diffuse + specular, 1.0);
}