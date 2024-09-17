#version 330 core

out vec4 Out_Color;

uniform sampler2D terrainTexture0;
uniform sampler2D terrainTexture1;
uniform sampler2D terrainTexture2;
uniform sampler2D terrainTexture3;

uniform float textureHeight0;
uniform float textureHeight1;
uniform float textureHeight2;
uniform float textureHeight3;

in vec2 texCoords;
in float height;

void main()
{
	vec4 texColor;

	if (height <= textureHeight0)
	{
		texColor = texture(terrainTexture0, texCoords);
	}
	else if (height <= textureHeight1)
	{
		vec4 color1 = texture(terrainTexture0, texCoords);
		vec4 color2 = texture(terrainTexture1, texCoords);
		float blendFactor = (height - textureHeight0) / (textureHeight1 - textureHeight0);
		texColor = mix(color1, color2, blendFactor);
	}
	else if (height <= textureHeight2)
	{
		vec4 color1 = texture(terrainTexture1, texCoords);
		vec4 color2 = texture(terrainTexture2, texCoords);
		float blendFactor = (height - textureHeight1) / (textureHeight2 - textureHeight1);
		texColor = mix(color1, color2, blendFactor);
	}
	else if (height > textureHeight2)
	{
		vec4 color1 = texture(terrainTexture2, texCoords);
		vec4 color2 = texture(terrainTexture3, texCoords);
		float blendFactor = (height - textureHeight2) / (textureHeight3 - textureHeight2);
		texColor = mix(color1, color2, blendFactor);
	}

	Out_Color = texColor;
	//Out_Color = vec4(textureHeight0, 0.1, 0.1, 1.0);
}