#version 330 core

out vec4 Out_Color;

in vec3 color;

void main()
{
	Out_Color = vec4(color, 1.0);
}