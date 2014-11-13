#pragma once
#ifndef _GRAPHICS_GL_COMMON_HPP_
#define _GRAPHICS_GL_COMMON_HPP_

#include "gl_core_3_3.h"
#include <exception> // std::exception
#include <string> // std::string

namespace Graphics { namespace GL {
	
	
	
	class Object;
	class Exception;
	class VAO;
	
	
	/* Base class for all OpenGL objects */
	class Object {
	public:
		
		/* Create object with ID */
		Object(GLuint ID);
		
		/* Get object ID */
		GLuint getObjectID() const;
		
	protected:
		
		const GLuint objectID;
		
	};
	
	
	
	/* Base class for all catchable OpenGL related exceptions */
	class Exception : public std::exception {
	public:
		
		/* Create exception and save information */
		Exception(const std::string &info);
		
		/* Return saved information */
		const char* what() const throw();
		
	private:
		
		const std::string exceptionInfo;
		
	};
	
	
	
	/* Vertex array object */
	class VAO : public Object {
	public:
		
		/* Create a new VAO */
		VAO();
		
		/* Bind this VAO */
		void bind() const;
		
		/* Unbind VAO */
		void unbind() const;
		
	};
	
	
	
}} // namespace Graphics::GL

#endif // _GRAPHICS_GL_COMMON_HPP_
