#pragma once
#ifndef _GRAPHICS_GL_TEXTURE_HPP_
#define _GRAPHICS_GL_TEXTURE_HPP_

#include "Common.hpp"

namespace Graphics { namespace GL {
	
	
	
	class Texture2D : public Object {
	public:
		
		/* Create a new 2D texture */
		Texture2D();
		
		/* Create a new 2D texture and set data */
		Texture2D(GLint level, GLsizei width, GLsizei height,
			GLenum format, GLenum type, const GLvoid *data);
		
		/* Delete texture */
		~Texture2D();
		
		/* Set texture data */
		void image(GLint level, GLsizei width, GLsizei height,
			GLenum format, GLenum type, const GLvoid *data);
		
		/* Bind this texture */
		void bind();
		
		/* Unbind texure */
		void unbind();
		
	};
	
	
	
}}; // namespace Graphics::GL

#endif // _GRAPHICS_GL_TEXTURE_HPP_
