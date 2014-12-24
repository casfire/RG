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

void A::CFRGeometry::load(Storage&, std::istream &stream)
{
	if (read32(stream) != 0x43465247) {
		throw A::LoadException("Invalid magic number.");
	} else if (read8(stream) != 1) {
		throw A::LoadException("Invalid version.");
	}
	uint32_t elementCount = read32(stream);
	uint8_t  elementBytes = read8 (stream);
	uint8_t  elementType  = read8 (stream);
	uint32_t vertexCount  = read32(stream);
	uint8_t  vertexBytes  = read8 (stream);
	uint8_t  vertexType   = read8 (stream);
	if (!stream.good()) {
		throw A::LoadException("Failed to read header.");
	} else if (elementBytes == 0 || elementBytes == 3 || elementBytes > 4) {
		throw A::LoadException("Invalid number of bytes per element.");
	} else if (elementType > 6) {
		throw A::LoadException("Invalid element type.");
	} else if (elementCount == 0) {
		throw A::LoadException("No elements.");
	} else if (vertexCount == 0) {
		throw A::LoadException("No vertices.");
	}
	uint8_t positionCount = (vertexType & 0b00000011) >> 0;
	uint8_t normalCount   = (vertexType & 0b00001100) >> 2;
	uint8_t textureCount  = (vertexType & 0b00110000) >> 4;
	if (positionCount != 3) {
		throw A::LoadException("Invalid position count.");
	} else if (normalCount != 3) {
		throw A::LoadException("Invalid normal count.");
	} else if (textureCount == 1 || textureCount == 3) {
		throw A::LoadException("Invalid texture count.");
	} else if (4 * (positionCount + normalCount + textureCount) != vertexBytes) {
		throw A::LoadException("Invalid number of bytes per vertex.");
	}
	
	std::vector<char> data;
	
	data.resize(static_cast<size_t>(vertexCount) * static_cast<size_t>(vertexBytes));
	stream.read(data.data(), data.size());
	if (!stream.good()) throw A::LoadException("Failed to read vertices.");
	GL::ArrayBuffer array(data.size(), data.data());
	vao.enableAttribute(0);
	vao.attribute(0, array, GL_FLOAT, 3, vertexBytes, 0 * 4);
	vao.enableAttribute(1);
	vao.attribute(1, array, GL_FLOAT, 3, vertexBytes, 3 * 4);
	if (textureCount == 2) {
		vao.enableAttribute(2);
		vao.attribute(2, array, GL_FLOAT, 2, vertexBytes, 6 * 4);
	}
	
	data.resize(static_cast<size_t>(elementCount) * static_cast<size_t>(elementBytes));
	stream.read(data.data(), data.size());
	if (!stream.good()) throw A::LoadException("Failed to read elements.");
	switch (elementBytes) {
	case 1:
		vao.set(GL::ElementBuffer8(
			elementCount, reinterpret_cast<uint8_t*>(data.data())
		));
		break;
	case 2:
		vao.set(GL::ElementBuffer16(
			elementCount, reinterpret_cast<uint16_t*>(data.data())
		));
		break;
	case 4:
		vao.set(GL::ElementBuffer32(
			elementCount, reinterpret_cast<uint32_t*>(data.data())
		));
		break;
	}
}

const GL::VAO& A::CFRGeometry::get()
{
	return vao;
}
