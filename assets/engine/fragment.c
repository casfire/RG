#version 330

smooth in vec2 fUV;
smooth in vec3 fNormal;
smooth in vec3 fTangent;
smooth in vec3 fBinormal;
smooth in vec3 fPositionWorldspace;
smooth in vec3   fEyeDirCameraspace;
smooth in vec3 fLightDirCameraspace;

uniform sampler2D uDiffuseSampler;
uniform sampler2D uNormalSampler;
uniform vec3 uLightPos;

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
	
	vec3  lightColor = vec3(1, 1, 1);
	float lightPower = 30.0;
	float specularSpread = 80;
	float ambientAmount = 0.2;
	float specularPower = 20.0;
	
	vec2 uv = vec2(fUV.x, -fUV.y);
	vec3 colorDiffuse  = texture(uDiffuseSampler, uv).rgb;
	vec3 colorSpecular = colorDiffuse;
	
	float distance = pow(length(uLightPos - fPositionWorldspace), 2);
	vec3 n = normalize(getNormal());
	vec3 l = normalize(fLightDirCameraspace);
	float diffuseAmount = clamp(dot(n, l), 0, 1);
	
	vec3 E = normalize(fEyeDirCameraspace);
	vec3 R = reflect(-l, n);
	float specularAmount = pow(clamp(dot(E, R), 0, 1), specularSpread);
	
	color = 
		+ ambientAmount  * colorDiffuse
		+ diffuseAmount  * colorDiffuse  * lightColor * lightPower    / distance
		+ specularAmount * colorSpecular * lightColor * specularPower / distance;
	
}
