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
		int sceneWidth;
		int sceneHeight;
		
		/* Programs */
		Asset::GLProgram &program;
		Asset::GLProgram &program_depth;
		
		/* Shadow buffer */
		GL::FrameBuffer shadowFB;
		GL::Texture2D   shadowTexture;
		glm::mat4       shadowMatP;
		int   shadowSizeX;
		int   shadowSizeY;
		int   shadowSamplesX;
		int   shadowSamplesY;
		float shadowSamplesSpread;
		bool  shadowEnable;
		
		/* Helper methods */
		void drawEverything(GL::Uniform &uModelMat);
		void updateShadowTexelSize();
		
		/* Uniforms */
		GL::Uniform uModelMat;
		GL::Uniform uViewMat;
		GL::Uniform uProjMat;
		GL::Uniform uShadowVP;
		
		GL::Uniform uShadowDepthBias;
		GL::Uniform uShadowTexelSize;
		GL::Uniform uShadowSamples;
		
		GL::Uniform uDiffuseSampler;
		GL::Uniform uNormalSampler;
		GL::Uniform uSpecularSampler;
		GL::Uniform uMaskSampler;
		GL::Uniform uEmitSampler;
		GL::Uniform uShadowSampler;
		
		GL::Uniform uAmbient;
		GL::Uniform uModelSpecularExp;
		
		GL::Uniform uDirLightColor;
		GL::Uniform uDirLightIntensity;
		GL::Uniform uDirLightDirection;
		
		GL::Uniform uPointLightColor;
		GL::Uniform uPointLightIntensity;
		GL::Uniform uPointLightSpread;
		GL::Uniform uPointLightPosition;
		
		GL::Uniform uDepthM;
		GL::Uniform uDepthV;
		GL::Uniform uDepthP;
		
	};
	
	
	
} // namespace Engine

#endif // _ENGINE_SCENE_HPP_
