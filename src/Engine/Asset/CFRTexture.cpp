#include "CFRTexture.hpp"
#include <vector>
#include <cstdint> // std::uintX_t
#include <cstddef> // std::size_t

namespace GL = Engine::GL;
using Engine::Asset::LoadException;
using Engine::Asset::CFRTexture1D;
using Engine::Asset::CFRTexture2D;
using Engine::Asset::CFRTexture3D;
using std::uint8_t;
using std::uint16_t;
using std::uint32_t;
using std::size_t;



/* CFRT Header */

struct CFRTHeader {
	uint32_t magic;
	uint32_t version;
	uint16_t width;
	uint16_t height;
	uint16_t depth;
	uint8_t  channels;
	uint8_t  bytes;
	inline void read(std::istream &stream);
	inline void readPixels(std::istream &stream, std::vector<char> &pixels);
	inline GLenum getFormat();
	inline GLenum getType();
	inline size_t getSize();
};

void CFRTHeader::read(std::istream &stream) {
	stream.read(reinterpret_cast<char*>(this), 16);
	if (!stream.good()) {
		throw LoadException("Failed to read header.");
	} else if (magic != 0x54524643) {
		throw LoadException("Invalid magic number.");
	} else if (version != 1) {
		throw LoadException("Invalid version.");
	} else if (channels == 0 || channels > 4) {
		throw LoadException("Invalid number of channels.");
	} else if (bytes == 0 || bytes == 3 || bytes > 4) {
		throw LoadException("Invalid number of bytes per color.");
	}
}

void CFRTHeader::readPixels(std::istream &stream, std::vector<char> &pixels)
{
	pixels.resize(getSize());
	stream.read(pixels.data(), pixels.size());
	if (!stream.good()) throw LoadException("Failed to read pixels.");
}

GLenum CFRTHeader::getFormat() {
	switch (channels) {
	default:
	case 4: return GL_RGBA;
	case 3: return GL_RGB;
	case 2: return GL_RG;
	case 1: return GL_RED;
	}
}

GLenum CFRTHeader::getType() {
	switch (bytes) {
	default:
	case 1: return GL_UNSIGNED_BYTE;
	case 2: return GL_UNSIGNED_SHORT;
	case 4: return GL_UNSIGNED_INT;
	}
}

size_t CFRTHeader::getSize()
{
	return
		  static_cast<size_t>(width)
		* static_cast<size_t>(height)
		* static_cast<size_t>(depth)
		* static_cast<size_t>(channels)
		* static_cast<size_t>(bytes);
}



/* CFRTexture1D */

void CFRTexture1D::load(Storage&, std::istream &stream)
{
	CFRTHeader header;
	header.read(stream);
	if (header.depth  != 1) throw LoadException("Depth is not 1.");
	if (header.height != 1) throw LoadException("Height is not 1.");
	std::vector<char> pixels;
	header.readPixels(stream, pixels);
	texture.setPixels(
		header.width,
		header.getFormat(), header.getType(), pixels.data()
	);
}

const GL::Texture1D& CFRTexture1D::get()
{
	return texture;
}



/* CFRTexture2D */

void CFRTexture2D::load(Storage&, std::istream &stream)
{
	CFRTHeader header;
	header.read(stream);
	if (header.depth != 1) throw LoadException("Depth is not 1.");
	std::vector<char> pixels;
	header.readPixels(stream, pixels);
	texture.setPixels(
		header.width, header.height,
		header.getFormat(), header.getType(), pixels.data()
	);
}

const GL::Texture2D& CFRTexture2D::get()
{
	return texture;
}



/* CFRTexture2D */

void CFRTexture3D::load(Storage&, std::istream &stream)
{
	CFRTHeader header;
	header.read(stream);
	std::vector<char> pixels;
	header.readPixels(stream, pixels);
	texture.setPixels(
		header.width, header.height, header.depth,
		header.getFormat(), header.getType(), pixels.data()
	);
}

const GL::Texture3D& CFRTexture3D::get()
{
	return texture;
}
