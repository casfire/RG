#pragma once
#ifndef _ENGINE_GL_BUFFER_HPP_
#define _ENGINE_GL_BUFFER_HPP_

#include "Forward.hpp"
#include "Core.hpp"
#include <cstdint>

namespace Engine { namespace GL {
	
	
	
	/* Base buffer object */
	class Buffer : public Object {
	public:
		
		/* Create a new buffer */
		Buffer(GLenum target, GLenum usage);
		
		/* Create a new buffer and set buffer data */
		Buffer(GLenum target, GLenum usage, GLsizeiptr size, const GLvoid *data);
		
		/* Delete the buffer */
		~Buffer();
		
		/* Set buffer data */
		void data(GLsizeiptr size, const GLvoid *data);
		
		/* Update buffer data */
		void subData(GLintptr offset, GLsizeiptr size, const GLvoid *data);
		
		/* Bind this buffer */
		void bind() const;
		
		/* Unbind buffer */
		void unbind() const;
		
		/* Getters */
		GLenum getTarget() const;
		GLenum getUsage() const;
		
	private:
		
		const GLenum target, usage;
		
	};
	
	
	
	/* Base element buffer object */
	class ElementBuffer : public Buffer {
	public:
		
		/* Getters */
		GLenum getType() const;
		GLsizei getCount() const;
		virtual GLsizei getBytes() const = 0;
		
	protected:
	
		ElementBuffer(GLenum type, GLenum usage);
		const GLenum type;
		GLsizei count;
		
	};
	
	
	/* 8-bit Element buffer */
	class ElementBuffer8 : public ElementBuffer {
	public:
		
		/* Create element buffer */
		ElementBuffer8(GLenum usage = GL_STATIC_DRAW);
		
		/* Create element buffer and set elements */
		ElementBuffer8(
			GLsizei count, const std::uint8_t *elements,
			GLenum usage = GL_STATIC_DRAW
		);
		
		/* Return 1 */
		GLsizei getBytes() const override;
		
		/* Set elements */
		void elements(GLsizei count, const std::uint8_t *elements);
		
	};
	
	
	
	/* 16-bit Element buffer */
	class ElementBuffer16 : public ElementBuffer {
	public:
		
		/* Create element buffer */
		ElementBuffer16(GLenum usage = GL_STATIC_DRAW);
		
		/* Create element buffer and set elements */
		ElementBuffer16(
			GLsizei count, const std::uint16_t *elements,
			GLenum usage = GL_STATIC_DRAW
		);
		
		/* Return 2 */
		GLsizei getBytes() const override;
		
		/* Set elements */
		void elements(GLsizei count, const std::uint16_t *elements);
		
	};
	
	
	
	/* 32-bit Element buffer */
	class ElementBuffer32 : public ElementBuffer {
	public:
		
		/* Create element buffer */
		ElementBuffer32(GLenum usage = GL_STATIC_DRAW);
		
		/* Create element buffer and set elements */
		ElementBuffer32(
			GLsizei count, const std::uint32_t *elements,
			GLenum usage = GL_STATIC_DRAW
		);
		
		/* Return 4 */
		GLsizei getBytes() const override;
		
		/* Set elements */
		void elements(GLsizei count, const std::uint32_t *elements);
		
	};
	
	
	
	/* Array buffer object */
	class ArrayBuffer : public Buffer {
	public:
		
		/* Create a new array buffer */
		ArrayBuffer(GLenum usage = GL_STATIC_DRAW);
		
		/* Create a new array buffer and set buffer data */
		ArrayBuffer(
			GLsizeiptr size, const GLvoid *data,
			GLenum usage = GL_STATIC_DRAW
		);
		
	};
	
	
	
	/* Uniform buffer object */
	class UniformBuffer : public Buffer {
	public:
		
		/* Create a new uniform buffer */
		UniformBuffer(GLenum usage = GL_STREAM_DRAW);
		
		/* Create a new uniform buffer and set buffer data */
		UniformBuffer(
			GLsizeiptr size, const GLvoid *data,
			GLenum usage = GL_STREAM_DRAW
		);
		
	};
	
	
	
}} // namespace Engine::GL

#endif // _ENGINE_GL_BUFFER_HPP_
