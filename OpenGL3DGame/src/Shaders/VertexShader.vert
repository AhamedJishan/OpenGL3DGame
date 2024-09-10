#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormals;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;
out vec3 Normals;
out vec3 FragPos;
//out vec3 ViewPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0);

	TexCoords = aTexCoords;
	FragPos = vec3(model * vec4(aPos, 1.0));
	Normals = mat3(transpose(inverse(model))) * aNormals;
	//ViewPos = vec3(inverse(view) * vec4(0.0, 0.0, 0.0, 1.0));
}