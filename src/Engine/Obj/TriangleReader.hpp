#pragma once
#ifndef _ENGINE_OBJ_TRIANGLEREADER_HPP_
#define _ENGINE_OBJ_TRIANGLEREADER_HPP_

#include "Reader.hpp"
#include <cstddef> // std::size_t

namespace Engine { namespace Obj {
	
	
	
	struct TriangleVertex {
		Vertex::Geometry geometry;
		Vertex::Texture texture;
		Vertex::Normal normal;
		bool hasTexture, hasNormal;
	};
	
	struct TriangleFace {
		std::size_t a, b, c;
	};
	
	
	
	/* Reader that builds vertices and triangles */
	class TriangleReader : public ObjectReader {
	public:
		
		/* Getters */
		const std::vector<TriangleVertex>& vertices() const;
		const std::vector<TriangleFace>& triangles() const;
		
		/* Delete everything */
		void clear();
		
	protected:
		
		/* Vertex data */
		bool parse(Vertex::Geometry &v) override;
		bool parse(Vertex::Texture &v) override;
		bool parse(Vertex::Normal &v) override;
		
		/* Elements */
		bool parse(Element::Face &e) override;
		
	private:
		
		std::vector<TriangleVertex> eVertices;
		std::vector<TriangleFace> eTriangles;
		
		std::vector<Vertex::Geometry> objGeometry;
		std::vector<Vertex::Texture> objTexture;
		std::vector<Vertex::Normal> objNormal;
		std::vector<Element::FaceVertex> eAddedVertices;
		
		void addTriangle(Element::FaceVertex a, Element::FaceVertex b, Element::FaceVertex c);
		std::size_t addVertex(Element::FaceVertex v);
		bool isSame(Element::FaceVertex a, Element::FaceVertex b);
		
	};
	
	
	
}} // namespace Engine::Obj

#endif // _ENGINE_OBJ_TRIANGLEREADER_HPP_
