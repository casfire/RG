#pragma once
#ifndef _ENGINE_GL_TEXTURE_HPP_
#define _ENGINE_GL_TEXTURE_HPP_

#include "Forward.hpp"
#include "Core.hpp"

namespace Engine { namespace GL {
	
	
	
	class Texture : public Object {
	public:
		
		/* Create a new texture */
		Texture(GLenum target);
		
		/* Delete texture */
		~Texture();
		
		/* Bind this texture */
		void bind() const;
		
		/* Unbind texure */
		void unbind() const;
		
	protected:
		
		const GLenum target;
		
	};
	
	
	
	class Texture1D : public Texture {
	public:
		
		/* Create a new 1D texture */
		Texture1D();
		
		/* Create a new 1D texture and set pixel data */
		Texture1D(
			GLsizei width,
			GLenum format, GLenum type, const GLvoid *data, bool compress = true
		);
		
		/* Set pixel data */
		void setPixels(
			GLsizei width,
			GLenum format, GLenum type, const GLvoid *data, bool compress = true
		);
		
	};
	
	
	
	class Texture2D : public Texture {
	public:
		
		/* Create a new 2D texture */
		Texture2D();
		
		/* Create a new 2D texture and set pixel data */
		Texture2D(
			GLsizei width, GLsizei height,
			GLenum format, GLenum type, const GLvoid *data, bool compress = true
		);
		
		/* Set pixel data */
		void setPixels(
			GLsizei width, GLsizei height,
			GLenum format, GLenum type, const GLvoid *data, bool compress = true
		);
		
	};
	
	
	
	class Texture3D : public Texture {
	public:
		
		/* Create a new 2D texture */
		Texture3D();
		
		/* Create a new 2D texture and set pixel data */
		Texture3D(
			GLsizei width, GLsizei height, GLsizei depth,
			GLenum format, GLenum type, const GLvoid *data, bool compress = true
		);
		
		/* Set pixel data */
		void setPixels(
			GLsizei width, GLsizei height, GLsizei depth,
			GLenum format, GLenum type, const GLvoid *data, bool compress = true
		);
		
	};
	
	
	
}} // namespace Engine::GL

#endif // _ENGINE_GL_TEXTURE_HPP_
