#include "Texture.hpp"

using Engine::GL::Texture;
using Engine::GL::Texture1D;
using Engine::GL::Texture2D;
using Engine::GL::Texture3D;

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



/* Texture */

inline GLuint createTexture()
{
	GLuint ID;
	glGenTextures(1, &ID);
	return ID;
}

Texture::Texture(GLenum target)
: Object(createTexture()), target(target)
{}

Texture::~Texture()
{
	glDeleteTextures(1, &objectID);
}

void Texture::bind() const
{
	glBindTexture(target, objectID);
}

void Texture::unbind() const
{
	glBindTexture(target, objectID);
}



/* Texture1D */

Texture1D::Texture1D()
: Texture(GL_TEXTURE_1D)
{}

Texture1D::Texture1D(
	GLsizei width,
	GLenum format, GLenum type, const GLvoid *data, bool compress)
: Texture(GL_TEXTURE_1D)
{
	setPixels(width, format, type, data, compress);
}

void Texture1D::setPixels(
	GLsizei width,
	GLenum format, GLenum type, const GLvoid *data, bool compress)
{
	bind();
	glTexImage1D(
		target, 0, getInternalFormat(format, compress),
		width, 0, format, type, data
	);
	unbind();
}



/* Texture2D */

Texture2D::Texture2D()
: Texture(GL_TEXTURE_2D)
{}

Texture2D::Texture2D(
	GLsizei width, GLsizei height,
	GLenum format, GLenum type, const GLvoid *data, bool compress)
: Texture(GL_TEXTURE_2D)
{
	setPixels(width, height, format, type, data, compress);
}

void Texture2D::setPixels(
	GLsizei width, GLsizei height,
	GLenum format, GLenum type, const GLvoid *data, bool compress)
{
	bind();
	glTexImage2D(
		target, 0, getInternalFormat(format, compress),
		width, height, 0, format, type, data
	);
	unbind();
}



/* Texture3D */

Texture3D::Texture3D()
: Texture(GL_TEXTURE_3D)
{}

Texture3D::Texture3D(
	GLsizei width, GLsizei height, GLsizei depth,
	GLenum format, GLenum type, const GLvoid *data, bool compress)
: Texture(GL_TEXTURE_3D)
{
	setPixels(width, height, depth, format, type, data, compress);
}

void Texture3D::setPixels(
	GLsizei width, GLsizei height, GLsizei depth,
	GLenum format, GLenum type, const GLvoid *data, bool compress)
{
	bind();
	glTexImage3D(
		target, 0, getInternalFormat(format, compress),
		width, height, depth, 0, format, type, data
	);
	unbind();
}
