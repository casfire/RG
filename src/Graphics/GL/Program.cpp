#include "Program.hpp"
#include <string>
#include <sstream> // to_string

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
