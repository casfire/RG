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



/* Graphics::GL::VAO */

inline GLuint createVAO() {
	GLuint ID;
	glGenVertexArrays(1, &ID);
	return ID;
}

GL::VAO::VAO()
: Object(createVAO())
{}

void GL::VAO::bind() const
{
	glBindVertexArray(objectID);
}

void GL::VAO::unbind() const
{
	glBindVertexArray(0);
}
