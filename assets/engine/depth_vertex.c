#version 330

layout(location = 0) in vec3 position;

uniform mat4 uDepthVP;
uniform mat4 uDepthM;

void main() {
	
	gl_Position = uDepthVP * uDepthM * vec4(position, 1);
	
}
