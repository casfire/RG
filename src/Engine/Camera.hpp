#pragma once
#ifndef _ENGINE_CAMERA_HPP_
#define _ENGINE_CAMERA_HPP_

#include "Forward.hpp"
#include "Node.hpp"

namespace Engine {
	
	
	
	class Camera : public Node {
	public:
		
		/* Build matrices */
		glm::mat4 getViewMatrix() const;
		glm::mat4 getProjectionMatrix() const;
		
		/* Get projection parameters */
		float getFov() const;
		float getAspect() const;
		float getNear() const;
		float getFar() const;
		
		/* Set projection parameters */
		void setProjection(float fov, float aspect, float near, float far);
		void setFov(float fov);
		void setAspect(float aspect);
		void setAspect(int windowX, int windowY);
		void setClip(float near, float far);
		
	private:
		
		friend class MainEngine;
		friend class Node;
		friend class Scene;
		friend class Model;
		
		Camera(Scene &scene);
		~Camera();
		
		Scene &scene;
		float fov     = 1.570796f;
		float aspect  = 1.f;
		float near    = 0.1f;
		float far     = 10000.f;
		
	};
	
	
	
} // namespace Engine

#endif // _ENGINE_CAMERA_HPP_
