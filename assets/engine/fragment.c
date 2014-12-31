#version 330

smooth in vec3 fPosition;
smooth in vec2 fUV;
smooth in vec3 fNormal;

//uniform sampler2D uTexture;

out vec3 color;

void main() {
	
	vec3  lightPosition = vec3(0, 0, 0);
	float lightPower = 40.0;
	vec3  lightColor = vec3(1, 1, 1);
	float ambientAmount = 0.3;
	int   specularSpread = 60;
	float specularPower = 0.2;
	//vec3  diffuseColor = texture(uTexture, fUV).rgb;
	vec3  diffuseColor = vec3(0.2, 0.8, 0.4);
	
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
