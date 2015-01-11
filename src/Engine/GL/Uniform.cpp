#include "Uniform.hpp"
#include "Program.hpp"
#define GLM_FORCE_RADIANS
#include <glm/gtc/type_ptr.hpp>

using Engine::GL::Uniform;
using Engine::GL::Program;

Uniform::Uniform()
: location(0)
{}

Uniform::Uniform(const Program &program, const GLchar *name)
: location(glGetUniformLocation(program.getObjectID(), name))
{}

Uniform::Uniform(const Uniform &uniform)
: location(uniform.location)
{}

GLuint Uniform::getLocation() const
{
	return location;
}

void Uniform::locate(const Program &program, const GLchar *name)
{
	location = glGetUniformLocation(program.getObjectID(), name);
}

void Uniform::set1f(GLfloat v0)
{
	glUniform1f(location, v0);
}

void Uniform::set2f(GLfloat v0, GLfloat v1)
{
	glUniform2f(location, v0, v1);
}

void Uniform::set3f(GLfloat v0, GLfloat v1, GLfloat v2)
{
	glUniform3f(location, v0, v1, v2);
}

void Uniform::set4f(GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
{
	glUniform4f(location, v0, v1, v2, v3);
}

void Uniform::set1i(GLint v0)
{
	glUniform1i(location, v0);
}

void Uniform::set2i(GLint v0, GLint v1)
{
	glUniform2i(location, v0, v1);
}

void Uniform::set3i(GLint v0, GLint v1, GLint v2)
{
	glUniform3i(location, v0, v1, v2);
}

void Uniform::set4i(GLint v0, GLint v1, GLint v2, GLint v3)
{
	glUniform4i(location, v0, v1, v2, v3);
}

void Uniform::set1fv(GLsizei count, const GLfloat *value)
{
	glUniform1fv(location, count, value);
}

void Uniform::set2fv(GLsizei count, const GLfloat *value)
{
	glUniform2fv(location, count, value);
}

void Uniform::set3fv(GLsizei count, const GLfloat *value)
{
	glUniform3fv(location, count, value);
}

void Uniform::set4fv(GLsizei count, const GLfloat *value)
{
	glUniform4fv(location, count, value);
}

void Uniform::set1iv(GLsizei count, const GLint *value)
{
	glUniform1iv(location, count, value);
}

void Uniform::set2iv(GLsizei count, const GLint *value)
{
	glUniform2iv(location, count, value);
}

void Uniform::set3iv(GLsizei count, const GLint *value)
{
	glUniform3iv(location, count, value);
}

void Uniform::set4iv(GLsizei count, const GLint *value)
{
	glUniform4iv(location, count, value);
}

void Uniform::setMatrix2fv(GLsizei count, GLboolean transpose, const GLfloat *value)
{
	glUniformMatrix2fv(location, count, transpose, value);
}

void Uniform::setMatrix3fv(GLsizei count, GLboolean transpose, const GLfloat *value)
{
	glUniformMatrix3fv(location, count, transpose, value);
}

void Uniform::setMatrix4fv(GLsizei count, GLboolean transpose, const GLfloat *value)
{
	glUniformMatrix4fv(location, count, transpose, value);
}

void Uniform::set(const glm::mat2 &mat)
{
	glUniformMatrix2fv(location, 1, GL_FALSE, glm::value_ptr(mat));
}

void Uniform::set(const glm::mat3 &mat)
{
	glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(mat));
}

void Uniform::set(const glm::mat4 &mat)
{
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
}

void Uniform::set(const glm::vec2 &vec)
{
	glUniform2f(location, vec.x, vec.y);
}

void Uniform::set(const glm::vec3 &vec)
{
	glUniform3f(location, vec.x, vec.y, vec.z);
}

void Uniform::set(const glm::vec4 &vec)
{
	glUniform4f(location, vec.x, vec.y, vec.z, vec.w);
}

void Uniform::set(const glm::ivec2 &vec)
{
	glUniform2i(location, vec.x, vec.y);
}

void Uniform::set(const glm::ivec3 &vec)
{
	glUniform3i(location, vec.x, vec.y, vec.z);
}

void Uniform::set(const glm::ivec4 &vec)
{
	glUniform4i(location, vec.x, vec.y, vec.z, vec.w);
}
