#include "Shader.hpp"
#include <sstream>
#include <fstream>

using Engine::GL::Shader;
using Engine::GL::ShaderFile;
using Engine::GL::VertexShader;
using Engine::GL::FragmentShader;
using Engine::GL::GeometryShader;
using Engine::GL::ShaderCompileException;



/* Shader */

Shader::Shader(GLenum type)
: Object(glCreateShader(type)), type(type)
{}

Shader::~Shader()
{
	glDeleteShader(objectID);
}

Shader::Shader(GLenum type, const GLchar *source)
: Object(glCreateShader(type)), type(type)
{
	compile(source);
}

Shader::Shader(GLenum type, const ShaderFile &file)
: Object(glCreateShader(type)), type(type)
{
	compile(file);
}

void Shader::compile(const GLchar *source)
{
	glShaderSource(objectID, 1, &source, NULL);
	glCompileShader(objectID);
	if (!isCompiled()) {
		throw ShaderCompileException(*this);
	}
}

void Shader::compile(const ShaderFile &file)
{
	compile(static_cast<const GLchar*>(file.contents.data()));
}

bool Shader::isCompiled() const
{
	GLint status = GL_FALSE;
	glGetShaderiv(objectID, GL_COMPILE_STATUS, &status);
	return status != GL_FALSE;
}

GLenum Shader::getType() const
{
	return type;
}

const char* Shader::getTypeName() const
{
	switch (type) {
		//case GL_COMPUTE_SHADER: return "GL_COMPUTE_SHADER";
		case GL_VERTEX_SHADER: return "GL_VERTEX_SHADER";
		//case GL_TESS_CONTROL_SHADER: return "GL_TESS_CONTROL_SHADER";
		//case GL_TESS_EVALUATION_SHADER: return "GL_TESS_EVALUATION_SHADER";
		case GL_GEOMETRY_SHADER: return "GL_GEOMETRY_SHADER";
		case GL_FRAGMENT_SHADER: return "GL_FRAGMENT_SHADER";
		default: return "INVALID_TYPE_SHADER";
	}
}



/* ShaderFile */

ShaderFile::ShaderFile(const std::string &filename)
{
	std::ifstream stream;
	stream.exceptions(std::ifstream::failbit);
	stream.open(filename, std::ios::binary);
	stream.seekg(0, std::ios_base::end);
	std::streamsize size = stream.tellg();
	stream.seekg(0, std::ios_base::beg);
	contents.resize(static_cast<std::size_t>(size + 1));
	stream.read(contents.data(), size);
	contents[size] = '\0';
	stream.close();
}



/* VertexShader */

VertexShader::VertexShader()
: Shader(GL_VERTEX_SHADER)
{}

VertexShader::VertexShader(const GLchar *source)
: Shader(GL_VERTEX_SHADER, source)
{}

VertexShader::VertexShader(const ShaderFile &file)
: Shader(GL_VERTEX_SHADER, file)
{}



/* FragmentShader */

FragmentShader::FragmentShader()
: Shader(GL_FRAGMENT_SHADER)
{}

FragmentShader::FragmentShader(const GLchar *source)
: Shader(GL_FRAGMENT_SHADER, source)
{}

FragmentShader::FragmentShader(const ShaderFile &file)
: Shader(GL_FRAGMENT_SHADER, file)
{}



/* GeometryShader */

GeometryShader::GeometryShader()
: Shader(GL_GEOMETRY_SHADER)
{}

GeometryShader::GeometryShader(const GLchar *source)
: Shader(GL_GEOMETRY_SHADER, source)
{}

GeometryShader::GeometryShader(const ShaderFile &file)
: Shader(GL_GEOMETRY_SHADER, file)
{}



/* ShaderCompileException */

template <typename T>
inline const std::string to_string(const T &value)
{
	std::ostringstream os;
	os << value;
	return os.str();
}

inline const char* fillShaderInfoLog(GLuint ID, std::vector<char> &log)
{
	GLint size = 0;
	glGetShaderiv(ID, GL_INFO_LOG_LENGTH, &size);
	log.resize(static_cast<std::size_t>(size + 1));
	if (size > 0) {
		glGetShaderInfoLog(ID, size, NULL, static_cast<GLchar*>(log.data()));
	}
	log[static_cast<std::size_t>(size)] = '\0';
	return static_cast<const char*>(log.data());
}

ShaderCompileException::ShaderCompileException(const Shader &shader)
: Exception(
	"Failed to compile " + std::string(shader.getTypeName())
	+ " with ID " + to_string(shader.getObjectID()) + ".\n"
	+ std::string(fillShaderInfoLog(shader.getObjectID(), compileLog)))
{}

const char* ShaderCompileException::log() const
{
	return static_cast<const char*>(compileLog.data());
}
