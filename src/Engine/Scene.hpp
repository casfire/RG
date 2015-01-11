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
		
		/* Uniforms */
		GL::ProgramUniform uModelMat;
		GL::ProgramUniform uViewMat;
		GL::ProgramUniform uProjMat;
		GL::ProgramUniform uShadowVP;
		
		GL::ProgramUniform uShadowDepthBias;
		GL::ProgramUniform uShadowTexelSize;
		GL::ProgramUniform uShadowSamples;
		
		GL::ProgramUniform uDiffuseSampler;
		GL::ProgramUniform uNormalSampler;
		GL::ProgramUniform uSpecularSampler;
		GL::ProgramUniform uMaskSampler;
		GL::ProgramUniform uEmitSampler;
		GL::ProgramUniform uShadowSampler;
		
		GL::ProgramUniform uAmbient;
		GL::ProgramUniform uModelSpecularExp;
		
		GL::ProgramUniform uDirLightColor;
		GL::ProgramUniform uDirLightIntensity;
		GL::ProgramUniform uDirLightDirection;
		
		GL::ProgramUniform uPointLightColor;
		GL::ProgramUniform uPointLightIntensity;
		GL::ProgramUniform uPointLightSpread;
		GL::ProgramUniform uPointLightPosition;
		
		GL::ProgramUniform uDepthM;
		GL::ProgramUniform uDepthV;
		GL::ProgramUniform uDepthP;
		
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
		
		void drawEverything(GL::ProgramUniform &uModelMat);
		void updateShadowTexelSize();
		
	};
	
	
	
} // namespace Engine

#endif // _ENGINE_SCENE_HPP_
