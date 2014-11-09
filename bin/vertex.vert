#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 color;
uniform mat4 mat_M;
uniform mat4 mat_V;
uniform mat4 mat_P;

smooth out vec4 outColor;
smooth out vec4 outNormal;

void main() {
	
	gl_Position =  mat_P * mat_V * mat_M * vec4(position, 1.0f);
	outColor = vec4(color, 1.0f);
	outNormal = vec4(normal, 1.0f);
	
}