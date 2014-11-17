#include "Buffer.hpp"

namespace GL = Engine::GL;



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

const char* GL::Buffer::getTargetName() const
{
	switch (target) {
		case GL_ARRAY_BUFFER: return "GL_ARRAY_BUFFER";
		//case GL_ATOMIC_COUNTER_BUFFER: return "GL_ATOMIC_COUNTER_BUFFER";
		case GL_COPY_READ_BUFFER: return "GL_COPY_READ_BUFFER";
		case GL_COPY_WRITE_BUFFER: return "GL_COPY_WRITE_BUFFER";
		//case GL_DISPATCH_INDIRECT_BUFFER: return "GL_DISPATCH_INDIRECT_BUFFER";
		//case GL_DRAW_INDIRECT_BUFFER: return "GL_DRAW_INDIRECT_BUFFER";
		case GL_ELEMENT_ARRAY_BUFFER: return "GL_ELEMENT_ARRAY_BUFFER";
		case GL_PIXEL_PACK_BUFFER: return "GL_PIXEL_PACK_BUFFER";
		case GL_PIXEL_UNPACK_BUFFER: return "GL_PIXEL_UNPACK_BUFFER";
		//case GL_QUERY_BUFFER: return "GL_QUERY_BUFFER";
		//case GL_SHADER_STORAGE_BUFFER: return "GL_SHADER_STORAGE_BUFFER";
		case GL_TEXTURE_BUFFER: return "GL_TEXTURE_BUFFER";
		case GL_TRANSFORM_FEEDBACK_BUFFER: return "GL_TRANSFORM_FEEDBACK_BUFFER";
		case GL_UNIFORM_BUFFER: return "GL_UNIFORM_BUFFER";
		default: return "INVALID_BUFFER_TARGET";
	}
}

const char* GL::Buffer::getUsageName() const
{
	switch (usage) {
		case GL_STREAM_DRAW: return "GL_STREAM_DRAW";
		case GL_STREAM_READ: return "GL_STREAM_READ";
		case GL_STREAM_COPY: return "GL_STREAM_COPY";
		case GL_STATIC_DRAW: return "GL_STATIC_DRAW";
		case GL_STATIC_READ: return "GL_STATIC_READ";
		case GL_STATIC_COPY: return "GL_STATIC_COPY";
		case GL_DYNAMIC_DRAW: return "GL_DYNAMIC_DRAW";
		case GL_DYNAMIC_READ: return "GL_DYNAMIC_READ";
		case GL_DYNAMIC_COPY: return "GL_DYNAMIC_COPY";
		default: return "INVALID_BUFFER_USAGE";
	}
}



/* Engine::GL::ElementBuffer */

GL::ElementBuffer::ElementBuffer(GLenum type, GLenum usage)
: Buffer(GL_ELEMENT_ARRAY_BUFFER, usage), type(type)
{}

GLenum GL::ElementBuffer::getType() const
{
	return type;
}

const char* GL::ElementBuffer::getTypeName() const
{
	switch(type) {
		case GL_UNSIGNED_BYTE: return "GL_UNSIGNED_BYTE";
		case GL_UNSIGNED_SHORT: return "GL_UNSIGNED_SHORT";
		case GL_UNSIGNED_INT: return "GL_UNSIGNED_INT";
		default: return "INVALID_ELEMENTBUFFER_TYPE";
	}
}

int GL::ElementBuffer::getTypeBits() const
{
	switch(type) {
		case GL_UNSIGNED_BYTE: return 8;
		case GL_UNSIGNED_SHORT: return 16;
		case GL_UNSIGNED_INT: return 32;
		default: return 0;
	}
}

void GL::ElementBuffer::drawPoints(GLsizei count, GLsizei start)
{
	glDrawElements(GL_POINTS, count, type, reinterpret_cast<const GLvoid*>(start));
}

void GL::ElementBuffer::drawLines(GLsizei count, GLsizei start)
{
	glDrawElements(GL_LINES, count, type, reinterpret_cast<const GLvoid*>(start));
}

