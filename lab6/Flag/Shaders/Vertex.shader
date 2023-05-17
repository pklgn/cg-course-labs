#version 330 core

layout (location = 0) in vec3 position;

out vec3 Color;
out vec3 FragPos;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

void main()
{
	FragPos = (u_model * vec4(position, 1.0)).xyz;
	gl_Position = u_projection * u_view * vec4(FragPos, 1.0f);
	Color = vec3(1.0f, 1.0f, 1.0f);
};