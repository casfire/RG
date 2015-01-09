#pragma once
#ifndef _ENGINE_SCENE_HPP_
#define _ENGINE_SCENE_HPP_

#include "Forward.hpp"
#include "Node.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "GL/GL.hpp"

namespace Engine {
	
	
	
	class Scene : public Node {
	public:
		
		/* Draw scene */
		void draw();
		
		/* Resize viewport */
		void resize(int width, int height);
		
		/* Get camera */
		Camera& getCamera();
		
		/* Get directional light */
		DirectionalLight& getDirectionalLight();
		
		/* Get point light */
		PointLight& getPointLight();
		
		/* Set ambient [0, 1] */
		void setAmbient(float amount);
		
		/* Set shadow projection */
		void setShadowProjection(
			float left,   float right,
			float bottom, float top,
			float near,   float far
		);
		
		/* Set shadow depth bias */
		void setShadowDepthBias(float bias);
		
		/* Set shadow texture size */
		void setShadowSize(int x, int y);
		
		/* Enable/Disable shadows */
		void enableShadows();
		void disableShadows();
		
		/* Set shadow sample size */
		void setShadowSamples(int x, int y, float spread);
		
	private:
		
		friend class MainEngine;
		friend class Node;
		friend class Camera;
		friend class Model;
		
		void updateProjection();
		Scene(MainEngine &engine);
		~Scene();
		
		MainEngine &engine;
		Camera camera;
		DirectionalLight lightDir;
		PointLight       lightPoint;
		Asset::GLProgram *program;
		int width, height;
		
		GL::ProgramUniform *uModelMat;
		GL::ProgramUniform *uViewMat;
		GL::ProgramUniform *uProjMat;
		GL::ProgramUniform *uDepthBiasVP;
		GL::ProgramUniform *uDepthBias;
		GL::ProgramUniform *uDepthTexelSize;
		GL::ProgramUniform *uShadowSamples;
		
		GL::ProgramUniform *uDiffuseSampler;
		GL::ProgramUniform *uNormalSampler;
		GL::ProgramUniform *uSpecularSampler;
		GL::ProgramUniform *uMaskSampler;
		GL::ProgramUniform *uEmitSampler;
		GL::ProgramUniform *uShadowSampler;
		
		GL::ProgramUniform *uAmbient;
		GL::ProgramUniform *uModelSpecularExp;
		
		GL::ProgramUniform *uDirLightColor;
		GL::ProgramUniform *uDirLightIntensity;
		GL::ProgramUniform *uDirLightDirection;
		
		GL::ProgramUniform *uPointLightColor;
		GL::ProgramUniform *uPointLightIntensity;
		GL::ProgramUniform *uPointLightSpread;
		GL::ProgramUniform *uPointLightPosition;
		
		GL::FrameBuffer    shadowFB;
		GL::Texture2D      shadowDepth;
		Asset::GLProgram   *program_depth;
		GL::ProgramUniform *uDepthVP;
		GL::ProgramUniform *uDepthM;
		glm::mat4 depthBiasMatrix;
		glm::mat4 depthProjectionMatrix;
		int shadowSizeX, shadowSizeY;
		int shadowSamplesX, shadowSamplesY;
		float shadowSamplesSpread;
		bool shadowEnable;
		
		void drawEverything(GL::ProgramUniform *uModelMat);
		
	};
	
	
	
} // namespace Engine

#endif // _ENGINE_SCENE_HPP_
