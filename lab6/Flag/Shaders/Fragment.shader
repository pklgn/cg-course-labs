#version 330 core

in vec3 Color;
in vec3 FragPos;

out vec4 fragColor;

float aspectRatio;
uniform vec2 u_resolution;
uniform float u_radius;
uniform float u_thickness;

float circle(in vec2 _st, in float _radius, in vec2 _centerOffset)
{
	vec2 dist = _st - (vec2(0.5) - _centerOffset);
	dist = vec2(aspectRatio * dist.x, dist.y);
	return 1. - smoothstep(_radius - (_radius * 0.1), _radius + (_radius * 0.1), dot(dist, dist) * 4.0);
}

void main()
{
	aspectRatio = u_resolution.x / u_resolution.y;
	vec2 st = gl_FragCoord.xy / u_resolution.xy;

	vec2 firstRingOffset = vec2(0.0f, 0.0f);
	float inInnerCircle = circle(st, u_radius / u_resolution.x, firstRingOffset);
	float inOuterCircle = circle(st, (1 + u_thickness) * u_radius / u_resolution.x, firstRingOffset);
	
	if (inInnerCircle != 0.0f && inOuterCircle != 0.0f)
	{
		fragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	}
	else if (inInnerCircle == 0.0f && inOuterCircle != 0.0f)
	{
		fragColor = vec4(0.0f, 0.0f, 1.0f, 1.0f);
	}
	else
	{
		fragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	}
}