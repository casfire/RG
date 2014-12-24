#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 uv;

uniform mat4 uViewMat;
uniform mat4 uProjMat;
uniform mat4 uModelMat;

smooth out vec2 fUV;
smooth out vec3 fNormal;
smooth out vec3 fPosition;

void main() {
	
	vec3 position_cameraspace = (uViewMat * uModelMat * vec4(position, 1)).xyz;
	vec3 normal_cameraspace = (uViewMat * uModelMat * vec4(normal, 0)).xyz;
	gl_Position = uProjMat * uViewMat * uModelMat * vec4(position, 1.0f);
	
	fUV = uv;
	fNormal = normal_cameraspace;
	fPosition = position_cameraspace;
	
}
