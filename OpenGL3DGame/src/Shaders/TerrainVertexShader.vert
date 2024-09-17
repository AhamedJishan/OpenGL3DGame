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
uniform float textureTileSize;

out vec2 texCoords;
out float height;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0);

	texCoords = aTexCoords * textureTileSize;
	height = (model * vec4(aPos, 1.0)).y;
}