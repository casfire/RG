#pragma once
#ifndef _ENGINE_GL_UNIFORM_HPP_
#define _ENGINE_GL_UNIFORM_HPP_

#include "Forward.hpp"
#include "Core.hpp"
#include <glm/mat4x4.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat2x2.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace Engine { namespace GL {
	
	
	
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
		
		void set(const glm::vec2 &vec);
		void set(const glm::vec3 &vec);
		void set(const glm::vec4 &vec);
		
	private:
		
		const GLuint location;
		
	};
	
	
	
}} // namespace Engine::GL

#endif // _ENGINE_GL_UNIFORM_HPP_
