#include "Shader.hpp"

namespace GE {
	
	
	/* std::to_string replacement */
	
	
	template <typename T>
	const std::string to_string(T value) {
		std::ostringstream os;
		os << value;
		return os.str();
	}
	
	
	/* ShaderException */


	ShaderException::ShaderException(const std::ios_base::failure &iofail)
	: info("IO exception: " + std::string(iofail.what())) {
		infoLog.push_back('\0');
	}
	
	ShaderException::ShaderException(const Shader &shader)
	: info("Failed to create " + std::string(shader.getTypeName()) + ".") {
		infoLog.push_back('\0');
	}
	
	ShaderException::ShaderException(const Shader &shader, GLuint ID)
	: info("Failed to compile " + std::string(shader.getTypeName())
	+ " with ID " + to_string(ID) + ".") {
		GLint logSize = 0;
		glGetShaderiv(ID, GL_INFO_LOG_LENGTH, &logSize);
		infoLog.resize(static_cast<std::size_t>(logSize + 1));
		if (logSize > 0) {
			glGetShaderInfoLog(ID, logSize, NULL, static_cast<GLchar*>(&infoLog[0]));
		}
		infoLog[static_cast<std::size_t>(logSize)] = '\0';
		#ifdef GE_EXCEPTION_APPEND_LOG
		if (logSize > 0) info += std::string("\n") + static_cast<GLchar*>(&infoLog[0]);
		#endif
	}
	
	ShaderException::ShaderException(const Program &program)
	: info("Failed to create program.") {
		(void) program;
		infoLog.push_back('\0');
	}
	
	ShaderException::ShaderException(const Program &program, GLuint ID)
	: info("Failed to link program with ID " + to_string(ID) + ".") {
		(void) program;
		GLint logSize = 0;
		glGetProgramiv(ID, GL_INFO_LOG_LENGTH, &logSize);
		infoLog.resize(static_cast<std::size_t>(logSize + 1));
		if (logSize > 0) {
			glGetProgramInfoLog(ID, logSize, NULL, static_cast<GLchar*>(&infoLog[0]));
		}
		infoLog[static_cast<std::size_t>(logSize)] = '\0';
		#ifdef GE_EXCEPTION_APPEND_LOG
		if (logSize > 0) info += std::string("\n") + static_cast<GLchar*>(&infoLog[0]);
		#endif
	}
	
	const char* ShaderException::what() const throw() {
		return info.c_str();
	}
	
	const char* ShaderException::log() const {
		return static_cast<const char*>(&infoLog[0]);
	}
	
	bool ShaderException::hasLog() const {
		return infoLog.size() > 1;
	}
	
	
	/* ShaderFile */
	
	
	ShaderFile::ShaderFile(const std::string &filename) : filename(filename) {}
	
	const std::string ShaderFile::get() const {
		return filename;
	}
	

	/* Shader */


	Shader::Shader(GLenum type) : type(type), ID(0) {}
	
	Shader::Shader(GLenum type, const GLchar *source) : type(type), ID(0) {
		compile(source);
	}
	
	Shader::Shader(GLenum type, std::istream &source) : type(type), ID(0) {
		compile(source);
	}
	
	Shader::Shader(GLenum type, const ShaderFile &file) : type(type), ID(0) {
		compile(file);
	}
	
	Shader::Shader(GLenum type, const std::string &source) : type(type), ID(0) {
		compile(source);
	}

	Shader::~Shader() {
		destroy();
	}
	
