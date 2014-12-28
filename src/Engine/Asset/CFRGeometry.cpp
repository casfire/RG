#include "CFRGeometry.hpp"
#include "../GL/Buffer.hpp"
#include <vector>
#include <cstdint> // std::uintX_t
#include <cstddef> // std::size_t

namespace A  = Engine::Asset;
namespace GL = Engine::GL;
using std::uint8_t;
using std::uint16_t;
using std::uint32_t;
using std::size_t;

inline uint8_t read8(std::istream &in) {
	return static_cast<uint8_t>(in.get());
}

inline uint32_t read32(std::istream &in) {
	uint32_t t = 0;
	t |= static_cast<uint32_t>(in.get()) << 0;
	t |= static_cast<uint32_t>(in.get()) << 8;
	t |= static_cast<uint32_t>(in.get()) << 16;
	t |= static_cast<uint32_t>(in.get()) << 24;
	return t;
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
	default: return 0;
	}
}

inline GLboolean getGLNormalize(uint8_t type) {
	return type & 0b10000000 ? true : false;
}

void A::CFRGeometry::load(Storage&, std::istream &stream)
{
	if (read32(stream) != 0x47524643) {
		throw A::LoadException("Invalid magic number.");
	} else if (read32(stream) != 1) {
		throw A::LoadException("Invalid version.");
	}
	uint32_t countElements   = read32(stream);
	uint32_t countVertices   = read32(stream);
	uint8_t  bytesPerVertex  = read8(stream);
	uint8_t  bytesPerElement = read8(stream);
	
	uint8_t offsetPosition = read8(stream);
	uint8_t   typePosition = read8(stream);
	uint8_t offsetTexcoord = read8(stream);
	uint8_t   typeTexcoord = read8(stream);
	uint8_t offsetNormal   = read8(stream);
	uint8_t   typeNormal   = read8(stream);
	uint8_t offsetTangent  = read8(stream);
	uint8_t   typeTangent  = read8(stream);
	uint8_t offsetBinormal = read8(stream);
	uint8_t   typeBinormal = read8(stream);
	stream.ignore(4);
	
	if (!stream.good()) {
		throw A::LoadException("Failed to read header.");
	} else if (bytesPerElement == 0 || bytesPerElement == 3 || bytesPerElement > 4) {
		throw A::LoadException("Invalid number of bytes per element.");
	} else if (countElements == 0) {
		throw A::LoadException("No elements.");
	} else if (countVertices == 0 || bytesPerVertex == 0) {
		throw A::LoadException("No vertices.");
	}
	
	std::vector<char> data;
	
	data.resize(static_cast<size_t>(countVertices) * static_cast<size_t>(bytesPerVertex));
	stream.read(data.data(), data.size());
	if (!stream.good()) throw A::LoadException("Failed to read vertices.");
	GL::ArrayBuffer array(data.size(), data.data());
	
	if (offsetPosition != 0xFF && typePosition != 0xFF) {
		vao.enableAttribute(0);
		vao.attribute(
			0, array,
			getGLType(typePosition), 3,
			bytesPerVertex, offsetPosition,
			getGLNormalize(typePosition)
		);
	}
	
	if (offsetTexcoord != 0xFF && typeTexcoord != 0xFF) {
		vao.enableAttribute(1);
		vao.attribute(
			1, array,
			getGLType(typeTexcoord), 3,
			bytesPerVertex, offsetTexcoord,
			getGLNormalize(typeTexcoord)
		);
	}
	
	if (offsetNormal != 0xFF && typeNormal != 0xFF) {
		vao.enableAttribute(2);
		vao.attribute(
			2, array,
			getGLType(typeNormal), 3,
			bytesPerVertex, offsetNormal,
			getGLNormalize(typeNormal)
		);
	}
	
	if (offsetTangent != 0xFF && typeTangent != 0xFF) {
		vao.enableAttribute(3);
		vao.attribute(
			3, array,
			getGLType(typeTangent), 3,
			bytesPerVertex, offsetTangent,
			getGLNormalize(typeTangent)
		);
	}
	
	if (offsetBinormal != 0xFF && typeBinormal != 0xFF) {
		vao.enableAttribute(4);
		vao.attribute(
			4, array,
			getGLType(typeBinormal), 3,
			bytesPerVertex, offsetBinormal,
			getGLNormalize(typeBinormal)
		);
	}
	
	data.resize(static_cast<size_t>(countElements) * static_cast<size_t>(bytesPerElement));
	stream.read(data.data(), data.size());
	if (!stream.good()) throw A::LoadException("Failed to read elements.");
	
	switch (bytesPerElement) {
	case 1:
		vao.set(GL::ElementBuffer8(
			countElements, reinterpret_cast<uint8_t*>(data.data())
		));
		break;
	case 2:
		vao.set(GL::ElementBuffer16(
			countElements, reinterpret_cast<uint16_t*>(data.data())
		));
		break;
	case 4:
		vao.set(GL::ElementBuffer32(
			countElements, reinterpret_cast<uint32_t*>(data.data())
		));
		break;
	}
}

const GL::VAO& A::CFRGeometry::get()
{
	return vao;
}
