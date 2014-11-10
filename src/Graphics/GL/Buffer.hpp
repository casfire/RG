#pragma once
#ifndef _GRAPHICS_GL_BUFFER_HPP_
#define _GRAPHICS_GL_BUFFER_HPP_

#include "Common.hpp"
#include <cstdint> // std::uint8_t, std::uint16_t, std::uint32_t
#include <cstddef> // std::size_t

namespace Graphics { namespace GL {
	
	
	
	class Buffer;
	class ElementBuffer;
	class ElementBuffer8;
	class ElementBuffer16;
	class ElementBuffer32;
	class ArrayBuffer;
	
	
	
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
		
		/* Bind the buffer */
		void bind() const;
		
		/* Unbind the buffer */
		void unbind() const;
		
		/* Getters */
		GLenum getTarget() const;
		GLenum getUsage() const;
		const char* getTargetName() const;
		const char* getUsageName() const;
		
	private:
		
		const GLenum target, usage;
		
	};
	
	
	
	/* Base element buffer object */
	class ElementBuffer : public Buffer {
	public:
		
		/* Create element buffer */
		ElementBuffer(GLenum type, GLenum usage);
		
		/* Getters */
		GLenum getType();
		const char* getTypeName();
		int getTypeBits();
		
	protected:
	
		const GLenum type;
		
	};
	
	
	
	/* 8-bit Element buffer */
	class ElementBuffer8 : public ElementBuffer {
	public:
		
		/* Create element buffer */
		ElementBuffer8(GLenum usage = GL_STATIC_DRAW);
		
		/* Create element buffer and set elements */
		ElementBuffer8(std::size_t count, const std::uint8_t *elements,
			GLenum usage = GL_STATIC_DRAW);
		
		/* Set elements */
		void elements(std::size_t count, const std::uint8_t *elements);
		
	};
	
	
	
	/* 16-bit Element buffer */
	class ElementBuffer16 : public ElementBuffer {
	public:
		
		/* Create element buffer */
		ElementBuffer16(GLenum usage = GL_STATIC_DRAW);
		
		/* Create element buffer and set elements */
		ElementBuffer16(std::size_t count, const std::uint16_t *elements,
			GLenum usage = GL_STATIC_DRAW);
		
		/* Set elements */
		void elements(std::size_t count, const std::uint16_t *elements);
		
	};
	
	
	
	/* 32-bit Element buffer */
	class ElementBuffer32 : public ElementBuffer {
	public:
		
		
		/* Create element buffer */
		ElementBuffer32(GLenum usage = GL_STATIC_DRAW);
		
		/* Create element buffer and set elements */
		ElementBuffer32(std::size_t count, const std::uint32_t *elements,
			GLenum usage = GL_STATIC_DRAW);
		
		/* Set elements */
		void elements(std::size_t count, const std::uint32_t *elements);
		
		
	};
	
	
	
	/* Array buffer object */
	class ArrayBuffer : public Buffer {
	public:
		
		/* Create a new array buffer */
		ArrayBuffer(GLenum usage = GL_STATIC_DRAW);
		
		/* Create a new array buffer and set buffer data */
		ArrayBuffer(GLsizeiptr size, const GLvoid *data,
			GLenum usage = GL_STATIC_DRAW);
		
	};
	
	
	
}} // namespace Graphics::GL

#endif // _GRAPHICS_GL_BUFFER_HPP_
