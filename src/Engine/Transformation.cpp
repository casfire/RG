#include "Transformation.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

namespace E = Engine;

E::Transformation::Transformation()
: position(0), scaling(1)
{}

glm::mat4 E::Transformation::getMatrix() const
{
	return glm::translate(position)
		* glm::mat4_cast(rotation)
		* glm::scale(scaling);
}

glm::mat4 E::Transformation::getInverseMatrix() const
{
	return glm::scale(scaling)
		* glm::mat4_cast(rotation)
		* glm::translate(position);
}

void E::Transformation::setTransformation(const Transformation &t)
{
	scaling = t.scaling;
	position = t.position;
	rotation = t.rotation;
}

void E::Transformation::setIdentity()
{
	position = glm::vec3(0);
	scaling = glm::vec3(1);
	rotation = glm::quat();
}

glm::vec3 E::Transformation::getScale() const
{
	return scaling;
}

void E::Transformation::setScale(const glm::vec3 &scale)
{
	this->scaling = scale;
}

void E::Transformation::scale(const glm::vec3 &scale)
{
	this->scaling *= scale;
}

glm::vec3 E::Transformation::getPosition() const
{
	return position;
}

void E::Transformation::setPosition(const glm::vec3 &position)
{
	this->position = position;
}

void E::Transformation::setPositionRelative(const glm::vec3 &position)
{
	this->position = (rotation * position);
}

void E::Transformation::setPositionRelativeInverse(const glm::vec3 &position)
{
	this->position = (position * rotation);
}

void E::Transformation::translate(const glm::vec3 &offset)
{
	this->position += offset;
}

void E::Transformation::translateRelative(const glm::vec3 &offset)
{
	this->position += (rotation * offset);
}

void E::Transformation::translateRelativeInverse(const glm::vec3 &offset)
{
	this->position += (offset * rotation);
}

glm::quat E::Transformation::getRotation() const
{
	return rotation;
}

void E::Transformation::setRotation(const glm::quat &rotation)
{
	this->rotation = rotation;
}

void E::Transformation::rotate(const glm::quat &rotation)
{
	this->rotation = rotation * this->rotation;
}

void E::Transformation::rotateRelative(const glm::quat &rotation)
{
	this->rotation *= rotation;
}
