#pragma once
#ifndef _ENGINE_GL_CORE_HPP_
#define _ENGINE_GL_CORE_HPP_

#include "Forward.hpp"
#include "gl_core_3_3.h"
#ifdef near
	#undef near
#endif
#ifdef far
	#undef far
#endif
#include <exception>
#include <string>

namespace Engine { namespace GL {
	
	
	
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
	class BaseException : public std::exception {
	public:
		
		/* Create exception and save information */
		BaseException(const std::string &info);
		
		/* Return saved information */
		const char* what() const throw();
		
	private:
		
		/* Saved information */
		const std::string exceptionInfo;
		
	};
	
	
	
	/* Get OpenGL information */
	extern std::string getString(GLenum name);
	extern std::string getVendor();
	extern std::string getRenderer();
	extern std::string getVersion();
	extern std::string getGLSLVersion();
	extern std::string getExtensions();
	
	
	
}} // namespace Engine::GL

#endif // _ENGINE_GL_BASE_HPP_
