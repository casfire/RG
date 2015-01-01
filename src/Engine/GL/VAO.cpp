#include "VAO.hpp"
#include "Buffer.hpp"

using Engine::GL::VAO;

inline GLuint createVAO()
{
	GLuint ID;
	glGenVertexArrays(1, &ID);
	return ID;
}

VAO::VAO()
: Object(createVAO()), type(GL_UNSIGNED_SHORT), count(0), bytes(0)
{}

VAO::VAO(const ElementBuffer &elements)
: Object(createVAO())
{
	set(elements);
}

VAO::~VAO()
{
	glDeleteVertexArrays(1, &objectID);
}

void VAO::bind() const
{
	glBindVertexArray(objectID);
}

void VAO::unbind() const
{
	glBindVertexArray(0);
}

void VAO::set(const ElementBuffer &elements)
{
	bind();
	elements.bind();
	unbind();
	elements.unbind();
	type = elements.getType();
	bytes = elements.getBytes();
	count = elements.getCount();
}

void VAO::enableAttribute(GLuint index)
{
	bind();
	glEnableVertexAttribArray(index);
	unbind();
}

void VAO::disableAttribute(GLuint index)
{
	bind();
	glDisableVertexAttribArray(index);
	unbind();
}

void VAO::attribute(
	GLuint index,
	const ArrayBuffer &v,
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

void VAO::attributeI(
	GLuint index,
	const ArrayBuffer &v,
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

void VAO::drawPoints() const
{
	draw(GL_POINTS);
}

void VAO::drawLines() const
{
	draw(GL_LINES);
}

void VAO::drawTriangles() const
{
	draw(GL_TRIANGLES);
}

void VAO::drawLineStrip() const
{
	draw(GL_LINE_STRIP);
}

void VAO::drawLineLoop() const
{
	draw(GL_LINE_LOOP);
}

void VAO::drawTriangleStrip() const
{
	draw(GL_TRIANGLE_STRIP);
}

void VAO::drawTriangleFan() const
{
	draw(GL_TRIANGLE_FAN);
}

void VAO::draw(GLenum mode) const
{
	bind();
	glDrawElements(mode, count, type, nullptr);
	unbind();
}

void VAO::draw(GLenum mode, GLsizei count, GLsizei start) const
{
	bind();
	glDrawElements(mode, count, type, reinterpret_cast<const GLvoid*>(start * bytes));
	unbind();
}
