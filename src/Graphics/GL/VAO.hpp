#pragma once
#ifndef _GRAPHICS_GL_VAO_HPP_
#define _GRAPHICS_GL_VAO_HPP_

#include "Common.hpp"
#include "Buffer.hpp"

namespace Graphics { namespace GL {
	
	
	
	/* Vertex array object */
	class VAO : public Object {
	public:
		
		/* Create new VAO */
		VAO(const ArrayBuffer &array, const ElementBuffer &elements);
		
		/* Add vertex attribute */
		void attribFloat (GLuint index, GLint count, GLsizei stride, GLsizei start);
		void attribDouble(GLuint index, GLint count, GLsizei stride, GLsizei start);
		void attribUint8 (GLuint index, GLint count, GLsizei stride, GLsizei start);
		void attribSint8 (GLuint index, GLint count, GLsizei stride, GLsizei start);
		void attribUint16(GLuint index, GLint count, GLsizei stride, GLsizei start);
		void attribSint16(GLuint index, GLint count, GLsizei stride, GLsizei start);
		void attribUint32(GLuint index, GLint count, GLsizei stride, GLsizei start);
		void attribSint32(GLuint index, GLint count, GLsizei stride, GLsizei start);
		void attrib(GLenum type, GLuint index, GLint count, GLsizei stride, GLsizei start);
		
		/* Remove vertex attribute */
		void removeAttrib (GLuint index);
		
		/*  IMPORTANT!
		   Make sure the VAO is bound with VAO::bind()
		   before drawing anything
		*/
		
		void drawPoints       (GLsizei count, GLsizei start);
		void drawLines        (GLsizei count, GLsizei start);
		void drawTriangles    (GLsizei count, GLsizei start);
		void drawLineStrip    (GLsizei count, GLsizei start);
		void drawTriangleStrip(GLsizei count, GLsizei start);
		void draw (GLenum mode, GLsizei count, GLsizei start);
		
	};
	
	
	
}} // Graphics::GL

#endif // _GRAPHICS_GL_VAO_HPP_
