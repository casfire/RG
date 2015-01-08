#include "Transform.hpp"
#include <glm/gtx/transform.hpp>

using Engine::Transform;



/* Constructors */

Transform::Transform()
: position(0), scaling(1)
{}

Transform::Transform(const Transform &t)
: position(t.position), scaling(t.scaling), rotation(t.rotation)
{}



/* Local position */

glm::vec3 Transform::getPosition() const
{
	return position;
}

void Transform::setPosition(const glm::vec3 &pos)
{
	position = pos;
}

void Transform::translate(const glm::vec3 &offset)
{
	position += offset;
}

void Transform::translateX(float offset)
{
	position.x += offset;
}

void Transform::translateY(float offset)
{
	position.y += offset;
}

void Transform::translateZ(float offset)
{
	position.z += offset;
}



/* Relative position */

glm::vec3 Transform::getPosition(const Transform &rel) const
{
	return (position - rel.position) * rel.rotation * rel.scaling;
}

void Transform::setPosition(const glm::vec3 &pos, const Transform &rel)
{
	position = rel.rotation * (pos * rel.scaling);
}

void Transform::translate(const glm::vec3 &offset, const Transform &rel)
{
	position += rel.rotation * (offset * rel.scaling);
}

void Transform::translateX(float offset, const Transform &rel)
{
	translate(glm::vec3(offset, 0, 0), rel);
}

void Transform::translateY(float offset, const Transform &rel)
{
	translate(glm::vec3(0, offset, 0), rel);
}

void Transform::translateZ(float offset, const Transform &rel)
{
	translate(glm::vec3(0, 0, offset), rel);
}



/* Local rotation */

glm::quat Transform::getRotation() const
{
	return rotation;
}

void Transform::setRotation(const glm::quat &rot)
{
	rotation = rot;
}

void Transform::rotate(const glm::quat &rot)
{
	rotation = rot * rotation;
}

void Transform::rotate(const glm::vec3 &euler)
{
	rotation = glm::quat(euler) * rotation;
}

void Transform::rotateX(float angle)
{
	rotation = glm::quat(glm::vec3(angle, 0, 0)) * rotation;
}

void Transform::rotateY(float angle)
{
	rotation = glm::quat(glm::vec3(0, angle, 0)) * rotation;
}

void Transform::rotateZ(float angle)
{
	rotation = glm::quat(glm::vec3(0, 0, angle)) * rotation;
}

void Transform::pitch(float angle)
{
	rotation = glm::quat(glm::vec3(angle, 0, 0)) * rotation;
}

void Transform::yaw(float angle)
{
	rotation = glm::quat(glm::vec3(0, angle, 0)) * rotation;
}

void Transform::roll(float angle)
{
	rotation = glm::quat(glm::vec3(0, 0, angle)) * rotation;
}

float Transform::getPitch() const
{
	return glm::pitch(rotation);
}

float Transform::getYaw() const
{
	return glm::yaw(rotation);
}

float Transform::getRoll() const
{
	return glm::roll(rotation);
}



/* Relative rotation */

glm::quat Transform::getRotation(const Transform &rel) const
{
	return rotation * glm::inverse(rel.rotation);
}

void Transform::setRotation(const glm::quat &rot, const Transform &rel)
{
	rotation = rel.rotation * rot * glm::inverse(rel.rotation);
}

void Transform::rotate(const glm::quat &rot, const Transform &rel)
{
	rotation = rel.rotation * rot * glm::inverse(rel.rotation) * rotation;
}

void Transform::rotate(const glm::vec3 &euler, const Transform &rel)
{
	rotate(glm::quat(euler), rel);
}

void Transform::rotateX(float angle, const Transform &rel)
{
	rotate(glm::quat(glm::vec3(angle, 0, 0)), rel);
}

void Transform::rotateY(float angle, const Transform &rel)
{
	rotate(glm::quat(glm::vec3(0, angle, 0)), rel);
}

void Transform::rotateZ(float angle, const Transform &rel)
{
	rotate(glm::quat(glm::vec3(0, 0, angle)), rel);
}

void Transform::pitch(float angle, const Transform &rel)
{
	rotate(glm::quat(glm::vec3(angle, 0, 0)), rel);
}

void Transform::yaw(float angle, const Transform &rel)
{
	rotate(glm::quat(glm::vec3(0, angle, 0)), rel);
}

void Transform::roll(float angle, const Transform &rel)
{
	rotate(glm::quat(glm::vec3(0, 0, angle)), rel);
}

float Transform::getPitch(const Transform &rel) const
{
	return glm::pitch(getRotation(rel));
}

float Transform::getYaw(const Transform &rel) const
{
	return glm::yaw(getRotation(rel));
}

float Transform::getRoll(const Transform &rel) const
{
	return glm::roll(getRotation(rel));
}



/* Local scale */

glm::vec3 Transform::getScale() const
{
	return scaling;
}

void Transform::setScale(const glm::vec3 &scale)
{
	scaling = scale;
}

void Transform::scale(const glm::vec3 &scale)
{
	scaling *= scale;
}



/* Relative scale */

glm::vec3 Transform::getScale(const Transform &rel) const
{
	// TODO
	(void) rel;
	return getScale();
}

void Transform::setScale(const glm::vec3 &scale, const Transform &rel)
{
	// TODO
	(void) rel;
	setScale(scale);
}

void Transform::scale(const glm::vec3 &scale, const Transform &rel)
{
	// TODO
	(void) rel;
	this->scale(scale);
}



/* Get local transformation matrix */

glm::mat4 Transform::getMatrix() const
{
	return glm::translate(position)
		* glm::mat4_cast(rotation)
		* glm::scale(scaling);
}

glm::mat4 Transform::getInverseMatrix() const
{
	return glm::scale(glm::vec3(1/scaling.x, 1/scaling.y, 1/scaling.z))
		* glm::mat4_cast(glm::inverse(rotation))
		* glm::translate(-position);
}



/* Set local transformation */

void Transform::setTransformation(const Transform &t)
{
	position = t.position;
	scaling = t.scaling;
	rotation = t.rotation;
}

void Transform::setIdentity()
{
	position = glm::vec3(0);
	scaling = glm::vec3(1);
	rotation = glm::quat();
}
