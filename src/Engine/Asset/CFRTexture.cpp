#include "CFRTexture.hpp"
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

inline uint16_t read16(std::istream &in) {
	uint16_t t = 0;
	t |= static_cast<uint16_t>(in.get()) << 0;
	t |= static_cast<uint16_t>(in.get()) << 8;
	return t;
}

inline uint32_t read32(std::istream &in) {
	uint32_t t = 0;
	t |= static_cast<uint32_t>(in.get()) << 0;
	t |= static_cast<uint32_t>(in.get()) << 8;
	t |= static_cast<uint32_t>(in.get()) << 16;
	t |= static_cast<uint32_t>(in.get()) << 24;
	return t;
}

struct Header {
	size_t width;
	size_t height;
	size_t depth;
	size_t channels;
	size_t bytes;
	size_t size;
};

inline Header readHeader(std::istream &stream) {
	Header h;
	if (read32(stream) != 0x43465254) {
		throw A::LoadException("Invalid magic number.");
	} else if (read8(stream) != 1) {
		throw A::LoadException("Invalid version.");
	}
	h.width    = static_cast<size_t>(read16(stream));
	h.height   = static_cast<size_t>(read16(stream));
	h.depth    = static_cast<size_t>(read16(stream));
	h.channels = static_cast<size_t>(read8 (stream));
	h.bytes    = static_cast<size_t>(read8 (stream));
	if (!stream.good()) {
		throw A::LoadException("Failed to read header.");
	} else if (h.channels == 0 || h.channels > 4) {
		throw A::LoadException("Invalid number of channels.");
	} else if (h.bytes == 0 || h.bytes == 3 || h.bytes > 4) {
		throw A::LoadException("Invalid number of bytes per color.");
	}
	h.size = h.width * h.height * h.depth * h.channels * h.bytes;
	return h;
}

inline GLenum getFormat(size_t channels) {
	switch (channels) {
	default:
	case 4: return GL_RGBA;
	case 3: return GL_RGB;
	case 2: return GL_RG;
	case 1: return GL_RED;
	}
}

inline GLenum getType(size_t bytes) {
	switch (bytes) {
	default:
	case 1: return GL_UNSIGNED_BYTE;
	case 2: return GL_UNSIGNED_SHORT;
	case 4: return GL_UNSIGNED_INT;
	}
}


/* Engine::Asset::CFRTexture1D */

void A::CFRTexture1D::load(Storage&, std::istream &stream)
{
	Header h = readHeader(stream);
	if (h.depth != 1) {
		throw A::LoadException("Depth is not 1.");
	} else if (h.height != 1) {
		throw A::LoadException("Height is not 1.");
	}
	std::vector<char> pixels(h.size);
	stream.read(&pixels[0], h.size);
	if (!stream.good()) throw A::LoadException("Failed to read pixels.");
	texture.image(
		h.width,
		getFormat(h.channels), getType(h.bytes), &pixels[0]
	);
}

const GL::Texture1D& A::CFRTexture1D::get()
{
	return texture;
}



/* Engine::Asset::CFRTexture2D */

void A::CFRTexture2D::load(Storage&, std::istream &stream)
{
	Header h = readHeader(stream);
	if (h.depth != 1) {
		throw A::LoadException("Depth is not 1.");
	}
	std::vector<char> pixels(h.size);
	stream.read(&pixels[0], h.size);
	if (!stream.good()) throw A::LoadException("Failed to read pixels.");
	texture.image(
		h.width, h.height,
		getFormat(h.channels), getType(h.bytes), &pixels[0]
	);
}

const GL::Texture2D& A::CFRTexture2D::get()
{
	return texture;
}



/* Engine::Asset::CFRTexture2D */

void A::CFRTexture3D::load(Storage&, std::istream &stream)
{
	Header h = readHeader(stream);
	std::vector<char> pixels(h.size);
	stream.read(&pixels[0], h.size);
	if (!stream.good()) throw A::LoadException("Failed to read pixels.");
	texture.image(
		h.width, h.height, h.depth,
		getFormat(h.channels), getType(h.bytes), &pixels[0]
	);
}

const GL::Texture3D& A::CFRTexture3D::get()
{
	return texture;
}
