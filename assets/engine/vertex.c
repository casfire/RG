#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 uv;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec4 tangent;

uniform mat4 uViewMat;
uniform mat4 uProjMat;
uniform mat4 uModelMat;
uniform mat4 uShadowVP;

uniform float uModelEmit;
uniform float uModelSpecularExp;

uniform vec3  uDirLightColor;
uniform float uDirLightIntensity;
uniform vec3  uDirLightDirection;

uniform vec3  uPointLightColor;
uniform float uPointLightIntensity;
uniform float uPointLightSpread;
uniform vec3  uPointLightPosition;

smooth out vec2 fUV;
smooth out vec3 fNormal;
smooth out vec3 fTangent;
smooth out vec3 fBinormal;
smooth out vec3 fPositionWorldspace;
smooth out vec3   fEyeDirCameraspace;
smooth out vec3 fDirLightDirCameraspace;
smooth out vec3 fPointLightDirCameraspace;
smooth out vec4 fShadowCoord;

void main() {
	
	mat4 matM   = uModelMat;            // Model to world
	mat4 matMV  = uViewMat * uModelMat; // Model to camera
	mat4 matMVP = uProjMat * matMV;     // Model to view
	mat4 matV   = uViewMat;             // World to camera
	
	gl_Position = matMVP * vec4(position, 1);
	
	vec3 position_worldspace  = (matM  * vec4(position,    1)).xyz;
	vec3   normal_cameraspace = (matMV * vec4(normal,      0)).xyz;
	vec3  tangent_cameraspace = (matMV * vec4(tangent.xyz, 0)).xyz;
	vec3 position_cameraspace = (matMV * vec4(position,    1)).xyz;
	vec3   eyedir_cameraspace = -position_cameraspace;
	
	fUV = uv;
	fNormal   = normal_cameraspace;
	fTangent  = tangent_cameraspace;
	fBinormal = normalize(cross(tangent_cameraspace, normal_cameraspace) * tangent.w);
	fPositionWorldspace  = position_worldspace;
	fEyeDirCameraspace   = eyedir_cameraspace;
	
	fDirLightDirCameraspace        = (matV * vec4(uDirLightDirection,  0)).xyz;
	vec3 pointlightpos_cameraspace = (matV * vec4(uPointLightPosition, 1)).xyz;
	fPointLightDirCameraspace      = pointlightpos_cameraspace + eyedir_cameraspace;
	
	fShadowCoord = uShadowVP * matM * vec4(position, 1);
}
