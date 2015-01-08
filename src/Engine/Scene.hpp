#pragma once
#ifndef _ENGINE_SCENE_HPP_
#define _ENGINE_SCENE_HPP_

#include "Forward.hpp"
#include "Node.hpp"
#include "Camera.hpp"
#include "Light.hpp"

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
		
		GL::ProgramUniform *uModelMat;
		GL::ProgramUniform *uViewMat;
		GL::ProgramUniform *uProjMat;
		
		GL::ProgramUniform *uDiffuseSampler;
		GL::ProgramUniform *uNormalSampler;
		GL::ProgramUniform *uSpecularSampler;
		GL::ProgramUniform *uMaskSampler;
		
		GL::ProgramUniform *uAmbient;
		GL::ProgramUniform *uModelEmit;
		GL::ProgramUniform *uModelSpecularExp;
		
		GL::ProgramUniform *uDirLightColor;
		GL::ProgramUniform *uDirLightIntensity;
		GL::ProgramUniform *uDirLightDirection;
		
		GL::ProgramUniform *uPointLightColor;
		GL::ProgramUniform *uPointLightIntensity;
		GL::ProgramUniform *uPointLightSpread;
		GL::ProgramUniform *uPointLightPosition;
		
	};
	
	
	
} // namespace Engine

#endif // _ENGINE_SCENE_HPP_
