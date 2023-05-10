#version 330 core

in vec3 Color;
in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoord;

out vec4 fragColor;

uniform vec3 u_lightPos;
uniform vec3 u_lightColor;
uniform vec3 u_objectColor;
uniform sampler2D u_sampler;

void main()
{
	// ambient
	float ambientStrength = 0.5;
	vec3 ambient = ambientStrength * u_lightColor;

	// diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(u_lightPos - FragPos);
	// TODO: ����� abs ������
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * u_lightColor;

	vec3 result = (ambient + diffuse) * Color;

	//fragColor = vec4(result, 1.0);
	fragColor = vec4(ambient + diffuse, 1) * texture2D(u_sampler, TexCoord);
}