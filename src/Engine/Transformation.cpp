#include "Transformation.hpp"
#include <glm/gtx/transform.hpp>

namespace E = Engine;

E::Transformation::Transformation()
: position(0), scaling(1)
{}

E::Transformation::Transformation(const E::Transformation &t)
: position(t.position), scaling(t.scaling), rotation(t.rotation)
{}

glm::vec3 E::Transformation::getPosition() const
{
	return position;
}

void E::Transformation::resetPosition()
{
	position = glm::vec3(0);
}

void E::Transformation::setPosition(const glm::vec3 &position)
{
	this->position = position;
}

void E::Transformation::setPositionLocal(const glm::vec3 &position)
{
	this->position = rotation * position;
}

void E::Transformation::translate(const glm::vec3 &offset)
{
	this->position += offset;
}

void E::Transformation::translateLocal(const glm::vec3 &offset)
{
	this->position += rotation * offset;
}

glm::quat E::Transformation::getRotation() const
{
	return rotation;
}

void E::Transformation::resetRotation()
{
	rotation = glm::quat();
}

void E::Transformation::setRotation(const glm::quat &rotation)
{
	this->rotation = rotation;
}

void E::Transformation::rotate(const glm::quat &rotation)
{
	this->rotation = rotation * this->rotation;
}

void E::Transformation::rotate(const glm::vec3 &euler)
{
	this->rotation = glm::quat(euler) * this->rotation;
}

void E::Transformation::rotateLocal(const glm::quat &rotation)
{
	this->rotation *= rotation;
}

void E::Transformation::rotateLocal(const glm::vec3 &euler)
{
	this->rotation *= glm::quat(euler);
}

void E::Transformation::pitch(float angle)
{
	this->rotation = glm::quat(glm::vec3(angle, 0, 0)) * this->rotation;
}

void E::Transformation::yaw(float angle)
{
	this->rotation = glm::quat(glm::vec3(0, angle, 0)) * this->rotation;
}

void E::Transformation::roll(float angle)
{
	this->rotation = glm::quat(glm::vec3(0, 0, angle)) * this->rotation;
}

void E::Transformation::pitchLocal(float angle)
{
	this->rotation *= glm::quat(glm::vec3(angle, 0, 0));
}

void E::Transformation::yawLocal(float angle)
{
	this->rotation *= glm::quat(glm::vec3(0, angle, 0));
}

void E::Transformation::rollLocal(float angle)
{
	this->rotation *= glm::quat(glm::vec3(0, 0, angle));
}

float E::Transformation::getPitch() const
{
	return glm::pitch(rotation);
}

float E::Transformation::getYaw() const
{
	return glm::yaw(rotation);
}

float E::Transformation::getRoll() const
{
	return glm::roll(rotation);
}

glm::vec3 E::Transformation::getScale() const
{
	return scaling;
}

void E::Transformation::resetScale()
{
	scaling = glm::vec3(1);
}

void E::Transformation::setScale(const glm::vec3& scale)
{
	this->scaling = scale;
}

void E::Transformation::scale(const glm::vec3 &scale)
{
	this->scaling *= scale;
}

glm::mat4 E::Transformation::getMatrix() const
{
	return glm::translate(position)
		* glm::mat4_cast(rotation)
		* glm::scale(scaling);
}

glm::mat4 E::Transformation::getInverseMatrix() const
{
	return glm::scale(glm::vec3(1/scaling.x, 1/scaling.y, 1/scaling.z))
		* glm::mat4_cast(glm::inverse(rotation))
		* glm::translate(-position);
}

void E::Transformation::setTransformation(const E::Transformation &t)
{
	position = t.position;
	scaling = t.scaling;
	rotation = t.rotation;
}

void E::Transformation::setIdentity()
{
	position = glm::vec3(0);
	scaling = glm::vec3(1);
	rotation = glm::quat();
}
