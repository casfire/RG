#include "Buffer.hpp"

namespace GL = Engine::GL;
using std::uint8_t;
using std::uint16_t;
using std::uint32_t;



/* Engine::GL::Buffer */

inline GLuint createBuffer()
{
	GLuint ID;
	glGenBuffers(1, &ID);
	return ID;
}

GL::Buffer::Buffer(GLenum target, GLenum usage)
: Object(createBuffer()), target(target), usage(usage)
{}

GL::Buffer::Buffer(GLenum target, GLenum usage, GLsizeiptr size, const GLvoid *data)
: Object(createBuffer()), target(target), usage(usage)
{
	this->data(size, data);
}

GL::Buffer::~Buffer()
{
	glDeleteBuffers(1, &objectID);
}

void GL::Buffer::data(GLsizeiptr size, const GLvoid *data)
{
	bind();
	glBufferData(target, size, data, usage);
	unbind();
}

void GL::Buffer::subData(GLintptr offset, GLsizeiptr size, const GLvoid *data)
{
	bind();
	glBufferSubData(target, offset, size, data);
	unbind();
}

void GL::Buffer::bind() const
{
	glBindBuffer(target, objectID);
}

void GL::Buffer::unbind() const
{
	glBindBuffer(target, 0);
}

GLenum GL::Buffer::getTarget() const
{
	return target;
}

GLenum GL::Buffer::getUsage() const
{
	return usage;
}



/* Engine::GL::ElementBuffer */

GL::ElementBuffer::ElementBuffer(GLenum type, GLenum usage)
: Buffer(GL_ELEMENT_ARRAY_BUFFER, usage), type(type), count(0)
{}

GLenum GL::ElementBuffer::getType() const
{
	return type;
}

GLsizei GL::ElementBuffer::getCount() const
{
	return count;
}



/* Engine::GL::ElementBuffer8 */

GL::ElementBuffer8::ElementBuffer8(GLenum usage)
: ElementBuffer(GL_UNSIGNED_BYTE, usage)
{}

GL::ElementBuffer8::ElementBuffer8(GLsizei count, const uint8_t *elements, GLenum usage)
: ElementBuffer(GL_UNSIGNED_BYTE, usage)
{
	this->elements(count, elements);
}

void GL::ElementBuffer8::elements(GLsizei count, const uint8_t *elements)
{
	data(sizeof(uint8_t) * count, static_cast<const GLvoid*>(elements));
	this->count = count;
}



/* Engine::GL::ElementBuffer16 */

GL::ElementBuffer16::ElementBuffer16(GLenum usage)
: ElementBuffer(GL_UNSIGNED_SHORT, usage)
{}

GL::ElementBuffer16::ElementBuffer16(GLsizei count, const uint16_t *elements, GLenum usage)
: ElementBuffer(GL_UNSIGNED_SHORT, usage)
{
	this->elements(count, elements);
}

void GL::ElementBuffer16::elements(GLsizei count, const uint16_t *elements)
{
	data(sizeof(uint16_t) * count, static_cast<const GLvoid*>(elements));
	this->count = count;
}



/* Engine::GL::ElementBuffer32 */

GL::ElementBuffer32::ElementBuffer32(GLenum usage)
: ElementBuffer(GL_UNSIGNED_INT, usage)
{}

GL::ElementBuffer32::ElementBuffer32(GLsizei count, const uint32_t *elements, GLenum usage)
: ElementBuffer(GL_UNSIGNED_INT, usage)
{
	this->elements(count, elements);
}

void GL::ElementBuffer32::elements(GLsizei count, const uint32_t *elements)
{
	data(sizeof(uint32_t) * count, static_cast<const GLvoid*>(elements));
	this->count = count;
}



/* Engine::GL::ArrayBuffer */

GL::ArrayBuffer::ArrayBuffer(GLenum usage)
: Buffer(GL_ARRAY_BUFFER, usage)
{}

GL::ArrayBuffer::ArrayBuffer(GLsizeiptr size, const GLvoid *data, GLenum usage)
: Buffer(GL_ARRAY_BUFFER, usage, size, data)
{}



/* Engine::GL::UniformBuffer */

GL::UniformBuffer::UniformBuffer(GLenum usage)
: Buffer(GL_UNIFORM_BUFFER, usage)
{}

GL::UniformBuffer::UniformBuffer(GLsizeiptr size, const GLvoid *data, GLenum usage)
: Buffer(GL_ARRAY_BUFFER, usage, size, data)
{}
