#version 330

smooth in vec3 fPosition;
smooth in vec2 fUV;
smooth in vec3 fNormal;

uniform sampler2D uTexture;

out vec3 color;

void main() {
	
	vec3  lightPosition = vec3(10, 10, 5);
	float lightPower = 200.0;
	vec3  lightColor = vec3(1, 1, 1);
	float ambientAmount = 0.3;
	int   specularSpread = 10;
	float specularPower = 0.5;
	vec3  diffuseColor = texture(uTexture, fUV).rgb;
	
	float distance = pow(length(lightPosition - fPosition), 2);
	vec3 l = normalize(lightPosition - fPosition);
	vec3 n = normalize(fNormal);
	float diffuseAmount = clamp(dot(n, l), 0, 1);
	
	vec3 R = reflect(-l, n);
	vec3 E = normalize(-fPosition);
	float specularAmount = pow(clamp(dot(E, R), 0, 1), specularSpread);
	
	color = 
		+ ambientAmount  * diffuseColor
		+ diffuseAmount  * diffuseColor * lightColor * lightPower / distance
		+ specularAmount * lightColor * lightPower * specularPower / distance;
}
