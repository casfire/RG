#pragma once
#ifndef _ENGINE_GL_VAO_HPP_
#define _ENGINE_GL_VAO_HPP_

#include "Common.hpp"

namespace Engine { namespace GL {
	
	
	
	class Buffer;
	class ElementBuffer;
	class ArrayBuffer;
	
	
	
	/* Vertex array object */
	class VAO : public Object {
	public:
		
		/* Create a new VAO */
		VAO(const ElementBuffer &elements);
		VAO();
		
		/* Delete VAO */
		~VAO();
		
		/* Bind VAO */
		void bind() const;
		
		/* Unbind VAO */
		void unbind() const;
		
		/* Set element buffer */
		void set(const ElementBuffer &elements);
		
		/* Set vertex atributes */
		void enable    (GLuint index);
		void disable   (GLuint index);
		void attribute (GLuint index, const ArrayBuffer &v, GLenum type, GLint count,
			GLsizei stride, GLsizei start, GLboolean normalized = GL_FALSE);
		void attributeI(GLuint index, const ArrayBuffer &v, GLenum type, GLint count,
			GLsizei stride, GLsizei start);
		
		/* Draw */
		void drawPoints() const;
		void drawLines() const;
		void drawTriangles() const;
		void drawLineStrip() const;
		void drawLineLoop() const;
		void drawTriangleStrip() const;
		void drawTriangleFan() const;
		void draw(GLenum mode) const;
		void draw(GLenum mode, GLsizei count, GLsizei offset) const;
		
	private:
		
		GLenum type;
		GLsizei count;
		
	};
	
	
	
}} // namespace Engine::GL

#endif // _ENGINE_GL_VAO_HPP_
