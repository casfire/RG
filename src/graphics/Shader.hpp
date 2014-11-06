#pragma once
#ifndef _GE_SHADER_HPP_
#define _GE_SHADER_HPP_

#include <istream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <exception>
#include "gl_core_3_3.h"

#define GE_EXCEPTION_APPEND_LOG

namespace GE {
	
	class ShaderException;
	class ShaderFile;
	class Shader;
	class VertexShader;
	class FragmentShader;
	class GeometryShader;
	class Program;
	
	class ShaderException : public std::exception {
	public:
		const char* what() const throw();
		const char* log() const;
		bool hasLog() const;
	private:
		friend class Shader;
		friend class Program;
		std::string info;
		std::vector<char> infoLog;
		ShaderException(const std::ios_base::failure &fail); /* IO exception */
		ShaderException(const Shader &shader);               /* Shader create exception */
		ShaderException(const Shader &shader, GLuint ID);    /* Shader compile exception */
		ShaderException(const Program &program);             /* Program create exception */
		ShaderException(const Program &program, GLuint ID);  /* Program link exception */ 
	};
	
	class ShaderFile {
	public:
		ShaderFile(const std::string &filename);
	private:
		friend class Shader;
		std::string filename;
		const std::string get() const;
	};
	
	class Shader {
	public:
		
		~Shader();
		Shader(GLenum type);
		
		/* Construct and compile - throws ShaderException */
		Shader(GLenum type, const GLchar *source);
		Shader(GLenum type, std::istream &source);
		Shader(GLenum type, const ShaderFile &file);
		Shader(GLenum type, const std::string &source);
		
		/* Compile - throws ShaderException */
		void compile(const GLchar *source);
		void compile(std::istream &source);
		void compile(const ShaderFile &file);
		void compile(const std::string &source);
		
		void destroy();
		bool isCompiled() const;
		GLuint getID() const;
		GLenum getType() const;
		const char *getTypeName() const;
		
	private:
		GLenum type;
		GLuint ID;
	};
	
	class VertexShader : public Shader {
	public:
		VertexShader();
		
		/* Construct and compile - throws ShaderException */
		VertexShader(const GLchar *source); 
		VertexShader(std::istream &source);
		VertexShader(const ShaderFile &file);
		VertexShader(const std::string &source);
		
	};
	
	class FragmentShader : public Shader {
	public:
		FragmentShader();
		
		/* Construct and compile - throws ShaderException */
		FragmentShader(const GLchar *source);
		FragmentShader(std::istream &source);
		FragmentShader(const ShaderFile &file);
		FragmentShader(const std::string &source);
		
	};
	
	class GeometryShader : public Shader {
	public:
		GeometryShader();
		
		/* Construct and compile - throws ShaderException */
		GeometryShader(const GLchar *source);
		GeometryShader(std::istream &source);
		GeometryShader(const ShaderFile &file);
		GeometryShader(const std::string &source);
		
	};
	
	class Program {
	public:
		Program(); ~Program();
		
		/* Vertex + Fragment - throws ShaderException */
		Program  (const ShaderFile   &vertex, const ShaderFile     &fragment);
		Program  (const VertexShader &vertex, const FragmentShader &fragment);
		void link(const VertexShader &vertex, const FragmentShader &fragment);
		void link(const ShaderFile   &vertex, const ShaderFile     &fragment);
		
		/* Vertex + Fragment + Geometry - throws ShaderException */
		Program  (const ShaderFile   &vertex, const ShaderFile     &fragment, const ShaderFile     &geometry);
		Program  (const VertexShader &vertex, const FragmentShader &fragment, const GeometryShader &geometry);
		void link(const VertexShader &vertex, const FragmentShader &fragment, const GeometryShader &geometry);
		void link(const ShaderFile   &vertex, const ShaderFile     &fragment, const ShaderFile     &geometry);
		
		void destroy();
		bool isLinked() const;
		GLuint getID() const;
		
	private:
		GLuint ID;
	};
	
}


#endif
