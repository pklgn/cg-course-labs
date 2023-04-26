#version 330 core

in vec3 Color;
in vec3 Normal;
in vec3 FragPos;

out vec4 fragColor;

uniform vec3 u_lightPos;
uniform vec3 u_lightColor;
uniform vec3 u_objectColor;

void main()
{
	// ambient
	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * u_lightColor;

	vec3 result = ambient * Color;

	fragColor = vec4(result, 1);
}