#version 330

smooth in vec3 fColor;
in vec3 fNormal;
in vec3 fPosition;

void main() {
	
	vec3 position_cameraspace = fPosition;
	vec3 normal_cameraspace = fNormal;
	vec3 eyedir_cameraspace = - position_cameraspace;
	vec3 lightpos_cameraspace = vec3(10, 10, 5);
	vec3 lightdir_cameraspace = lightpos_cameraspace + eyedir_cameraspace;
	vec3 l = normalize(lightdir_cameraspace);
	vec3 n = normalize(normal_cameraspace);
	float diffuseAmount = clamp(dot(n, l), 0, 1);
	
	float ambientAmount = 0.3;
	
	vec3 R = reflect(-l, n);
	vec3 E = normalize(eyedir_cameraspace);
	float cosAlpha = clamp(dot(E, R), 0, 1);
	float specularAmount = pow(cosAlpha, 20);
	
	vec3 finalColor =
		+ fColor * ambientAmount
		+ fColor * diffuseAmount
		+ specularAmount * vec3(0.6, 0.6, 0.6);
	
	gl_FragColor = vec4(finalColor, 1.0);
}
