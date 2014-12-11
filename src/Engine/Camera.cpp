#include "Camera.hpp"
#include <glm/gtx/transform.hpp>

namespace E = Engine;

E::Camera::Camera(float fov, float aspect, float near, float far)
: fov(fov), aspect(aspect), near(near), far(far)
{}

E::Camera::Camera(const Camera &cam)
: Transformation(cam), fov(cam.fov), aspect(cam.aspect), near(cam.near), far(cam.far)
{}

glm::mat4 E::Camera::getViewMatrix() const
{
	return glm::mat4_cast(glm::inverse(rotation)) * glm::translate(-position);
}

glm::mat4 E::Camera::getProjectionMatrix() const
{
	return glm::perspective(fov, aspect, near, far);
}

void E::Camera::setProjection(float fov, float aspect, float near, float far)
{
	this->fov = fov;
	this->aspect = aspect;
	this->near = near;
	this->far = far;
}

void E::Camera::setFov(float fov)
{
	this->fov = fov;
}

void E::Camera::setAspect(float aspect)
{
	this->aspect = aspect;
}

void E::Camera::setAspect(int windowX, int windowY)
{
	this->aspect = static_cast<float>(windowX) / static_cast<float>(windowY);
}

void E::Camera::setClip(float near, float far)
{
	this->near = near;
	this->far = far;
}

float E::Camera::getFov() const
{
	return fov;
}

float E::Camera::getAspect() const
{
	return aspect;
}

float E::Camera::getNear() const
{
	return near;
}

float E::Camera::getFar() const
{
	return far;
}
