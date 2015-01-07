#version 330

smooth in vec2 fUV;
smooth in vec3 fNormal;
smooth in vec3 fTangent;
smooth in vec3 fBinormal;
smooth in vec3 fPositionWorldspace;
smooth in vec3   fEyeDirCameraspace;

smooth in vec3 fDirLightDirCameraspace;
smooth in vec3 fPointLightDirCameraspace;

uniform sampler2D uDiffuseSampler;
uniform sampler2D uNormalSampler;

uniform float uAmbient;

uniform vec3  uDirLightColor;
uniform float uDirLightIntensity;
uniform vec3  uDirLightDirection;

uniform vec3  uPointLightColor;
uniform float uPointLightIntensity;
uniform float uPointLightSpread;
uniform vec3  uPointLightPosition;

out vec3 color;

vec3 getNormal() {
	vec3 mapped   = (2 * texture(uNormalSampler, fUV).rgb) - 1;
	vec3 normal   = normalize(fNormal);
	vec3 tangent  = normalize(fTangent);
	vec3 binormal = normalize(fBinormal);
	mat3 TBN = mat3(tangent, binormal, normal);
	return TBN * mapped;
}

void main() {
	
	/* Constants */
	float specularSpread = 80; // [1, inf]
	float specularPower = 0.2; // [0, 1]
	
	/* Variables */
	vec3 n, l, E, R, colorDiffuse;
	float diffuseAmount, specularAmount, attenuation;
	
	/* Constant variables */
	colorDiffuse = texture(uDiffuseSampler, fUV).rgb;
	n = normalize(getNormal());
	E = normalize(fEyeDirCameraspace);
	
	/* No light */
	color = vec3(0, 0, 0);
	
	/* Add ambient light */
	color += uAmbient * colorDiffuse;
	
	/* Add diffuse directional light */
	l = normalize(fDirLightDirCameraspace);
	diffuseAmount = clamp(dot(n, l), 0, 1);
	color += diffuseAmount * colorDiffuse * uDirLightColor * uDirLightIntensity;
	
	/* Add specular directional light */
	R = reflect(-l, n);
	specularAmount = pow(clamp(dot(E, R), 0, 1), specularSpread);
	color += specularAmount * colorDiffuse * uDirLightColor * specularPower * uDirLightIntensity;
	
	/* Add diffuse point light */
	l = normalize(fPointLightDirCameraspace);
	diffuseAmount = clamp(dot(n, l), 0, 1);
	float distance = length(uPointLightPosition - fPositionWorldspace);
	attenuation = 1.f / (1.f + uPointLightSpread * pow(distance, 2));
	color += diffuseAmount * colorDiffuse * uPointLightColor * uPointLightIntensity * attenuation;
	
	/* Add specular point light */
	R = reflect(-l, n);
	specularAmount = pow(clamp(dot(E, R), 0, 1), specularSpread);
	color += specularAmount * colorDiffuse * uPointLightColor * specularPower * uPointLightIntensity * attenuation;
	
}
