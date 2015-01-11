#include "CFRGeometry.hpp"
#include "../GL/Buffer.hpp"
#include <vector>
#include <cstdint> // std::uintX_t
#include <cstddef> // std::size_t

namespace GL = Engine::GL;
using Engine::Asset::LoadException;
using Engine::Asset::CFRGeometry;
using std::uint8_t;
using std::uint16_t;
using std::uint32_t;
using std::size_t;

struct CFRGHeader {
	uint32_t magic;
	uint32_t version;
	uint32_t countElements;
	uint32_t countVertices;
	uint8_t  bytesPerVertex;
	uint8_t  bytesPerElement;
	uint8_t  offsetPosition;
	uint8_t    typePosition;
	uint8_t  offsetTexcoord;
	uint8_t    typeTexcoord;
	uint8_t  offsetNormal;
	uint8_t    typeNormal;
	uint8_t  offsetTangent;
	uint8_t    typeTangent;
	uint8_t  unused1, unused2, unused3, unused4, unused5, unused6;
	inline void read(std::istream &stream);
	inline void readVertices(std::istream &stream, std::vector<char> &data);
	inline void readElements(std::istream &stream, std::vector<char> &data);
};

void CFRGHeader::read(std::istream &stream) {
	stream.read(reinterpret_cast<char*>(this), 32);
	if (!stream.good()) {
		throw LoadException("Failed to read header.");
	} else if (magic != 0x47524643) {
		throw LoadException("Invalid magic number.");
	} else if (version != 1) {
		throw LoadException("Invalid version.");
	} else if (countElements == 0) {
		throw LoadException("No elements.");
	} else if (countVertices == 0 || bytesPerVertex == 0) {
		throw LoadException("No vertices.");
	}
}

void CFRGHeader::readVertices(std::istream &stream, std::vector<char> &data) {
	data.resize(static_cast<size_t>(countVertices) * static_cast<size_t>(bytesPerVertex));
	stream.read(data.data(), data.size());
	if (!stream.good()) throw LoadException("Failed to read vertices.");
}

void CFRGHeader::readElements(std::istream &stream, std::vector<char> &data) {
	data.resize(static_cast<size_t>(countElements) * static_cast<size_t>(bytesPerElement));
	stream.read(data.data(), data.size());
	if (!stream.good()) throw LoadException("Failed to read elements.");
}

inline GLenum getGLType(uint8_t type) {
	switch (type & 0b01111111) {
	case 0:  return GL_BYTE;
	case 1:  return GL_UNSIGNED_BYTE;
	case 2:  return GL_SHORT;
	case 3:  return GL_UNSIGNED_SHORT;
	case 4:  return GL_INT;
	case 5:  return GL_UNSIGNED_INT;
	case 6:  return GL_FLOAT;
	case 10: return GL_DOUBLE;
	case 11: return GL_HALF_FLOAT;
	default: return GL_INVALID_ENUM;
	}
}

inline GLboolean getGLNormalize(uint8_t type) {
	return type & 0b10000000 ? GL_TRUE : GL_FALSE;
}

void CFRGeometry::load(Storage&, std::istream &stream)
{
	CFRGHeader header;
	header.read(stream);
	
	GLenum glTypePositon  = getGLType(header.typePosition);
	GLenum glTypeTexcoord = getGLType(header.typeTexcoord);
	GLenum glTypeNormal   = getGLType(header.typeNormal);
	GLenum glTypeTangent  = getGLType(header.typeTangent);
	
	std::vector<char> data;
	header.readVertices(stream, data);
	GL::ArrayBuffer array(data.size(), data.data());
	
	if (header.offsetPosition != 0xFF && glTypePositon != GL_INVALID_ENUM) {
		enableAttribute(0);
		attribute(
			0, array,
			glTypePositon, 3,
			header.bytesPerVertex, header.offsetPosition,
			getGLNormalize(header.typePosition)
		);
	}
	
	if (header.offsetTexcoord != 0xFF && glTypeTexcoord != GL_INVALID_ENUM) {
		enableAttribute(1);
		attribute(
			1, array,
			glTypeTexcoord, 2,
			header.bytesPerVertex, header.offsetTexcoord,
			getGLNormalize(header.typeTexcoord)
		);
	}
	
	if (header.offsetNormal != 0xFF && glTypeNormal != GL_INVALID_ENUM) {
		enableAttribute(2);
		attribute(
			2, array,
			glTypeNormal, 3,
			header.bytesPerVertex, header.offsetNormal,
			getGLNormalize(header.typeNormal)
		);
	}
	
	if (header.offsetTangent != 0xFF && glTypeTangent != GL_INVALID_ENUM) {
		enableAttribute(3);
		attribute(
			3, array,
			glTypeTangent, 4,
			header.bytesPerVertex, header.offsetTangent,
			getGLNormalize(header.typeTangent)
		);
	}
	
	header.readElements(stream, data);
	switch (header.bytesPerElement) {
	case 1:
		set(GL::ElementBuffer8(
			header.countElements, reinterpret_cast<uint8_t*>(data.data())
		));
		break;
	case 2:
		set(GL::ElementBuffer16(
			header.countElements, reinterpret_cast<uint16_t*>(data.data())
		));
		break;
	case 4:
		set(GL::ElementBuffer32(
			header.countElements, reinterpret_cast<uint32_t*>(data.data())
		));
		break;
	}
}
