#version 410 core

/*
 * Vertex Shader - Only passes shared values from CPU to the fragment shader.
 */

layout (location = 0) attribute vec3 pos;
layout (location = 1) attribute vec2 texCoord;

varying float vSystemTime;
varying vec2 vSystemResolution;
varying vec3 vMouse;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

uniform float systemTime;
uniform vec2 systemResolution;
uniform vec3 mouse;

void main()
{
	gl_Position = u_projection * u_view * u_model * vec4(pos, 1.0);
	vSystemTime = systemTime;
	vSystemResolution = systemResolution;
	vMouse = mouse;
}