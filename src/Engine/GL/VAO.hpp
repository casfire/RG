#pragma once
#ifndef _ENGINE_GL_VAO_HPP_
#define _ENGINE_GL_VAO_HPP_

#include "Forward.hpp"
#include "Core.hpp"

namespace Engine { namespace GL {
	
	
	
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
		void enableAttribute (GLuint index);
		void disableAttribute(GLuint index);
		void attribute(
			GLuint index,
			const ArrayBuffer &v,
			GLenum type, GLint size,
			GLsizei stride, GLsizei start,
			GLboolean normalized = GL_FALSE
		);
		void attributeI(
			GLuint index,
			const ArrayBuffer &v,
			GLenum type, GLint size,
			GLsizei stride, GLsizei start
		);
		
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
