#pragma once
#ifndef _ENGINE_GL_SHADER_HPP_
#define _ENGINE_GL_SHADER_HPP_

#include "Forward.hpp"
#include "Core.hpp"
#include <string>
#include <vector>

namespace Engine { namespace GL {
	
	
	
	/* Base class for all GLSL shaders */
	class Shader : public Object {
	public:
		
		/* Create a new shader */
		Shader(GLenum type);
		
		/* Delete shader */
		~Shader();
		
		/* Create and compile shader - throws ShaderCompileException */
		Shader(GLenum type, const GLchar *source);
		Shader(GLenum type, const ShaderFile &file);
		
		/* Compile shader - throws ShaderCompileException */
		void compile(const GLchar *source);
		void compile(const ShaderFile &file);
		
		/* Getters */
		bool isCompiled() const;
		GLenum getType() const;
		const char* getTypeName() const;
		
	private:
		
		const GLenum type;
		
	};
	
	
	
	/* Shader file object for compilation from file */
	class ShaderFile {
	public:
		
		/* Read entire file - throws std::ios_base::failure */
		ShaderFile(const std::string &filename);
		
	private:
		
		friend class Shader;
		std::vector<char> contents;
		
	};
	
	
	
	/* Vertex shader */
	class VertexShader : public Shader {
	public:
		
		/* Create shader */
		VertexShader();
		
		/* Create and compile shader - throws ShaderCompileException */
		VertexShader(const GLchar *source);
		VertexShader(const ShaderFile &file);
		
	};
	
	
	
	/* Fragment shader */
	class FragmentShader : public Shader {
	public:
		
		/* Create shader */
		FragmentShader();
		
		/* Create and compile shader - throws ShaderCompileException */
		FragmentShader(const GLchar *source);
		FragmentShader(const ShaderFile &file);
		
	};
	
	
	
	/* Geometry shader */
	class GeometryShader : public Shader {
	public:
		
		/* Create shader */
		GeometryShader();
		
		/* Create and compile shader - throws ShaderCompileException */
		GeometryShader(const GLchar *source);
		GeometryShader(const ShaderFile &file);
		
	};
	
	
	
	/* Thrown when shader compilation fails */
	class ShaderCompileException : public BaseException {
	public:
		
		/* Return entire compile log */
		const char* log() const;
		
	private:
		
		friend class Shader;
		std::vector<char> compileLog;
		ShaderCompileException(const Shader &shader);
		
	};
	
	
	
}} // namespace Engine::GL

#endif // _ENGINE_GL_SHADER_HPP_
