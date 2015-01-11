#include "Program.hpp"
#include "Uniform.hpp"
#include "Shader.hpp"
#include <string>
#include <sstream>

using Engine::GL::Program;
using Engine::GL::ProgramLinkException;
using Engine::GL::Uniform;



/* Program */

Program::Program()
: Object(glCreateProgram())
{}

Program::~Program()
{
	glDeleteProgram(objectID);
}

Program::Program(
	const VertexShader &vertex,
	const FragmentShader &fragment)
: Object(glCreateProgram())
{
	attach(vertex);
	attach(fragment);
	link();
}

Program::Program(
	const VertexShader &vertex,
	const FragmentShader &fragment,
	const GeometryShader &geometry)
: Object(glCreateProgram())
{
	attach(vertex);
	attach(fragment);
	attach(geometry);
	link();
}

void Program::attach(const Shader &shader)
{
	glAttachShader(objectID, shader.getObjectID());
}

void Program::detach(const Shader &shader)
{
	glDetachShader(objectID, shader.getObjectID());
}

void Program::link()
{
	glLinkProgram(objectID);
	if (!isLinked()) {
		throw ProgramLinkException(*this);
	}
}

void Program::bind() const
{
	glUseProgram(objectID);
}

void Program::unbind() const
{
	glUseProgram(0);
}

bool Program::isLinked() const
{
	GLint status = GL_FALSE;
	glGetProgramiv(objectID, GL_LINK_STATUS, &status);
	return status != GL_FALSE;
}

bool Program::isAttached(const Shader &shader) const
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

Uniform Program::getUniform(const GLchar *name) const
{
	return Uniform(*this, name);
}



/* ProgramLinkException */

template <typename T>
inline const std::string to_string(const T &value)
{
	std::ostringstream os;
	os << value;
	return os.str();
}

inline const char* fillProgramInfoLog(GLuint ID, std::vector<char> &log)
{
	GLint size = 0;
	glGetProgramiv(ID, GL_INFO_LOG_LENGTH, &size);
	log.resize(static_cast<std::size_t>(size + 1));
	if (size > 0) {
		glGetProgramInfoLog(ID, size, NULL, static_cast<GLchar*>(log.data()));
	}
	log[static_cast<std::size_t>(size)] = '\0';
	return static_cast<const char*>(log.data());
}

ProgramLinkException::ProgramLinkException(const Program &program)
: BaseException(
	"Failed to link program with ID "
	+ to_string(program.getObjectID()) + ".\n"
	+ std::string(fillProgramInfoLog(program.getObjectID(), linkLog)))
{}

const char* ProgramLinkException::log() const
{
	return static_cast<const char*>(linkLog.data());
}
