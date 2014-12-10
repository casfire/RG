#include "GLProgram.hpp"
#include "Storage.hpp"
#include <vector>
#include <cctype> // std::isgraph, std::iscntrl
#include <cstddef> // std::size_t

namespace A = Engine::Asset;
namespace GL = Engine::GL;



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



/* Engine::Asset::GLVertexShader */

A::GLVertexShader::GLVertexShader()
{}

A::GLVertexShader::~GLVertexShader()
{}

void A::GLVertexShader::load(A::Storage& storage, std::istream& stream)
{
	(void) storage;
	compileFromStream(stream, shader);
}

const GL::VertexShader& A::GLVertexShader::get()
{
	return shader;
}



/* Engine::Asset::GLFragmentShader */

A::GLFragmentShader::GLFragmentShader()
{}

A::GLFragmentShader::~GLFragmentShader()
{}

void A::GLFragmentShader::load(A::Storage& storage, std::istream& stream)
{
	(void) storage;
	compileFromStream(stream, shader);
}

const GL::FragmentShader& A::GLFragmentShader::get()
{
	return shader;
}



/* Engine::Asset::GLGeometryShader */

A::GLGeometryShader::GLGeometryShader()
{}

A::GLGeometryShader::~GLGeometryShader()
{}

void A::GLGeometryShader::load(A::Storage& storage, std::istream& stream)
{
	(void) storage;
	compileFromStream(stream, shader);
}

const GL::GeometryShader& A::GLGeometryShader::get()
{
	return shader;
}



/* Engine::Asset::GLProgram */

A::GLProgram::GLProgram()
{}

A::GLProgram::~GLProgram()
{}

void A::GLProgram::load(Storage& storage, std::istream& stream)
{
	stream.seekg(0, std::ios_base::end);
	std::streamsize size = stream.tellg();
	stream.seekg(0, std::ios_base::beg);
	std::vector<char> contents(static_cast<std::size_t>(size + 1));
	stream.read(&contents[0], size);
	contents[size] = '\0';
	
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
			throw A::LoadException("Unexpected EOF after '" + std::string(1, type) + "'.");
		} else if (std::isgraph(s[pos])) {
			throw A::LoadException("Shader type must be a single character.");
		}
		
		/* Skip space and non-printable characters */
		while (pos < length && !std::isgraph(s[pos])) pos++;
		if (pos >= length) {
			throw A::LoadException("Unexpected EOF after '" + std::string(1, type) + "'.");
		}
		
		/* Read key */
		std::size_t start = pos;
		while (pos < length && !std::iscntrl(s[pos])) pos++;
		s[pos] = '\0';
		const char* key = static_cast<const char*>(&s[start]);
		
		/* Attach shader */
		if (type == 'v') {
			A::GLVertexShader& s = storage.grab<A::GLVertexShader>(key);
			program.attach(s.get());
			storage.release(s);
		} else if (type == 'f') {
			A::GLFragmentShader& s = storage.grab<A::GLFragmentShader>(key);
			program.attach(s.get());
			storage.release(s);
		} else if (type == 'g') {
			A::GLGeometryShader& s = storage.grab<A::GLGeometryShader>(key);
			program.attach(s.get());
			storage.release(s);
		} else {
			throw A::LoadException("Invalid shader type '" + std::string(1, type) + "'.");
		}
		
	}
	
	program.link();
}

const GL::Program& A::GLProgram::get()
{
	return program;
}
