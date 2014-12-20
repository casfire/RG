#include "VAO.hpp"
#include "Buffer.hpp"

namespace GL = Engine::GL;

inline GLuint createVAO()
{
	GLuint ID;
	glGenVertexArrays(1, &ID);
	return ID;
}

GL::VAO::VAO()
: Object(createVAO()), type(GL_UNSIGNED_SHORT), count(0)
{}

GL::VAO::VAO(const GL::ElementBuffer &elements)
: Object(createVAO())
{
	set(elements);
}

GL::VAO::~VAO()
{
	glDeleteVertexArrays(1, &objectID);
}

void GL::VAO::bind() const
{
	glBindVertexArray(objectID);
}

void GL::VAO::unbind() const
{
	glBindVertexArray(0);
}

void GL::VAO::set(const GL::ElementBuffer &elements)
{
	bind();
	elements.bind();
	unbind();
	elements.unbind();
	type = elements.getType();
	count = elements.getCount();
}

void GL::VAO::enableAttribute(GLuint index)
{
	bind();
	glEnableVertexAttribArray(index);
	unbind();
}

void GL::VAO::disableAttribute(GLuint index)
{
	bind();
	glDisableVertexAttribArray(index);
	unbind();
}

void GL::VAO::attribute(
	GLuint index,
	const GL::ArrayBuffer &v,
	GLenum type, GLint size,
	GLsizei stride, GLsizei start,
	GLboolean normalized)
{
	bind();
	v.bind();
	glVertexAttribPointer(
		index, size, type, normalized,
		stride, reinterpret_cast<const GLvoid*>(start)
	);
	v.unbind();
	unbind();
}

void GL::VAO::attributeI(
	GLuint index,
	const GL::ArrayBuffer &v,
	GLenum type, GLint size,
	GLsizei stride, GLsizei start)
{
	bind();
	v.bind();
	glVertexAttribIPointer(
		index, size, type,
		stride, reinterpret_cast<const GLvoid*>(start)
	);
	v.unbind();
	unbind();
}

void GL::VAO::drawPoints() const
{
	draw(GL_POINTS);
}

void GL::VAO::drawLines() const
{
	draw(GL_LINES);
}

void GL::VAO::drawTriangles() const
{
	draw(GL_TRIANGLES);
}

void GL::VAO::drawLineStrip() const
{
	draw(GL_LINE_STRIP);
}

void GL::VAO::drawLineLoop() const
{
	draw(GL_LINE_LOOP);
}

void GL::VAO::drawTriangleStrip() const
{
	draw(GL_TRIANGLE_STRIP);
}

void GL::VAO::drawTriangleFan() const
{
	draw(GL_TRIANGLE_FAN);
}

void GL::VAO::draw(GLenum mode) const
{
	bind();
	glDrawElements(mode, count, type, nullptr);
	unbind();
}

void GL::VAO::draw(GLenum mode, GLsizei count, GLsizei offset) const
{
	bind();
	glDrawElements(mode, count, type, reinterpret_cast<const GLvoid*>(offset));
	unbind();
}
