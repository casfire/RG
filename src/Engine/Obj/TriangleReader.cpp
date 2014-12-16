#include "TriangleReader.hpp"

namespace Obj = Engine::Obj;

const std::vector<Obj::TriangleVertex>& Obj::TriangleReader::vertices() const
{
	return eVertices;
}

const std::vector<Obj::TriangleFace>& Obj::TriangleReader::triangles() const
{
	return eTriangles;
}

void Obj::TriangleReader::clear()
{
	eVertices.clear();
	eTriangles.clear();
	objGeometry.clear();
	objTexture.clear();
	objNormal.clear();
	eAddedVertices.clear();
}

bool Obj::TriangleReader::parse(Obj::Vertex::Geometry &v)
{
	objGeometry.push_back(v);
	return true;
}

bool Obj::TriangleReader::parse(Obj::Vertex::Texture &v)
{
	objTexture.push_back(v);
	return true;
}

bool Obj::TriangleReader::parse(Obj::Vertex::Normal &v)
{
	objNormal.push_back(v);
	return true;
}

bool Obj::TriangleReader::parse(Obj::Element::Face &e)
{
	for (std::size_t i = 2; i < e.size(); i++) {
		addTriangle(e[0], e[i - 1], e[i]);
	}
	return true;
}

void Obj::TriangleReader::addTriangle(Obj::Element::FaceVertex a, Obj::Element::FaceVertex b, Obj::Element::FaceVertex c)
{
	Obj::TriangleFace f;
	f.a = addVertex(a);
	f.b = addVertex(b);
	f.c = addVertex(c);
	eTriangles.push_back(f);
}

std::size_t Obj::TriangleReader::addVertex(Obj::Element::FaceVertex v)
{
	std::size_t size = eAddedVertices.size();
	for (std::size_t i = 0; i < size; i++) {
		if (isSame(eAddedVertices[i], v)) {
			return i;
		}
	}
	TriangleVertex tv;
	tv.geometry = objGeometry[v.v - 1];
	tv.hasTexture = v.hasTexture;
	if (v.hasTexture) tv.texture = objTexture[v.vt - 1];
	tv.hasNormal = v.hasNormal;
	if (v.hasNormal) tv.normal = objNormal[v.vn - 1];
	eVertices.push_back(tv);
	eAddedVertices.push_back(v);
	return size;
}

bool Obj::TriangleReader::isSame(Obj::Element::FaceVertex a, Obj::Element::FaceVertex b)
{
	
	return a.v == b.v
		&& a.hasTexture == b.hasTexture
		&& a.hasNormal == b.hasNormal
		&& (!a.hasTexture || (a.vt == b.vt))
		&& (!a.hasNormal || (a.vn == b.vn));
}
