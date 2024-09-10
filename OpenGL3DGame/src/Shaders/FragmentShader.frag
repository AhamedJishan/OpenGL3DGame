#version 330 core

out vec4 Out_Color;

struct Material
{
	vec3 specularColor;
	float shineDamper;
	float reflectivity;
};

struct Light
{
	vec3 color;
	vec3 ambient;
	vec3 position;
};

uniform sampler2D texture_diffuse1;
uniform bool useTexture;

uniform Light light;
uniform Material material;
uniform vec3 viewPos;

in vec2 TexCoords;
in vec3 FragPos;
//in vec3 ViewPos;
in vec3 Normals;

void main()
{
	vec3 color;
	if (!useTexture)
		color = vec3(0.7, 0.7, 0.7);
	else
		color = texture(texture_diffuse1, TexCoords).xyz;

	// AMBIENT COLOR
	vec3 ambientColor = light.ambient * color;

	// DIFFUSE COLOR
	vec3 normal = normalize(Normals);
	vec3 lightDir = normalize(light.position - FragPos);
	float diffuseFactor = max(dot(normal, lightDir), 0.0);
	vec3 diffuseColor = light.color * (diffuseFactor * color);

	// SPECULAR COLOR
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectedDir = reflect(-lightDir, normal);
	float specularFactor = pow(max(dot(viewDir, reflectedDir), 0.0), material.shineDamper);
	specularFactor *= max(min(material.reflectivity, 1.0), 0.0);
	vec3 specularColor = material.specularColor * specularFactor * color;

	color = ambientColor + diffuseColor + specularColor;

	Out_Color = vec4(color, 1.0);
}