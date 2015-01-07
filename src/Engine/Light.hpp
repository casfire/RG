#pragma once
#ifndef _ENGINE_LIGHT_HPP_
#define _ENGINE_LIGHT_HPP_

#include "Forward.hpp"
#include <glm/vec3.hpp>

namespace Engine {
	
	
	
	class DirectionalLight {
	public:
		
		/* Getters */
		float     getIntensity() const;
		glm::vec3 getColor()     const;
		glm::vec3 getDirection() const;
		
		/* Setters */
		void setIntensity(float intensity);
		void setColor    (const glm::vec3 &color);
		void setDirection(const glm::vec3 &direction);
		
	private:
		
		friend class MainEngine;
		friend class Scene;
		DirectionalLight(MainEngine &engine);
		MainEngine& engine;
		float intensity;
		glm::vec3 color;
		glm::vec3 direction;
		
	};
	
	
	
	class PointLight {
	public:
		
		/* Getters */
		float     getIntensity() const;
		float     getSpread()    const;
		glm::vec3 getColor()     const;
		glm::vec3 getPosition()  const;
		
		/* Setters */
		void setIntensity(float intensity);
		void setSpread   (float spread);
		void setColor    (const glm::vec3 &color);
		void setPosition (const glm::vec3 &position);
		
	private:
		
		friend class MainEngine;
		friend class Scene;
		PointLight(MainEngine &engine);
		MainEngine& engine;
		float intensity, spread;
		glm::vec3 color;
		glm::vec3 position;
		
	};
	
	
	
} // namespace Engine

#endif // _ENGINE_LIGHT_HPP_
