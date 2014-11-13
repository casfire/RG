#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 color;
uniform mat4 mat_M;
uniform mat4 mat_V;
uniform mat4 mat_P;

smooth out vec3 fColor;
out vec3 fNormal;
out vec3 fPosition;

void main() {
	
	vec3 position_cameraspace = (mat_V * mat_M * vec4(position, 1)).xyz;
	vec3 normal_cameraspace = (mat_V * mat_M * vec4(normal, 0)).xyz;
	gl_Position =  mat_P * mat_V * mat_M * vec4(position, 1.0f);
	
	fColor = color;
	fNormal = normal_cameraspace;
	fPosition = position_cameraspace;
	
}