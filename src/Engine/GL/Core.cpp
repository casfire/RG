#include "Core.hpp"

using Engine::GL::Object;
using Engine::GL::BaseException;
namespace GL = Engine::GL;



/* Object */

Object::Object(GLuint ID)
: objectID(ID)
{}

GLuint Object::getObjectID() const
{
	return objectID;
}



/* BaseException */

BaseException::BaseException(const std::string &info)
: exceptionInfo(info)
{}

const char* BaseException::what() const throw()
{
	return exceptionInfo.c_str();
}



/* Get OpenGL information */

std::string GL::getString(GLenum name)
{
	return std::string(reinterpret_cast<const char*>(glGetString(name)));
}

std::string GL::getVendor()
{
	return getString(GL_VENDOR);
}

std::string GL::getRenderer()
{
	return getString(GL_RENDERER);
}

std::string GL::getVersion()
{
	return getString(GL_VERSION);
}

std::string GL::getGLSLVersion()
{
	return getString(GL_SHADING_LANGUAGE_VERSION);
}

std::string GL::getExtensions()
{
	return getString(GL_EXTENSIONS);
}
