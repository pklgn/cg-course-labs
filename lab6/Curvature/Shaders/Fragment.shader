#version 330 core

in vec3 Color;
in vec3 FragPos;

out vec4 fragColor;

void main()
{
	//fragColor = vec4(result, 1.0);
	fragColor = vec4(Color, 1.0);
}