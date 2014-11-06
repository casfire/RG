#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
uniform mat4 MVP_m;
uniform mat4 MVP_v;
uniform mat4 MVP_p;

smooth out vec4 theColor;

void main() {
	
	gl_Position = MVP_p * MVP_v * MVP_m * vec4(position, 1.0f);
	
	theColor = vec4(color, 1.0f);
}