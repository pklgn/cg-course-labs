#version 330 core

in vec3 vs_color;

out vec4 fragColor;

uniform vec4 u_color;

void main()
{
	fragColor = vec4(vs_color, 1);
}