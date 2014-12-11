#pragma once
#ifndef _ENGINE_TRANSFORMATION_HPP_
#define _ENGINE_TRANSFORMATION_HPP_

#define GLM_FORCE_RADIANS
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Engine {
	
	
	
	/* Base class for all transformationable objects */
	class Transformation {
	public:
		
		/* Create transformation */
		Transformation();
		Transformation(const Transformation &t);
		
		/* Position */
		glm::vec3 getPosition() const;
		void resetPosition();
		void setPosition	 (const glm::vec3 &position);
		void setPositionLocal(const glm::vec3 &position);
		void translate	   (const glm::vec3 &offset);
		void translateLocal  (const glm::vec3 &offset);
		
		/* Rotation */
		glm::quat getRotation() const;
		void resetRotation();
		void setRotation(const glm::quat &rotation);
		void rotate	 (const glm::quat &rotation);
		void rotate	 (const glm::vec3 &euler);
		void rotateLocal(const glm::quat &rotation);
		void rotateLocal(const glm::vec3 &euler);
		void pitch(float angle);
		void yaw  (float angle);
		void roll (float angle);
		void pitchLocal(float angle);
		void yawLocal  (float angle);
		void rollLocal (float angle);
		float getPitch() const;
		float getYaw()   const;
		float getRoll()  const;
		
		/* Scale */
		glm::vec3 getScale() const;
		void resetScale();
		void setScale(const glm::vec3 &scale);
		void scale   (const glm::vec3 &scale);
		
		/* Get transformation matrix */
		glm::mat4 getMatrix() const;
		glm::mat4 getInverseMatrix() const;
		
		/* Set transformation */
		void setTransformation(const Transformation &t);
		void setIdentity();
		
	protected:
		
		glm::vec3 position, scaling;
		glm::quat rotation;
		
	};
	
	
	
} // namespace Engine

#endif // _ENGINE_TRANSFORMATION_HPP_
