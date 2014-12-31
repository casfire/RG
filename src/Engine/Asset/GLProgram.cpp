#include "GLProgram.hpp"
#include "Storage.hpp"
#include <vector>
#include <cctype> // std::isgraph, std::iscntrl
#include <cstddef> // std::size_t

namespace GL = Engine::GL;
using Engine::Asset::BaseAsset;
using Engine::Asset::LoadException;
using Engine::Asset::GLProgram;
using Engine::Asset::GLVertexShader;
using Engine::Asset::GLFragmentShader;
using Engine::Asset::GLGeometryShader;
typedef std::vector<BaseAsset*>::iterator AssetIterator;



void compileFromStream(std::istream &stream, GL::Shader& shader)
{
	stream.seekg(0, std::ios_base::end);
	std::streamsize size = stream.tellg();
	stream.seekg(0, std::ios_base::beg);
	std::vector<char> contents(static_cast<std::size_t>(size + 1));
	stream.read(contents.data(), size);
	contents[size] = '\0';
	shader.compile(static_cast<const GLchar*>(contents.data()));
}



/* GLVertexShader */

void GLVertexShader::load(Storage&, std::istream &stream)
{
	compileFromStream(stream, shader);
}

const GL::VertexShader& GLVertexShader::get()
{
	return shader;
}



/* GLFragmentShader */

void GLFragmentShader::load(Storage&, std::istream &stream)
{
	compileFromStream(stream, shader);
}

const GL::FragmentShader& GLFragmentShader::get()
{
	return shader;
}



/* GLGeometryShader */

void GLGeometryShader::load(Storage&, std::istream &stream)
{
	compileFromStream(stream, shader);
}

const GL::GeometryShader& GLGeometryShader::get()
{
	return shader;
}



/* GLProgram */

void GLProgram::load(Storage &storage, std::istream &stream)
{
	stream.seekg(0, std::ios_base::end);
	std::streamsize size = stream.tellg();
	stream.seekg(0, std::ios_base::beg);
	std::vector<char> contents(static_cast<std::size_t>(size + 1));
	stream.read(contents.data(), size);
	contents[size] = '\0';
	
	char* s = static_cast<char*>(contents.data());
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
			throw LoadException("Unexpected EOF after '" + std::string(1, type) + "'.");
		} else if (std::isgraph(s[pos])) {
			throw LoadException("Shader type must be a single character.");
		}
		
		/* Skip space and non-printable characters */
		while (pos < length && !std::isgraph(s[pos])) pos++;
		if (pos >= length) {
			throw LoadException("Unexpected EOF after '" + std::string(1, type) + "'.");
		}
		
		/* Read key */
		std::size_t start = pos;
		while (pos < length && !std::iscntrl(s[pos])) pos++;
		s[pos] = '\0';
		const char* key = static_cast<const char*>(&s[start]);
		
		/* Attach shader */
		if (type == 'v') {
			GLVertexShader& s = storage.grab<GLVertexShader>(key);
			program.attach(s.get());
			shaders.push_back(&s);
		} else if (type == 'f') {
			GLFragmentShader& s = storage.grab<GLFragmentShader>(key);
			program.attach(s.get());
			shaders.push_back(&s);
		} else if (type == 'g') {
			GLGeometryShader& s = storage.grab<GLGeometryShader>(key);
			program.attach(s.get());
			shaders.push_back(&s);
		} else {
			throw LoadException("Invalid shader type '" + std::string(1, type) + "'.");
		}
		
	}
	
	program.link();
}

void GLProgram::unload(Storage &storage)
{
	AssetIterator end = shaders.end();
	for (AssetIterator i = shaders.begin(); i != end; i++) {
		storage.release(**i);
	}
	shaders.clear();
}

const GL::Program& GLProgram::get()
{
	return program;
}
