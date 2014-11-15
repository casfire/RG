#pragma once
#ifndef _ENGINE_GL_PROGRAM_HPP_
#define _ENGINE_GL_PROGRAM_HPP_

#include "Common.hpp"
#include "Shader.hpp"
#include <vector>
#include <glm/glm.hpp>

namespace Engine { namespace GL {
	
	
	
	class Program;
	class ProgramUniform;
	class ProgramLinkException;
	
	
	
	/* GLSL program object */
	class Program : public Object {
	public:
		
		/* Create a new program */
		Program();
		
		/* Delete program */
		~Program();
		
		/* Create and link a new program - throws ProgramLinkException */
		Program(const VertexShader &vertex, const FragmentShader &fragment);
		Program(const VertexShader &vertex, const FragmentShader &fragment,
			const GeometryShader &geometry);
		
		/* Attach a shader */
		void attach(const Shader &shader);
		
		/* Detach a shader */
		void detach(const Shader &shader);
		
		/* Link attached shaders - throws ProgramLinkException */
		void link();
		
		/* Use this program */
		void bind() const;
		
		/* Stop using program */
		void unbind() const;
		
		/* Getters */
		bool isLinked() const;
		bool isAttached(const Shader &shader) const;
		
		/* Retrieve uniform variable */
		ProgramUniform getUniform(const GLchar *name);
		
	};
	
	
	
	/* Program uniform variable */
	class ProgramUniform {
	public:
		
		/* Retrieve uniform variable */
		ProgramUniform(const Program &program, const GLchar *name);
		
		/* Get location of the uniform */
		GLuint getLocation() const;
		
		/*  IMPORTANT!
		  Make sure the program is bound with Program::bind()
		  before setting the variable
		*/
		
		void set1f(GLfloat v0);
		void set2f(GLfloat v0, GLfloat v1);
		void set3f(GLfloat v0, GLfloat v1, GLfloat v2);
		void set4f(GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
		
		void set1i(GLint v0);
		void set2i(GLint v0, GLint v1);
		void set3i(GLint v0, GLint v1, GLint v2);
		void set4i(GLint v0, GLint v1, GLint v2, GLint v3);
		
		void set1fv(GLsizei count, const GLfloat *value);
		void set2fv(GLsizei count, const GLfloat *value);
		void set3fv(GLsizei count, const GLfloat *value);
		void set4fv(GLsizei count, const GLfloat *value);
		
		void set1iv(GLsizei count, const GLint *value);
		void set2iv(GLsizei count, const GLint *value);
		void set3iv(GLsizei count, const GLint *value);
		void set4iv(GLsizei count, const GLint *value);
		
		void setMatrix2fv(GLsizei count, GLboolean transpose, const GLfloat *value);
		void setMatrix3fv(GLsizei count, GLboolean transpose, const GLfloat *value);
		void setMatrix4fv(GLsizei count, GLboolean transpose, const GLfloat *value);
		
		void set(const glm::mat2 &mat);
		void set(const glm::mat3 &mat);
		void set(const glm::mat4 &mat);
		
	private:
		
		const GLuint location;
		
	};
	
	
	
	/* Exception thrown when program link fails */
	class ProgramLinkException : public Exception {
	public:
		
		/* Return entire link log */
		const char* log() const;
		
	private:
		
		friend class Program;
		std::vector<char> linkLog;
		ProgramLinkException(const Program &program);
		
	};
	
	
	
}} // namespace Engine::GL

#endif // _ENGINE_GL_PROGRAM_HPP_
