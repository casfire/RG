#include "GLProgram.hpp"
#include "Storage.hpp"
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



/* GLVertexShader */

void GLVertexShader::load(Storage&, std::vector<char> &data)
{
	shader.compile(static_cast<const GLchar*>(data.data()));
}

const GL::VertexShader& GLVertexShader::get()
{
	return shader;
}



/* GLFragmentShader */

void GLFragmentShader::load(Storage&, std::vector<char> &data)
{
	shader.compile(static_cast<const GLchar*>(data.data()));
}

const GL::FragmentShader& GLFragmentShader::get()
{
	return shader;
}



/* GLGeometryShader */

void GLGeometryShader::load(Storage&, std::vector<char> &data)
{
	shader.compile(static_cast<const GLchar*>(data.data()));
}

const GL::GeometryShader& GLGeometryShader::get()
{
	return shader;
}



/* GLProgram */

void GLProgram::loadBegin(Storage&)
{}

void GLProgram::loadEnd(Storage&)
{
	program.link();
}

void GLProgram::loadToken(
	Storage &storage,
	const std::string &key,
	const std::string &value)
{
	if (key.length() != 1) throw LoadException("Shader type must be a single character.");
	char type = key[0];
	if (type == 'v') {
		GLVertexShader& s = storage.grab<GLVertexShader>(value);
		program.attach(s.get());
		shaders.push_back(&s);
	} else if (type == 'f') {
		GLFragmentShader& s = storage.grab<GLFragmentShader>(value);
		program.attach(s.get());
		shaders.push_back(&s);
	} else if (type == 'g') {
		GLGeometryShader& s = storage.grab<GLGeometryShader>(value);
		program.attach(s.get());
		shaders.push_back(&s);
	} else {
		throw LoadException("Invalid shader type '" + std::string(1, type) + "'.");
	}
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
