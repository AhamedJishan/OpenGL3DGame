#version 330 core

out vec4 Color;

in vec2 texCoords;

uniform sampler2D textureSampler;

void main()
{
	Color = texture(textureSampler, texCoords);
}