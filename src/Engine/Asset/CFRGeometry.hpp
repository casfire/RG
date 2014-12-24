#pragma once
#ifndef _ENGINE_ASSET_CFRGEOMETRY_HPP_
#define _ENGINE_ASSET_CFRGEOMETRY_HPP_

#include "Common.hpp"
#include "../GL/VAO.hpp"
#include <istream>

namespace Engine { namespace Asset {
	
	
	
	/* CFR Geometry asset */
	class CFRGeometry : public virtual Asset {
	public:
		
		/* Load geometry */
		void load(Storage &storage, std::istream &stream) override;
		
		/* Return loaded geometry */
		const GL::VAO& get();
		
	private:
		
		GL::VAO vao;
		
	};
	
	
	
	/*
		CFR geometry file format
		Byte order: little endian
		
		uint32_t  magic = 0x43465247; (CFRG)
		uint8_t   version = 1;
		uint32_t  elementCount; // Number of elements
		uint8_t   elementBytes; // Number of bytes per element (1, 2 or 4)
		uint8_t   elementType;  // Type of elements
		uint32_t  vertexCount;  // Number of vertices
		uint8_t   vertexBytes;  // Number of bytes per vertex
		uint8_t   vertexType;   // Type of vertices
		float     vertices[vertexCount  * vertexBytes / 4];
		uint8_t   elements[elementCount * elementBytes];
		
		Vertex type:
			(vertexType & 0b00000011) >> 0 = Number of floats for position
			(vertexType & 0b00001100) >> 2 = Number of floats for normal
			(vertexType & 0b00110000) >> 4 = Number of floats for texture
			(vertexType & 0b11000000) >> 6 = Unused
			
			Common types:
			47 - 0b00101111 - position[3] + normal [3] + texture[2]
			15 - 0b00001111 - position[3] + normal [3]
			35 - 0b00100011 - position[3] + texture[2]
			3  - 0b00000011 - position[3]
			
			vertexBytes can be calculated from vertexType, but not vice versa
		
		Element type:
			0 - points         (GL_POINTS)
			1 - lines          (GL_LINES)
			2 - line loop      (GL_LINE_LOOP)
			3 - line strip     (GL_LINE_STRIP)
			4 - triangles      (GL_TRIANGLES)
			5 - triangle strip (GL_TRIANGLE_STRIP)
			6 - triangle fan   (GL_TRIANGLE_FAN)
		
	*/
	
	
	
}} // namespace Engine::Asset

#endif // _ENGINE_ASSET_CFRGEOMETRY_HPP_
