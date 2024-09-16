#version 330 core

out vec4 Out_Color;

uniform sampler2D terrainTexture;

in vec3 color;
in vec2 texCoords;

void main()
{
	vec4 texColor = texture(terrainTexture, texCoords);
	Out_Color = vec4(vec4(color, 1.0) * texColor);
}