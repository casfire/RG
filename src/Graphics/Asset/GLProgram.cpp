#include "GLProgram.hpp"
#include <vector>
#include <cctype> // std::isgraph, std::iscntrl
#include <cstddef> // std::size_t

namespace A = Graphics::Asset;
namespace GL = Graphics::GL;



void compileFromStream(std::istream& stream, GL::Shader &shader)
{
	stream.seekg(0, std::ios_base::end);
	std::streamsize size = stream.tellg();
	stream.seekg(0, std::ios_base::beg);
	std::vector<char> contents(static_cast<std::size_t>(size + 1));
	stream.read(&contents[0], size);
	contents[size] = '\0';
	shader.compile(static_cast<const GLchar*>(&contents[0]));
}



/* Graphics::Asset::GLVertexShader */

A::GLVertexShader::GLVertexShader(A::Storage* storage, std::istream& stream)
{
	(void) storage;
	compileFromStream(stream, shader);
}

A::GLVertexShader::~GLVertexShader()
{}

const GL::VertexShader& A::GLVertexShader::get()
{
	return shader;
}



/* Graphics::Asset::GLFragmentShader */

A::GLFragmentShader::GLFragmentShader(A::Storage* storage, std::istream& stream)
{
	(void) storage;
	compileFromStream(stream, shader);
}

A::GLFragmentShader::~GLFragmentShader()
{}

const GL::FragmentShader& A::GLFragmentShader::get()
{
	return shader;
}



/* Graphics::Asset::GLGeometryShader */

A::GLGeometryShader::GLGeometryShader(A::Storage* storage, std::istream& stream)
{
	(void) storage;
	compileFromStream(stream, shader);
}

A::GLGeometryShader::~GLGeometryShader()
{}

const GL::GeometryShader& A::GLGeometryShader::get()
{
	return shader;
}



/* Graphics::Asset::GLProgram */

A::GLProgram::GLProgram(Storage* storage, std::istream& stream)
{
	stream.seekg(0, std::ios_base::end);
	std::streamsize size = stream.tellg();
	stream.seekg(0, std::ios_base::beg);
	std::vector<char> contents(static_cast<std::size_t>(size));
	stream.read(&contents[0], size);
	
	std::vector<A::GLVertexShader*>   vShaders;
	std::vector<A::GLFragmentShader*> fShaders;
	std::vector<A::GLGeometryShader*> gShaders;
	
	char* s = static_cast<char*>(&contents[0]);
	std::size_t pos = 0;
	std::size_t length = static_cast<std::size_t>(size);
	while (pos < length) {
		
		/* Skip space and non-printable characters */
		while (pos < length && !std::isgraph(s[pos])) pos++;
		if (pos >= length) break;
		
		/* Shader type */
		char type = s[pos];
		pos++;
		if (pos >= length) {
			throw A::FormatException("Unexpected EOF.");
		} else if (std::isgraph(s[pos])) {
			throw A::FormatException("Shader type must be a single character.");
		}
		
		/* Skip space and non-printable characters */
		while (pos < length && !std::isgraph(s[pos])) pos++;
		if (pos >= length) throw A::FormatException("Unexpected EOF.");
		
		/* Read key */
		std::size_t start = pos;
		while (pos < length && !std::iscntrl(s[pos])) pos++;
		s[pos] = '\0';
		const char* key = static_cast<const char*>(&s[start]);
		
		switch (type) {
		case 'v':
			vShaders.push_back(storage->grab<A::GLVertexShader>(key));
			break;
		case 'f':
			fShaders.push_back(storage->grab<A::GLFragmentShader>(key));
			break;
		case 'g':
			gShaders.push_back(storage->grab<A::GLGeometryShader>(key));
			break;
		default:
			throw A::FormatException("Invalid shader type '" + std::string(1, type) + "'.");
		}
		
	}
	
	for (std::vector<A::GLVertexShader*>::iterator it = vShaders.begin(); it != vShaders.end(); ++it) {
		program.attach((*it)->get());
		storage->release(*it);
	}
	for (std::vector<A::GLFragmentShader*>::iterator it = fShaders.begin(); it != fShaders.end(); ++it) {
		program.attach((*it)->get());
		storage->release(*it);
	}
	for (std::vector<A::GLGeometryShader*>::iterator it = gShaders.begin(); it != gShaders.end(); ++it) {
		program.attach((*it)->get());
		storage->release(*it);
	}
	
	program.link();
}

A::GLProgram::~GLProgram()
{}

const GL::Program& A::GLProgram::get()
{
	return program;
}
