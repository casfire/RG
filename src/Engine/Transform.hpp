#pragma once
#ifndef _ENGINE_TRANSFORM_HPP_
#define _ENGINE_TRANSFORM_HPP_

#include "Forward.hpp"
#define GLM_FORCE_RADIANS
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Engine {
	
	
	
	/* Base class for all transformationable objects */
	class Transform {
	public:
		
		/* Create transformation */
		Transform();
		Transform(const Transform &t);
		
		/* Local position */
		glm::vec3 getPosition() const;
		void setPosition(const glm::vec3 &pos);
		void translate  (const glm::vec3 &offset);
		
		/* Relative position */
		glm::vec3 getPosition(const Transform &rel) const;
		void setPosition(const glm::vec3 &pos,    const Transform &rel);
		void translate  (const glm::vec3 &offset, const Transform &rel);
		
		/* Local rotation */
		glm::quat getRotation() const;
		void setRotation(const glm::quat &rot);
		void rotate	    (const glm::quat &rot);
		void rotate	    (const glm::vec3 &euler);
		void pitch      (float angle);
		void yaw        (float angle);
		void roll       (float angle);
		float getPitch() const;
		float getYaw()   const;
		float getRoll()  const;
		
		/* Relative rotation */
		glm::quat getRotation(const Transform &rel) const;
		void setRotation(const glm::quat &rot,   const Transform &rel);
		void rotate	    (const glm::quat &rot,   const Transform &rel);
		void rotate	    (const glm::vec3 &euler, const Transform &rel);
		void pitch      (float angle, const Transform &rel);
		void yaw        (float angle, const Transform &rel);
		void roll       (float angle, const Transform &rel);
		float getPitch(const Transform &rel) const;
		float getYaw  (const Transform &rel) const;
		float getRoll (const Transform &rel) const;
		
		/* Local scale */
		glm::vec3 getScale() const;
		void setScale(const glm::vec3 &scale);
		void scale   (const glm::vec3 &scale);
		
		/* Relative scale */
		glm::vec3 getScale(const Transform &rel) const;
		void setScale(const glm::vec3 &scale, const Transform &rel);
		void scale   (const glm::vec3 &scale, const Transform &rel);
		
		/* Get local transformation matrix */
		glm::mat4 getMatrix() const;
		glm::mat4 getInverseMatrix() const;
		
		/* Set local transformation */
		void setTransformation(const Transform &t);
		void setIdentity();
		
	protected:
		
		glm::vec3 position, scaling;
		glm::quat rotation;
		
	};
	
	
	
} // namespace Engine

#endif // _ENGINE_TRANSFORM_HPP_
