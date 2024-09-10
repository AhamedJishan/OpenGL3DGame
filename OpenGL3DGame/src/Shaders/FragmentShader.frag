#version 330 core

out vec4 Out_Color;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normals;

uniform sampler2D texture_diffuse1;
uniform bool useTexture;
uniform vec3 lightPos;
uniform vec3 lightColor;

void main()
{
	vec3 color;
	if (!useTexture)
		color = vec3(0.7, 0.7, 0.7);
	else
		color = texture(texture_diffuse1, TexCoords).xyz;

	vec3 normal = normalize(Normals);
	vec3 lightDir = normalize(lightPos - FragPos);

	float diffuse = max(dot(normal, lightDir), 0.0);
	color = lightColor * color * diffuse;

	Out_Color = vec4(color, 1.0f);
}