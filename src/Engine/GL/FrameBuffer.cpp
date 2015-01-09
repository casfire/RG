#include "FrameBuffer.hpp"

using Engine::GL::FrameBuffer;

inline GLuint createFrameBuffer()
{
	GLuint ID;
	glGenFramebuffers(1, &ID);
	return ID;
}

FrameBuffer::FrameBuffer()
: Object(createFrameBuffer())
{}

FrameBuffer::~FrameBuffer()
{
	glDeleteFramebuffers(1, &objectID);
}

void FrameBuffer::bind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, objectID);
}

void FrameBuffer::unbind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
