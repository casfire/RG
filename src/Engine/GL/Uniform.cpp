#include "Uniform.hpp"
#include "Program.hpp"
#define GLM_FORCE_RADIANS
#include <glm/gtc/type_ptr.hpp>

using Engine::GL::ProgramUniform;
using Engine::GL::Program;

ProgramUniform::ProgramUniform(const Program &program, const GLchar *name)
: location(glGetUniformLocation(program.getObjectID(), name))
{}

GLuint ProgramUniform::getLocation() const
{
	return location;
}

void ProgramUniform::set1f(GLfloat v0)
{
	glUniform1f(location, v0);
}

void ProgramUniform::set2f(GLfloat v0, GLfloat v1)
{
	glUniform2f(location, v0, v1);
}

void ProgramUniform::set3f(GLfloat v0, GLfloat v1, GLfloat v2)
{
	glUniform3f(location, v0, v1, v2);
}

void ProgramUniform::set4f(GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
{
	glUniform4f(location, v0, v1, v2, v3);
}

void ProgramUniform::set1i(GLint v0)
{
	glUniform1i(location, v0);
}

void ProgramUniform::set2i(GLint v0, GLint v1)
{
	glUniform2i(location, v0, v1);
}

void ProgramUniform::set3i(GLint v0, GLint v1, GLint v2)
{
	glUniform3i(location, v0, v1, v2);
}

void ProgramUniform::set4i(GLint v0, GLint v1, GLint v2, GLint v3)
{
	glUniform4i(location, v0, v1, v2, v3);
}

void ProgramUniform::set1fv(GLsizei count, const GLfloat *value)
{
	glUniform1fv(location, count, value);
}

void ProgramUniform::set2fv(GLsizei count, const GLfloat *value)
{
	glUniform2fv(location, count, value);
}

void ProgramUniform::set3fv(GLsizei count, const GLfloat *value)
{
	glUniform3fv(location, count, value);
}

void ProgramUniform::set4fv(GLsizei count, const GLfloat *value)
{
	glUniform4fv(location, count, value);
}

void ProgramUniform::set1iv(GLsizei count, const GLint *value)
{
	glUniform1iv(location, count, value);
}

void ProgramUniform::set2iv(GLsizei count, const GLint *value)
{
	glUniform2iv(location, count, value);
}

void ProgramUniform::set3iv(GLsizei count, const GLint *value)
{
	glUniform3iv(location, count, value);
}

void ProgramUniform::set4iv(GLsizei count, const GLint *value)
{
	glUniform4iv(location, count, value);
}

void ProgramUniform::setMatrix2fv(GLsizei count, GLboolean transpose, const GLfloat *value)
{
	glUniformMatrix2fv(location, count, transpose, value);
}

void ProgramUniform::setMatrix3fv(GLsizei count, GLboolean transpose, const GLfloat *value)
{
	glUniformMatrix3fv(location, count, transpose, value);
}

void ProgramUniform::setMatrix4fv(GLsizei count, GLboolean transpose, const GLfloat *value)
{
	glUniformMatrix4fv(location, count, transpose, value);
}

void ProgramUniform::set(const glm::mat2 &mat)
{
	glUniformMatrix2fv(location, 1, GL_FALSE, glm::value_ptr(mat));
}

void ProgramUniform::set(const glm::mat3 &mat)
{
	glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(mat));
}

void ProgramUniform::set(const glm::mat4 &mat)
{
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
}

void ProgramUniform::set(const glm::vec2 &vec)
{
	glUniform2f(location, vec.x, vec.y);
}

void ProgramUniform::set(const glm::vec3 &vec)
{
	glUniform3f(location, vec.x, vec.y, vec.z);
}

void ProgramUniform::set(const glm::vec4 &vec)
{
	glUniform4f(location, vec.x, vec.y, vec.z, vec.w);
}
