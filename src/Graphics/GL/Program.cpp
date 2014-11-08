#include "Program.hpp"
#include <string>
#include <sstream> // to_string
#define GLM_FORCE_RADIANS
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

namespace GL = Graphics::GL;



/* Graphics::Program::GL */

GL::Program::Program()
: Object(glCreateProgram())
{}

GL::Program::~Program()
{
	glDeleteProgram(objectID);
}

GL::Program::Program(const VertexShader &vertex, const FragmentShader &fragment)
: Object(glCreateProgram())
{
	attach(vertex);
	attach(fragment);
	link();
}

GL::Program::Program(const VertexShader &vertex, const FragmentShader &fragment,
	const GeometryShader &geometry)
: Object(glCreateProgram())
{
	attach(vertex);
	attach(fragment);
	attach(geometry);
	link();
}

void GL::Program::attach(const Shader &shader)
{
	glAttachShader(objectID, shader.getObjectID());
}

void GL::Program::detach(const Shader &shader)
{
	glDetachShader(objectID, shader.getObjectID());
}

void GL::Program::link()
{
	glLinkProgram(objectID);
	if (!isLinked()) {
		throw ProgramLinkException(*this);
	}
}

void GL::Program::bind() const
{
	glUseProgram(objectID);
}

bool GL::Program::isLinked() const
{
	GLint status = GL_FALSE;
	glGetProgramiv(objectID, GL_LINK_STATUS, &status);
	return status != GL_FALSE;
}

bool GL::Program::isAttached(const Shader &shader) const
{
	GLint number = 0;
	glGetProgramiv(objectID, GL_ATTACHED_SHADERS, &number);
	std::vector<GLuint> shaders(static_cast<std::size_t>(number));
	glGetAttachedShaders(objectID, number, NULL, static_cast<GLuint*>(&shaders[0]));
	number--;
	while (number > 0) {
		if (shaders[number] == shader.getObjectID()) {
			return true;
		}
		number--;
	}
	return false;
}

GL::ProgramUniform GL::Program::getUniform(const GLchar *name)
{
	return GL::ProgramUniform(*this, name);
}



/* Graphics::GL::ProgramUniform */

GL::ProgramUniform::ProgramUniform(const Program &program, const GLchar *name)
: Object(glGetUniformLocation(program.getObjectID(), name))
{}

void GL::ProgramUniform::set1f(GLfloat v0)
{
	glUniform1f(objectID, v0);
}

void GL::ProgramUniform::set2f(GLfloat v0, GLfloat v1)
{
	glUniform2f(objectID, v0, v1);
}

void GL::ProgramUniform::set3f(GLfloat v0, GLfloat v1, GLfloat v2)
{
	glUniform3f(objectID, v0, v1, v2);
}

void GL::ProgramUniform::set4f(GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
{
	glUniform4f(objectID, v0, v1, v2, v3);
}

void GL::ProgramUniform::set1i(GLint v0)
{
	glUniform1i(objectID, v0);
}

void GL::ProgramUniform::set2i(GLint v0, GLint v1)
{
	glUniform2i(objectID, v0, v1);
}

void GL::ProgramUniform::set3i(GLint v0, GLint v1, GLint v2)
{
	glUniform3i(objectID, v0, v1, v2);
}

void GL::ProgramUniform::set4i(GLint v0, GLint v1, GLint v2, GLint v3)
{
	glUniform4i(objectID, v0, v1, v2, v3);
}

void GL::ProgramUniform::set1fv(GLsizei count, const GLfloat *value)
{
	glUniform1fv(objectID, count, value);
}

void GL::ProgramUniform::set2fv(GLsizei count, const GLfloat *value)
{
	glUniform2fv(objectID, count, value);
}

void GL::ProgramUniform::set3fv(GLsizei count, const GLfloat *value)
{
	glUniform3fv(objectID, count, value);
}

void GL::ProgramUniform::set4fv(GLsizei count, const GLfloat *value)
{
	glUniform4fv(objectID, count, value);
}

void GL::ProgramUniform::set1iv(GLsizei count, const GLint *value)
{
	glUniform1iv(objectID, count, value);
}

void GL::ProgramUniform::set2iv(GLsizei count, const GLint *value)
{
	glUniform2iv(objectID, count, value);
}

void GL::ProgramUniform::set3iv(GLsizei count, const GLint *value)
{
	glUniform3iv(objectID, count, value);
}

void GL::ProgramUniform::set4iv(GLsizei count, const GLint *value)
{
	glUniform4iv(objectID, count, value);
}

void GL::ProgramUniform::setMatrix2fv(GLsizei count, GLboolean transpose, const GLfloat *value)
{
	glUniformMatrix2fv(objectID, count, transpose, value);
}

void GL::ProgramUniform::setMatrix3fv(GLsizei count, GLboolean transpose, const GLfloat *value)
{
	glUniformMatrix3fv(objectID, count, transpose, value);
}

void GL::ProgramUniform::setMatrix4fv(GLsizei count, GLboolean transpose, const GLfloat *value)
{
	glUniformMatrix4fv(objectID, count, transpose, value);
}

void GL::ProgramUniform::set(const glm::mat2 &mat)
{
	glUniformMatrix2fv(objectID, 1, GL_FALSE, glm::value_ptr(mat));
}

void GL::ProgramUniform::set(const glm::mat3 &mat)
{
	glUniformMatrix3fv(objectID, 1, GL_FALSE, glm::value_ptr(mat));
}

void GL::ProgramUniform::set(const glm::mat4 &mat)
{
	glUniformMatrix4fv(objectID, 1, GL_FALSE, glm::value_ptr(mat));
}



/* Graphics::GL::ProgramLinkException */

template <typename T>
inline const std::string to_string(const T &value) {
	std::ostringstream os;
	os << value;
	return os.str();
}

inline void fillProgramInfoLog(GLuint ID, std::vector<char> &log) {
	GLint size = 0;
	glGetProgramiv(ID, GL_INFO_LOG_LENGTH, &size);
	log.resize(static_cast<std::size_t>(size + 1));
	if (size > 0) {
		glGetProgramInfoLog(ID, size, NULL, static_cast<GLchar*>(&log[0]));
	}
	log[static_cast<std::size_t>(size)] = '\0';
}

GL::ProgramLinkException::ProgramLinkException(const Program &program)
: Exception(
	"Failed to link program with ID "
	+ to_string(program.getObjectID()) + ".")
{
	fillProgramInfoLog(program.getObjectID(), linkLog);
}

const char* GL::ProgramLinkException::log() const
{
	return static_cast<const char*>(&linkLog[0]);
}
