#version 330 core

out vec4 Color;

in vec2 texCoords;

uniform sampler2D texture_diffuse1;
uniform bool useTexture;

void main()
{
	if (!useTexture)
		Color = vec4(0.7, 0.7, 0.7, 1.0);
	else
		Color = texture(texture_diffuse1, texCoords);
}