#version 330 core

in vec3 Color;
in vec3 FragPos;

out vec4 fragColor;

void main()
{
	float x = gl_FragCoord.x / 500.0;
	vec3 color = vec3(0.5 + 0.5 * sin(20.0 * x), 0.5 + 0.5 * cos(20.0 * x), 0.5 + 0.5 * sin(20.0 * x + 0.5));
	fragColor = vec4(color, 1.0);
}