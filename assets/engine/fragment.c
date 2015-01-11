#version 330

smooth in vec2 fUV;
smooth in vec3 fNormal;
smooth in vec3 fTangent;
smooth in vec3 fBinormal;
smooth in vec3 fPositionWorldspace;
smooth in vec3   fEyeDirCameraspace;
smooth in vec3 fDirLightDirCameraspace;
smooth in vec3 fPointLightDirCameraspace;
smooth in vec4 fShadowCoord;

uniform sampler2D uDiffuseSampler;
uniform sampler2D uNormalSampler;
uniform sampler2D uSpecularSampler;
uniform sampler2D uMaskSampler;
uniform sampler2D uEmitSampler;
uniform sampler2DShadow uShadowSampler;

uniform float uShadowDepthBias;
uniform vec2  uShadowTexelSize;
uniform ivec2 uShadowSamples;

uniform float uAmbient;
uniform float uModelSpecularExp;

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
	mat3 TBN      = mat3(tangent, binormal, normal);
	return TBN * mapped;
}

float getShadowValue() {
	float bias = uShadowDepthBias;
	float shadowValue = 0.f;
	vec2 coord = fShadowCoord.xy;
	ivec2 samples = uShadowSamples;
	for (int x = 0; x < samples.x; x++) {
		for (int y = 0; y < samples.y; y++) {
			vec2 off = ((vec2(x, y) + 0.5) / samples) * uShadowTexelSize;
			shadowValue += texture(uShadowSampler, vec3(coord + off, (fShadowCoord.z / fShadowCoord.w) - bias));
		}
	}
	return shadowValue / (samples.x * samples.y);
}

void main() {
	
	/* Variables */
	vec3 n, l, E, R, colorDiffuse, specularPower, emit;
	float diffuseAmount, specularAmount, attenuation, shadowValue;
	
	/* Alpha mask */
	if (texture(uMaskSampler, fUV).r < 0.1) discard;
	
	/* Constant variables */
	colorDiffuse  = texture(uDiffuseSampler,  fUV).rgb;
	specularPower = texture(uSpecularSampler, fUV).rgb;
	emit          = texture(uEmitSampler,     fUV).rgb;
	n = normalize(getNormal());
	E = normalize(fEyeDirCameraspace);
	
	/* No light */
	color = vec3(0, 0, 0);
	
	/* Add emissive light */
	color += emit * colorDiffuse;
	
	/* Add ambient light */
	color += (1 - emit) * uAmbient * colorDiffuse;
	
	/* Add diffuse directional light */
	l = normalize(fDirLightDirCameraspace);
	diffuseAmount = clamp(dot(n, l), 0, 1);
	shadowValue = getShadowValue();
	color += (1 - emit) * diffuseAmount * colorDiffuse * uDirLightColor * uDirLightIntensity * shadowValue;
	
	/* Add specular directional light */
	R = reflect(-l, n);
	specularAmount = pow(clamp(dot(E, R), 0, 1), uModelSpecularExp);
	color += (1 - emit) * specularAmount * colorDiffuse * uDirLightColor * specularPower * uDirLightIntensity * shadowValue;
	
	/* Add diffuse point light */
	l = normalize(fPointLightDirCameraspace);
	diffuseAmount = clamp(dot(n, l), 0, 1);
	float distance = length(uPointLightPosition - fPositionWorldspace);
	attenuation = 1.f / (1.f + uPointLightSpread * pow(distance, 2));
	color += (1 - emit) * diffuseAmount * colorDiffuse * uPointLightColor * uPointLightIntensity * attenuation;
	
	/* Add specular point light */
	R = reflect(-l, n);
	specularAmount = pow(clamp(dot(E, R), 0, 1), uModelSpecularExp);
	color += (1 - emit) * specularAmount * colorDiffuse * uPointLightColor * specularPower * uPointLightIntensity * attenuation;
	
}
