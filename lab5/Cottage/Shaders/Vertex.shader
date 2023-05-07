#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 colors;
layout(location = 2) in vec3 normal;

out vec3 Color;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

void main()
{
	FragPos = vec3(u_model * vec4(position, 1.0));
	Normal = normal;
	gl_Position = u_projection * u_view * vec4(FragPos, 1.0f);
	Color = colors;
};