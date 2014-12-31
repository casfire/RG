#pragma once
#ifndef _ENGINE_SCENE_HPP_
#define _ENGINE_SCENE_HPP_

#include "Forward.hpp"
#include "Node.hpp"
#include "Camera.hpp"

namespace Engine {
	
	
	
	class Scene : public Node {
	public:
		
		/* Draw scene */
		void draw() override;
		
		/* Resize viewport */
		void resize(int width, int height);
		
		/* Get camera */
		Camera& getCamera();
		
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
		Asset::GLProgram *program;
		GL::ProgramUniform *uModelMat;
		GL::ProgramUniform *uViewMat;
		GL::ProgramUniform *uProjMat;
		
	};
	
	
	
} // namespace Engine

#endif // _ENGINE_SCENE_HPP_