void GL::ElementBuffer::drawTriangles(GLsizei count, GLsizei start)
{
	glDrawElements(GL_TRIANGLES, count, type, reinterpret_cast<const GLvoid*>(start));
}

void GL::ElementBuffer::drawLineStrip(GLsizei count, GLsizei start)
{
	glDrawElements(GL_LINE_STRIP, count, type, reinterpret_cast<const GLvoid*>(start));
}

void GL::ElementBuffer::drawTriangleStrip(GLsizei count, GLsizei start)
{
	glDrawElements(GL_TRIANGLE_STRIP, count, type, reinterpret_cast<const GLvoid*>(start));
}

void GL::ElementBuffer::draw(GLenum mode, GLsizei count, GLsizei start)
{
	glDrawElements(mode, count, type, reinterpret_cast<const GLvoid*>(start));
}



/* Engine::GL::ElementBuffer8 */

GL::ElementBuffer8::ElementBuffer8(GLenum usage)
: ElementBuffer(GL_UNSIGNED_BYTE, usage)
{}

GL::ElementBuffer8::ElementBuffer8(std::size_t count, const std::uint8_t *elements, GLenum usage)
: ElementBuffer(GL_UNSIGNED_BYTE, usage)
{
	this->elements(count, elements);
}

void GL::ElementBuffer8::elements(std::size_t count, const std::uint8_t *elements)
{
	data(sizeof(std::uint8_t) * count, static_cast<const GLvoid*>(elements));
}



/* Engine::GL::ElementBuffer16 */

GL::ElementBuffer16::ElementBuffer16(GLenum usage)
: ElementBuffer(GL_UNSIGNED_SHORT, usage)
{}

GL::ElementBuffer16::ElementBuffer16(std::size_t count, const std::uint16_t *elements, GLenum usage)
: ElementBuffer(GL_UNSIGNED_SHORT, usage)
{
	this->elements(count, elements);
}

void GL::ElementBuffer16::elements(std::size_t count, const std::uint16_t *elements)
{
	data(sizeof(std::uint16_t) * count, static_cast<const GLvoid*>(elements));
}



/* Engine::GL::ElementBuffer32 */

GL::ElementBuffer32::ElementBuffer32(GLenum usage)
: ElementBuffer(GL_UNSIGNED_INT, usage)
{}

GL::ElementBuffer32::ElementBuffer32(std::size_t count, const std::uint32_t *elements, GLenum usage)
: ElementBuffer(GL_UNSIGNED_INT, usage)
{
	this->elements(count, elements);
}

void GL::ElementBuffer32::elements(std::size_t count, const std::uint32_t *elements)
{
	data(sizeof(std::uint32_t) * count, static_cast<const GLvoid*>(elements));
}



/* Engine::GL::ArrayBuffer */

GL::ArrayBuffer::ArrayBuffer(GLenum usage)
: Buffer(GL_ARRAY_BUFFER, usage)
{}

GL::ArrayBuffer::ArrayBuffer(GLsizeiptr size, const GLvoid *data, GLenum usage)
: Buffer(GL_ARRAY_BUFFER, usage, size, data)
{}

void GL::ArrayBuffer::enableVertexAttribute(GLuint index, GLint count, GLenum type,
	GLsizei stride, GLsizei start)
{
	bind();
	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, count, type, GL_FALSE,
		stride, reinterpret_cast<const GLvoid*>(start));
	unbind();
}

void GL::ArrayBuffer::disableVertexAttribute(GLuint index)
{
	bind();
	glDisableVertexAttribArray(index);
	unbind();
}



/* Engine::GL::UniformBuffer */

GL::UniformBuffer::UniformBuffer(GLenum usage)
: Buffer(GL_UNIFORM_BUFFER, usage)
{}

GL::UniformBuffer::UniformBuffer(GLsizeiptr size, const GLvoid *data, GLenum usage)
: Buffer(GL_ARRAY_BUFFER, usage, size, data)
{}
