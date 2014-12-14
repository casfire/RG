#include "Common.hpp"

namespace GL = Engine::GL;



/* Engine::GL::Object */

GL::Object::Object(GLuint ID)
: objectID(ID)
{}

GLuint GL::Object::getObjectID() const
{
	return objectID;
}



/* Engine::GL::Exception */

GL::Exception::Exception(const std::string &info)
: exceptionInfo(info)
{}

const char* GL::Exception::what() const throw()
{
	return exceptionInfo.c_str();
}
