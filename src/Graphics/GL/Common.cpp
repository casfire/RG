#include "Common.hpp"

namespace GL = Graphics::GL;



/* Graphics::GL::Object */



GL::Object::Object(GLuint ID)
: objectID(ID)
{}

GLuint GL::Object::getObjectID() const
{
	return objectID;
}



/* Graphics::GL::Exception */



GL::Exception::Exception(const std::string &info)
: exceptionInfo(info)
{}

const char* GL::Exception::what() const throw()
{
	return exceptionInfo.c_str();
}
