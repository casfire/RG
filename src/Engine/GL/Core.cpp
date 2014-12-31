#include "Core.hpp"

using Engine::GL::Object;
using Engine::GL::Exception;


/* Object */

Object::Object(GLuint ID)
: objectID(ID)
{}

GLuint Object::getObjectID() const
{
	return objectID;
}



/* Exception */

Exception::Exception(const std::string &info)
: exceptionInfo(info)
{}

const char* Exception::what() const throw()
{
	return exceptionInfo.c_str();
}
