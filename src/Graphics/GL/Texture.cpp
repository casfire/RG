#include "Texture.hpp"

namespace GL = Graphics::GL;



/* Graphics::GL::Texture2D */

inline GLuint createTexture() {
	GLuint ID;
	glGenTextures(1, &ID);
	return ID;
}

GL::Texture2D::Texture2D()
: Object(createTexture())
{}

GL::Texture2D::Texture2D(GLint level, GLsizei width, GLsizei height,
	GLenum format, GLenum type, const GLvoid *data)
: Object(createTexture())
{
	image(level, width, height, format, type, data);
}

GL::Texture2D::~Texture2D()
{
	glDeleteTextures(1, &objectID);
}

void GL::Texture2D::image(GLint level, GLsizei width, GLsizei height,
	GLenum format, GLenum type, const GLvoid *data)
{
	bind();
	glTexImage2D(GL_TEXTURE_2D, level, GL_RGB, width, height, 0, format, type, data);
	unbind();
}

void GL::Texture2D::bind()
{
	glBindTexture(GL_TEXTURE_2D, objectID);
}

void GL::Texture2D::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
