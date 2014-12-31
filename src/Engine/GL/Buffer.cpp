#include "Buffer.hpp"

using Engine::GL::Buffer;
using Engine::GL::ElementBuffer;
using Engine::GL::ElementBuffer8;
using Engine::GL::ElementBuffer16;
using Engine::GL::ElementBuffer32;
using Engine::GL::ArrayBuffer;
using Engine::GL::UniformBuffer;
using std::uint8_t;
using std::uint16_t;
using std::uint32_t;



/* Buffer */

inline GLuint createBuffer()
{
	GLuint ID;
	glGenBuffers(1, &ID);
	return ID;
}

Buffer::Buffer(GLenum target, GLenum usage)
: Object(createBuffer()), target(target), usage(usage)
{}

Buffer::Buffer(GLenum target, GLenum usage, GLsizeiptr size, const GLvoid *data)
: Object(createBuffer()), target(target), usage(usage)
{
	this->data(size, data);
}

Buffer::~Buffer()
{
	glDeleteBuffers(1, &objectID);
}

void Buffer::data(GLsizeiptr size, const GLvoid *data)
{
	bind();
	glBufferData(target, size, data, usage);
	unbind();
}

void Buffer::subData(GLintptr offset, GLsizeiptr size, const GLvoid *data)
{
	bind();
	glBufferSubData(target, offset, size, data);
	unbind();
}

void Buffer::bind() const
{
	glBindBuffer(target, objectID);
}

void Buffer::unbind() const
{
	glBindBuffer(target, 0);
}

GLenum Buffer::getTarget() const
{
	return target;
}

GLenum Buffer::getUsage() const
{
	return usage;
}



/* ElementBuffer */

ElementBuffer::ElementBuffer(GLenum type, GLenum usage)
: Buffer(GL_ELEMENT_ARRAY_BUFFER, usage), type(type), count(0)
{}

GLenum ElementBuffer::getType() const
{
	return type;
}

GLsizei ElementBuffer::getCount() const
{
	return count;
}



/* ElementBuffer8 */

ElementBuffer8::ElementBuffer8(GLenum usage)
: ElementBuffer(GL_UNSIGNED_BYTE, usage)
{}

ElementBuffer8::ElementBuffer8(GLsizei count, const uint8_t *elements, GLenum usage)
: ElementBuffer(GL_UNSIGNED_BYTE, usage)
{
	this->elements(count, elements);
}

void ElementBuffer8::elements(GLsizei count, const uint8_t *elements)
{
	data(sizeof(uint8_t) * count, static_cast<const GLvoid*>(elements));
	this->count = count;
}



/* ElementBuffer16 */

ElementBuffer16::ElementBuffer16(GLenum usage)
: ElementBuffer(GL_UNSIGNED_SHORT, usage)
{}

ElementBuffer16::ElementBuffer16(GLsizei count, const uint16_t *elements, GLenum usage)
: ElementBuffer(GL_UNSIGNED_SHORT, usage)
{
	this->elements(count, elements);
}

void ElementBuffer16::elements(GLsizei count, const uint16_t *elements)
{
	data(sizeof(uint16_t) * count, static_cast<const GLvoid*>(elements));
	this->count = count;
}



/* ElementBuffer32 */

ElementBuffer32::ElementBuffer32(GLenum usage)
: ElementBuffer(GL_UNSIGNED_INT, usage)
{}

ElementBuffer32::ElementBuffer32(GLsizei count, const uint32_t *elements, GLenum usage)
: ElementBuffer(GL_UNSIGNED_INT, usage)
{
	this->elements(count, elements);
}

void ElementBuffer32::elements(GLsizei count, const uint32_t *elements)
{
	data(sizeof(uint32_t) * count, static_cast<const GLvoid*>(elements));
	this->count = count;
}



/* ArrayBuffer */

ArrayBuffer::ArrayBuffer(GLenum usage)
: Buffer(GL_ARRAY_BUFFER, usage)
{}

ArrayBuffer::ArrayBuffer(GLsizeiptr size, const GLvoid *data, GLenum usage)
: Buffer(GL_ARRAY_BUFFER, usage, size, data)
{}



/* UniformBuffer */

UniformBuffer::UniformBuffer(GLenum usage)
: Buffer(GL_UNIFORM_BUFFER, usage)
{}

UniformBuffer::UniformBuffer(GLsizeiptr size, const GLvoid *data, GLenum usage)
: Buffer(GL_ARRAY_BUFFER, usage, size, data)
{}
