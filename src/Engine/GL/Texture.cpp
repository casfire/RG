#include "Texture.hpp"

namespace GL = Engine::GL;



inline GLint getInternalFormat(GLenum format, bool compress)
{
	if (!compress) return format;
	switch (format) {
	case GL_RED:
		return GL_COMPRESSED_RED;
	case GL_RG:
		return GL_COMPRESSED_RG;
	case GL_RGB:
	case GL_BGR:
		return GL_COMPRESSED_RGB;
	case GL_RGBA:
	case GL_BGRA:
		return GL_COMPRESSED_RGBA;
	default:
		return format;
	}
}

/* Engine::GL::Texture */

inline GLuint createTexture()
{
	GLuint ID;
	glGenTextures(1, &ID);
	return ID;
}

GL::Texture::Texture(GLenum target)
: Object(createTexture()), target(target)
{}

GL::Texture::~Texture()
{
	glDeleteTextures(1, &objectID);
}

void GL::Texture::bind() const
{
	glBindTexture(target, objectID);
}

void GL::Texture::unbind() const
{
	glBindTexture(target, objectID);
}



/* Engine::GL::Texture1D */

GL::Texture1D::Texture1D()
: Texture(GL_TEXTURE_1D)
{}

GL::Texture1D::Texture1D(
	GLsizei width,
	GLenum format, GLenum type, const GLvoid *data,
	bool compress)
: Texture(GL_TEXTURE_1D)
{
	image(width, format, type, data, compress);
}

void GL::Texture1D::image(
	GLsizei width,
	GLenum format, GLenum type, const GLvoid *data,
	bool compress)
{
	bind();
	glTexImage1D(
		target, 0, getInternalFormat(format, compress),
		width, 0, format, type, data
	);
	unbind();
}



/* Engine::GL::Texture2D */

GL::Texture2D::Texture2D()
: Texture(GL_TEXTURE_2D)
{}

GL::Texture2D::Texture2D(
	GLsizei width, GLsizei height,
	GLenum format, GLenum type, const GLvoid *data,
	bool compress)
: Texture(GL_TEXTURE_2D)
{
	image(width, height, format, type, data, compress);
}

void GL::Texture2D::image(
	GLsizei width, GLsizei height,
	GLenum format, GLenum type, const GLvoid *data,
	bool compress)
{
	bind();
	glTexImage2D(
		target, 0, getInternalFormat(format, compress),
		width, height, 0, format, type, data
	);
	unbind();
}



/* Engine::GL::Texture3D */

GL::Texture3D::Texture3D()
: Texture(GL_TEXTURE_3D)
{}

GL::Texture3D::Texture3D(
	GLsizei width, GLsizei height, GLsizei depth,
	GLenum format, GLenum type, const GLvoid *data,
	bool compress)
: Texture(GL_TEXTURE_3D)
{
	image(width, height, depth, format, type, data, compress);
}

void GL::Texture3D::image(
	GLsizei width, GLsizei height, GLsizei depth,
	GLenum format, GLenum type, const GLvoid *data,
	bool compress)
{
	bind();
	glTexImage3D(
		target, 0, getInternalFormat(format, compress),
		width, height, depth, 0, format, type, data
	);
	unbind();
}
