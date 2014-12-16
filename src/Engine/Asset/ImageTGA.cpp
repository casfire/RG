#include "ImageTGA.hpp"
#include <sstream>
#include <cstddef>

namespace A = Engine::Asset;

struct TGAHeader {
	uint8_t   idlength;
	uint8_t   colourmaptype;
	uint8_t   datatypecode;
	uint16_t  colourmaporigin;
	uint16_t  colourmaplength;
	uint8_t   colourmapdepth;
	uint16_t  x_origin;
	uint16_t  y_origin;
	uint16_t  width;
	uint16_t  height;
	uint8_t   bitsperpixel;
	uint8_t   imagedescriptor;
};

inline uint8_t read8(std::istream& in)
{
	return static_cast<uint8_t>(in.get());
}

inline uint16_t read16(std::istream& in)
{
	uint32_t t = 0;
	t |= static_cast<uint32_t>(in.get());
	t |= static_cast<uint32_t>(in.get()) << 8;
	return t;
}

std::istream& operator>>(std::istream& in, TGAHeader& obj)
{
	obj.idlength        = read8(in);
	obj.colourmaptype   = read8(in);
	obj.datatypecode    = read8(in);
	obj.colourmaporigin = read16(in);
	obj.colourmaplength = read16(in);
	obj.colourmapdepth  = read8(in);
	obj.x_origin        = read16(in);
	obj.y_origin        = read16(in);
	obj.width           = read16(in);
	obj.height          = read16(in);
	obj.bitsperpixel    = read8(in);
	obj.imagedescriptor = read8(in);
	return in;
}

template <typename T>
inline const std::string to_string(const T &value)
{
	std::ostringstream os;
	os << value;
	return os.str();
}

A::ImageTGA::ImageTGA()
: bpp(0), width(0), height(0)
{}

void A::ImageTGA::load(Storage&, std::istream& stream)
{
	TGAHeader h;
	stream >> h;
	if (!stream.good()) throw A::LoadException("Invalid TGA header.");
	if (h.idlength > 0) stream.ignore(h.idlength);
	if (h.colourmaptype != 0) {
		throw A::LoadException("TGA color map (" + to_string(h.colourmaptype) + ") not supported.");
	} else if (h.imagedescriptor != 0) {
		throw A::LoadException("Invalid TGA image descriptor (" + to_string(h.imagedescriptor) + ").");
	} else if (h.datatypecode != 2 && h.datatypecode != 10) {
		throw A::LoadException("Invalid TGA data type (" + to_string(h.datatypecode) + ").");
	} else if (h.bitsperpixel != 24 && h.bitsperpixel != 32) {
		throw A::LoadException("Invalid TGA bpp (" + to_string(h.bitsperpixel) + ").");
	}
	width = h.width;
	height = h.height;
	bpp = h.bitsperpixel;
	std::size_t size = (bpp == 24 ? 3 : 4) * width * height; 
	pixels.resize(size);
	if (h.datatypecode == 2) {
		stream.read(reinterpret_cast<char*>(&pixels[0]), size);
	} else {
		throw A::LoadException("TGA run length encoding not supported.");
	}
}

const uint8_t* A::ImageTGA::getPixels() const
{
	return static_cast<const uint8_t*>(&pixels[0]);
}

uint8_t A::ImageTGA::getBitsPerPixel() const
{
	return bpp;
}

uint16_t A::ImageTGA::getWidth() const
{
	return width;
}

uint16_t A::ImageTGA::getHeight() const
{
	return height;
}
