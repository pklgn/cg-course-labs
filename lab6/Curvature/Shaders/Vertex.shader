#version 330 core

layout(location = 0) in vec3 position;

out vec3 Color;
out vec3 FragPos;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

void main()
{
	float theta = position.x;
	float R = (1.0 + sin(theta)) * (1.0 + 0.9 * cos(8.0 * theta)) * (1.0 + 0.1 * cos(24.0 * theta)) * (0.5 + 0.05 * cos(140.0 * theta));
	float x = R * cos(theta) * 1;
	float y = R * sin(theta) * 1;

	FragPos = vec3(u_model * vec4(x, y, 1.0, 1.0));
	gl_Position = u_projection * u_view * vec4(FragPos, 1.0f);
	Color = vec3(1.0f, 1.0f, 1.0f);
};