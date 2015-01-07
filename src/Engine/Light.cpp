#include "Light.hpp"

using Engine::DirectionalLight;
using Engine::PointLight;



/* DirectionalLight */

DirectionalLight::DirectionalLight(MainEngine &engine)
: engine(engine)
{}

float DirectionalLight::getIntensity() const
{
	return intensity;
}

glm::vec3 DirectionalLight::getColor() const
{
	return color;
}

glm::vec3 DirectionalLight::getDirection() const
{
	return direction;
}

void DirectionalLight::setIntensity(float intensity)
{
	this->intensity = intensity;
}

void DirectionalLight::setColor(const glm::vec3 &color)
{
	this->color = color;
}

void DirectionalLight::setDirection(const glm::vec3 &direction)
{
	this->direction = direction;
}



/* PointLight */

PointLight::PointLight(MainEngine &engine)
: engine(engine)
{}

float PointLight::getIntensity() const
{
	return intensity;
}

float PointLight::getSpread() const
{
	return spread;
}


glm::vec3 PointLight::getColor() const
{
	return color;
}

glm::vec3 PointLight::getPosition() const
{
	return position;
}

void PointLight::setIntensity(float intensity)
{
	this->intensity = intensity;
}

void PointLight::setSpread(float spread)
{
	this->spread = spread;
}

void PointLight::setColor(const glm::vec3 &color)
{
	this->color = color;
}

void PointLight::setPosition(const glm::vec3 &position)
{
	this->position = position;
}
