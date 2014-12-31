#include "Camera.hpp"
#include "Scene.hpp"
#include <glm/gtx/transform.hpp>

using Engine::MainEngine;
using Engine::Node;
using Engine::Camera;
using Engine::Scene;
using Engine::Model;

Camera::Camera(Scene &scene)
: scene(scene)
{}

Camera::~Camera()
{}

glm::mat4 Camera::getViewMatrix() const
{
	return glm::mat4_cast(glm::inverse(rotation)) * glm::translate(-position);
}

glm::mat4 Camera::getProjectionMatrix() const
{
	return glm::perspective(fov, aspect, near, far);
}

void Camera::setProjection(float fov, float aspect, float near, float far)
{
	this->fov = fov;
	this->aspect = aspect;
	this->near = near;
	this->far = far;
	scene.updateProjection();
}

void Camera::setFov(float fov)
{
	setProjection(fov, aspect, near, far);
}

void Camera::setAspect(float aspect)
{
	setProjection(fov, aspect, near, far);
}

void Camera::setAspect(int windowX, int windowY)
{
	setAspect(static_cast<float>(windowX) / static_cast<float>(windowY));
}

void Camera::setClip(float near, float far)
{
	setProjection(fov, aspect, near, far);
}

float Camera::getFov() const
{
	return fov;
}

float Camera::getAspect() const
{
	return aspect;
}

float Camera::getNear() const
{
	return near;
}

float Camera::getFar() const
{
	return far;
}
