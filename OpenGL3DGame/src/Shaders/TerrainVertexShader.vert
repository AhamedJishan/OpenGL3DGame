#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormals;
layout (location = 2) in vec2 aTexCoords;

//out vec2 TexCoords;
//out vec3 Normals;
//out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform float minHeight;
uniform float maxHeight;

out vec3 color;
out vec2 texCoords;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0);

	float minMaxHeightDelta = maxHeight - minHeight;
	float heightRatio = (aPos.y-minHeight) / minMaxHeightDelta ;

	float c = heightRatio * 0.8 + 0.1;

	color = vec3(c);
	texCoords = aTexCoords;
}