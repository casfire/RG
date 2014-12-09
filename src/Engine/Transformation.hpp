#pragma once
#ifndef _ENGINE_TRANSFORMATION_HPP_
#define _ENGINE_TRANSFORMATION_HPP_

#define GLM_FORCE_RADIANS
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Engine {
	
	
	
	class Transformation {
	public:
		
		/* Create identity transformation */
		Transformation();
		
		/* Get transformation matrix */
		glm::mat4 getMatrix() const;
		glm::mat4 getInverseMatrix() const;
		
		/* Set transformation */
		void setTransformation(const Transformation &t);
		void setIdentity();
		
		/* Scale */
		glm::vec3 getScale() const;
		void setScale(const glm::vec3 &scale);
		void scale(const glm::vec3 &scale);
		
		/* Position */
		glm::vec3 getPosition() const;
		void setPosition(const glm::vec3 &position);
		void setPositionRelative(const glm::vec3 &position);
		void setPositionRelativeInverse(const glm::vec3 &position);
		void translate(const glm::vec3 &offset);
		void translateRelative(const glm::vec3 &offset);
		void translateRelativeInverse(const glm::vec3 &offset);
		
		/* Rotation */
		glm::quat getRotation() const;
		void setRotation(const glm::quat &rotation);
		void rotate(const glm::quat &rotation);
		void rotateRelative(const glm::quat &rotation);
		
	private:
		
		glm::vec3 position, scaling;
		glm::quat rotation;
		
	};
	
	
	
} // namespace Engine

#endif // _ENGINE_TRANSFORMATION_HPP_
