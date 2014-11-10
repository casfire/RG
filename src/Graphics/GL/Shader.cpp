#include "Shader.hpp"
#include <sstream> // to_string
#include <fstream> // ShaderFile

namespace GL = Graphics::GL;



/* Graphics::GL::Shader */

GL::Shader::Shader(GLenum type)
: Object(glCreateShader(type)), type(type)
{}

GL::Shader::~Shader()
{
	glDeleteShader(objectID);
}

GL::Shader::Shader(GLenum type, const GLchar *source)
: Object(glCreateShader(type)), type(type)
{
	compile(source);
}

GL::Shader::Shader(GLenum type, const ShaderFile &file)
: Object(glCreateShader(type)), type(type)
{
	compile(file);
}

void GL::Shader::compile(const GLchar *source)
{
	glShaderSource(objectID, 1, &source, NULL);
	glCompileShader(objectID);
	if (!isCompiled()) {
		throw ShaderCompileException(*this);
	}
}

void GL::Shader::compile(const ShaderFile &file)
{
	compile(static_cast<const GLchar*>(&file.contents[0]));
}

bool GL::Shader::isCompiled() const
{
	GLint status = GL_FALSE;
	glGetShaderiv(objectID, GL_COMPILE_STATUS, &status);
	return status != GL_FALSE;
}

GLenum GL::Shader::getType() const
{
	return type;
}

const char* GL::Shader::getTypeName() const
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



/* Graphics::GL::ShaderFile */

GL::ShaderFile::ShaderFile(const std::string &filename)
{
	std::ifstream stream;
	stream.exceptions(std::ifstream::failbit);
	stream.open(filename, std::ios::binary);
	stream.seekg(0, std::ios_base::end);
	std::streamsize size = stream.tellg();
	stream.seekg(0, std::ios_base::beg);
	contents.resize(static_cast<std::size_t>(size + 1));
	stream.read(&contents[0], size);
	contents[size] = '\0';
	stream.close();
}



/* Graphics::GL::VertexShader */

GL::VertexShader::VertexShader()
: Shader(GL_VERTEX_SHADER)
{}

GL::VertexShader::VertexShader(const GLchar *source)
: Shader(GL_VERTEX_SHADER, source)
{}

GL::VertexShader::VertexShader(const ShaderFile &file)
: Shader(GL_VERTEX_SHADER, file)
{}



/* Graphics::GL::FragmentShader */

GL::FragmentShader::FragmentShader()
: Shader(GL_FRAGMENT_SHADER)
{}

GL::FragmentShader::FragmentShader(const GLchar *source)
: Shader(GL_FRAGMENT_SHADER, source)
{}

GL::FragmentShader::FragmentShader(const ShaderFile &file)
: Shader(GL_FRAGMENT_SHADER, file)
{}



/* Graphics::GL::GeometryShader */

GL::GeometryShader::GeometryShader()
: Shader(GL_GEOMETRY_SHADER)
{}

GL::GeometryShader::GeometryShader(const GLchar *source)
: Shader(GL_GEOMETRY_SHADER, source)
{}

GL::GeometryShader::GeometryShader(const ShaderFile &file)
: Shader(GL_GEOMETRY_SHADER, file)
{}



/* Graphics::GL::ShaderCompileException */

template <typename T>
inline const std::string to_string(const T &value)
{
	std::ostringstream os;
	os << value;
	return os.str();
}

inline void fillShaderInfoLog(GLuint ID, std::vector<char> &log)
{
	GLint size = 0;
	glGetShaderiv(ID, GL_INFO_LOG_LENGTH, &size);
	log.resize(static_cast<std::size_t>(size + 1));
	if (size > 0) {
		glGetShaderInfoLog(ID, size, NULL, static_cast<GLchar*>(&log[0]));
	}
	log[static_cast<std::size_t>(size)] = '\0';
}

GL::ShaderCompileException::ShaderCompileException(const Shader &shader)
: Exception(
	"Failed to compile " + std::string(shader.getTypeName())
	+ " with ID " + to_string(shader.getObjectID()) + ".")
{
	fillShaderInfoLog(shader.getObjectID(), compileLog);
}

const char* GL::ShaderCompileException::log() const
{
	return static_cast<const char*>(&compileLog[0]);
}
