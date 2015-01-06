#pragma once
#ifndef _ENGINE_ASSET_CFRGEOMETRY_HPP_
#define _ENGINE_ASSET_CFRGEOMETRY_HPP_

#include "Forward.hpp"
#include "Base.hpp"
#include "../GL/VAO.hpp"
#include <istream>

namespace Engine { namespace Asset {
	
	
	
	/* CFR Geometry asset */
	class CFRGeometry : public BaseAsset {
	public:
		
		/* Load geometry */
		void load(Storage &storage, std::istream &stream) override;
		
		/* Return loaded geometry */
		const GL::VAO& get();
		
	private:
		
		GL::VAO vao;
		
	};
	
	
	
	/*
		CFR Geometry file format
		Byte order: little endian
		
		Uint32 magic = 0x47524643; // CFRG
		Uint32 version = 1;
		Uint32 countElements;     // Number of elements
		Uint32 countVertices;     // Number of vertices
		Uint8  bytesPerVertex;    // Bytes per vertex
		Uint8  bytesPerElement;   // Bytes per element (1, 2 or 4)
		Uint8  attribPosition[2]; // Vertex position (3 dimensions)
		Uint8  attribTexCoord[2]; // Vertex UV       (2 dimensions)
		Uint8  attribNormal  [2]; // Vertex normal   (3 dimensions)
		Uint8  attribTangent [2]; // Vertex tangent  (4 dimensions)
		Uint8  unused[6];
		Uint8  vertices[countVertices * bytesPerVertex ];
		Uint8  elements[countElements * bytesPerElement];
		
		Attributes:
			attribute[0] = Byte offset within a vertex
			attribute[1] = Attribute type
			If offset or type is 0xFF, the attribute isn't used
		
		Attribute type:
			Normalize     = type & 0b10000000
			Variable type = type & 0b01111111
		
		Attribute variable types:
			0  - Signed   byte  (GL_BYTE)
			1  - Unsigned byte  (GL_UNSIGNED_BYTE)
			2  - Signed   short (GL_SHORT)
			3  - Unsigned short (GL_UNSIGNED_SHORT)
			4  - Signed   int   (GL_INT)
			5  - Unsigned int   (GL_UNSIGNED_INT)
			6  - Float          (GL_FLOAT)
			10 - Double         (GL_DOUBLE)
			11 - Half float     (GL_HALF_FLOAT)
		
		Tangent space:
			Fourth tangent dimension is either 1 or -1
			Binormal = cross(tangent.xyz, normal) * tangent.w
		
	*/
	
	
	
}} // namespace Engine::Asset

#endif // _ENGINE_ASSET_CFRGEOMETRY_HPP_
