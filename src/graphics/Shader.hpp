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
		Shader(GLenum type, const GLchar *source);      /* throws ShaderException */
		Shader(GLenum type, std::istream &source);      /* throws ShaderException */
		Shader(GLenum type, const ShaderFile &file);    /* throws ShaderException */
		Shader(GLenum type, const std::string &source); /* throws ShaderException */
		void compile(const GLchar *source);      /* throws ShaderException */
		void compile(std::istream &source);      /* throws ShaderException */
		void compile(const ShaderFile &file);    /* throws ShaderException */
		void compile(const std::string &source); /* throws ShaderException */
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
		VertexShader(const GLchar *source);      /* throws ShaderException */
		VertexShader(std::istream &source);      /* throws ShaderException */
		VertexShader(const ShaderFile &file);    /* throws ShaderException */
		VertexShader(const std::string &source); /* throws ShaderException */
	};
	
	class FragmentShader : public Shader {
	public:
		FragmentShader();
		FragmentShader(const GLchar *source);      /* throws ShaderException */
		FragmentShader(std::istream &source);      /* throws ShaderException */
		FragmentShader(const ShaderFile &file);    /* throws ShaderException */
		FragmentShader(const std::string &source); /* throws ShaderException */
	};
	
	class GeometryShader : public Shader {
	public:
		GeometryShader();
		GeometryShader(const GLchar *source);      /* throws ShaderException */
		GeometryShader(std::istream &source);      /* throws ShaderException */
		GeometryShader(const ShaderFile &file);    /* throws ShaderException */
		GeometryShader(const std::string &source); /* throws ShaderException */
	};
	
	class Program {
	public:
		Program(); ~Program();
		Program(const ShaderFile &vertex, const ShaderFile &fragment);         /* throws ShaderException */
		Program(const VertexShader &vertex, const FragmentShader &fragment);   /* throws ShaderException */
		void link(const ShaderFile &vertex, const ShaderFile &fragment);       /* throws ShaderException */
		void link(const VertexShader &vertex, const FragmentShader &fragment); /* throws ShaderException */
		void destroy();
		bool isLinked() const;
		GLuint getID() const;
	private:
		GLuint ID;
	};
	
}


#endif
