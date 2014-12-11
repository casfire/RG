#pragma once
#ifndef _ENGINE_CAMERA_HPP_
#define _ENGINE_CAMERA_HPP_

#include "Transformation.hpp"
#include <glm/mat4x4.hpp>

namespace Engine {
	
	
	
	/* 3D Camera */
	class Camera : public Transformation {
	public:
		
		/* Create a new camera */
		Camera(float fov = 1.570796f, float aspect = 1.f,
			float near = 0.1f, float far = 10000.f);
		Camera(const Camera &cam);
		
		/* Build matrices */
		glm::mat4 getViewMatrix() const;
		glm::mat4 getProjectionMatrix() const;
		
		/* Projection */
		void setProjection(float fov, float aspect, float near, float far);
		void setFov(float fov);
		void setAspect(float aspect);
		void setAspect(int windowX, int windowY);
		void setClip(float near, float far);
		float getFov() const;
		float getAspect() const;
		float getNear() const;
		float getFar() const;
		
	private:
		
		float fov;
		float aspect;
		float near;
		float far;
		
	};
	
	
	
} // namespace Engine

#endif // _ENGINE_CAMERA_HPP_
