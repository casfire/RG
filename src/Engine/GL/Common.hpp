#pragma once
#ifndef _ENGINE_GL_COMMON_HPP_
#define _ENGINE_GL_COMMON_HPP_

#include "gl_core_3_3.h"
#include <exception>
#include <string>

#ifdef near
	#undef near
#endif
#ifdef far
	#undef far
#endif

namespace Engine { namespace GL {
	
	
	
	class Object;
	class Exception;
	
	
	
	/* Base class for all OpenGL objects */
	class Object {
	public:
		
		/* Create object with ID */
		Object(GLuint ID);
		
		/* Get object ID */
		GLuint getObjectID() const;
		
	protected:
		
		const GLuint objectID;
		
	private:
		
		/* Prevent copying */
		Object(const Object&) = delete;
		Object& operator=(const Object&) = delete;
		
	};
	
	
	
	/* Base class for all catchable OpenGL related exceptions */
	class Exception : public std::exception {
	public:
		
		/* Create exception and save information */
		Exception(const std::string &info);
		
		/* Return saved information */
		const char* what() const throw();
		
	private:
		
		/* Saved information */
		const std::string exceptionInfo;
		
	};
	
	
	
}} // namespace Engine::GL

#endif // _ENGINE_GL_COMMON_HPP_
