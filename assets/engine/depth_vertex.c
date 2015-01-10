#version 330

layout(location = 0) in vec3 position;

uniform mat4 uDepthM;
uniform mat4 uDepthV;
uniform mat4 uDepthP;

void main() {
	
	gl_Position = uDepthP * uDepthV * uDepthM * vec4(position, 1);
	
}