	void Shader::compile(const GLchar *source) {
		destroy();
		GLuint shaderID = glCreateShader(type);
		if (shaderID == 0) throw ShaderException(*this);
		glShaderSource(shaderID, 1, &source, NULL);
		glCompileShader(shaderID);
		GLint status = GL_FALSE;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &status);
		if (status == GL_FALSE) {
			throw ShaderException(*this, shaderID);
		}
		ID = shaderID;
	}
	
	void Shader::compile(std::istream &source) {
		try {
			source.exceptions(std::ifstream::failbit);
			source.seekg(0, std::ios_base::end);
			std::streamsize size = source.tellg();
			source.seekg(0, std::ios_base::beg);
			std::vector<char> buffer(static_cast<std::size_t>(size + 1));
			source.read(&buffer[0], size);
			buffer[size] = '\0';
			compile(static_cast<const GLchar*>(&buffer[0]));
		} catch (std::ios_base::failure &fail) {
			throw ShaderException(fail);
		}
	}
	
	void Shader::compile(const ShaderFile &file) {
		try {
			std::ifstream stream;
			stream.exceptions(std::ifstream::failbit);
			stream.open(file.get(), std::ios::binary);
			compile(stream);
			stream.close();
		} catch (std::ios_base::failure &fail) {
			throw ShaderException(fail);
		}
	}
	
	void Shader::compile(const std::string &source) {
		compile(static_cast<const GLchar*>(source.c_str()));
	}
	
	void Shader::destroy() {
		if (ID != 0) {
			glDeleteShader(ID);
			ID = 0;
		}
	}

	bool Shader::isCompiled() const {
		return ID != 0;
	}

	GLuint Shader::getID() const {
		return ID;
	}
	
	GLenum Shader::getType() const {
		return type;
	}
	
	const char* Shader::getTypeName() const {
		switch (type) {
		case GL_VERTEX_SHADER: return "GL_VERTEX_SHADER";
		case GL_GEOMETRY_SHADER: return "GL_GEOMETRY_SHADER";
		case GL_FRAGMENT_SHADER: return "GL_FRAGMENT_SHADER";
		default: return "INVALID_TYPE_SHADER";
		}
	}


	/* Other shaders */


	VertexShader::VertexShader() : Shader(GL_VERTEX_SHADER) {}
	VertexShader::VertexShader(const GLchar *source) : Shader(GL_VERTEX_SHADER, source) {}
	VertexShader::VertexShader(std::istream &source) : Shader(GL_VERTEX_SHADER, source) {}
	VertexShader::VertexShader(const ShaderFile &file) : Shader(GL_VERTEX_SHADER, file) {}
	VertexShader::VertexShader(const std::string &source) : Shader(GL_VERTEX_SHADER, source) {}

	FragmentShader::FragmentShader() : Shader(GL_FRAGMENT_SHADER) {}
	FragmentShader::FragmentShader(const GLchar *source) : Shader(GL_FRAGMENT_SHADER, source) {}
	FragmentShader::FragmentShader(std::istream &source) : Shader(GL_FRAGMENT_SHADER, source) {}
	FragmentShader::FragmentShader(const ShaderFile &file) : Shader(GL_FRAGMENT_SHADER, file) {}
	FragmentShader::FragmentShader(const std::string &source) : Shader(GL_FRAGMENT_SHADER, source) {}

	GeometryShader::GeometryShader() : Shader(GL_GEOMETRY_SHADER) {}
	GeometryShader::GeometryShader(const GLchar *source) : Shader(GL_GEOMETRY_SHADER, source) {}
	GeometryShader::GeometryShader(std::istream &source) : Shader(GL_GEOMETRY_SHADER, source) {}
	GeometryShader::GeometryShader(const ShaderFile &file) : Shader(GL_GEOMETRY_SHADER, file) {}
	GeometryShader::GeometryShader(const std::string &source) : Shader(GL_GEOMETRY_SHADER, source) {}
	
	
	/* Program */
	
	
	Program::Program() : ID(0) {}
	
	Program::Program(const ShaderFile &vertex, const ShaderFile &fragment) : ID(0) {
		link(vertex, fragment);
	}
	
	Program::Program(const VertexShader &vertex, const FragmentShader &fragment) : ID(0) {
		link(vertex, fragment);
	}
	
	Program::Program(const ShaderFile &vertex, const ShaderFile &fragment, const ShaderFile &geometry)
	: ID(0) {
		link(vertex, fragment, geometry);
	}
	
	Program::Program(const VertexShader &vertex, const FragmentShader &fragment, const GeometryShader &geometry)
	: ID(0) {
		link(vertex, fragment, geometry);
	}
	
	Program::~Program() {
		destroy();
	}
	
	void Program::link(const ShaderFile &vertex, const ShaderFile &fragment) {
		link(VertexShader(vertex), FragmentShader(fragment));
	}
	
	void Program::link(const VertexShader &vertex, const FragmentShader &fragment) {
		destroy();
		GLuint programID = glCreateProgram();
		if (programID == 0) throw ShaderException(*this);
		glAttachShader(programID, vertex.getID());
		glAttachShader(programID, fragment.getID());
		glLinkProgram(programID);
		GLint status = GL_FALSE;
		glGetProgramiv(programID, GL_LINK_STATUS, &status);
		if (status == GL_FALSE) {
			throw ShaderException(*this, programID);
		}
		ID = programID;
	}
	
	void Program::link(const VertexShader &vertex, const FragmentShader &fragment, const GeometryShader &geometry) {
		destroy();
		GLuint programID = glCreateProgram();
		if (programID == 0) throw ShaderException(*this);
		glAttachShader(programID, vertex.getID());
		glAttachShader(programID, fragment.getID());
		glAttachShader(programID, geometry.getID());
		glLinkProgram(programID);
		GLint status = GL_FALSE;
		glGetProgramiv(programID, GL_LINK_STATUS, &status);
		if (status == GL_FALSE) {
			throw ShaderException(*this, programID);
		}
		ID = programID;
	}
	
	void Program::link(const ShaderFile &vertex, const ShaderFile &fragment, const ShaderFile &geometry) {
		link(VertexShader(vertex), FragmentShader(fragment), GeometryShader(geometry));
	}
	
	void Program::destroy() {
		if (ID != 0) {
			glDeleteProgram(ID);
			ID = 0;
		}
	}
	
	bool Program::isLinked() const {
		return ID != 0;
	}
	
	GLuint Program::getID() const {
		return ID;
	}
	
	
} // namespace GE
