#include "Reader.hpp"
#include <fstream>
#include <sstream>

namespace Obj = Engine::Obj;

bool Obj::Reader::read(const std::string &filename)
{
	std::ofstream sink;
	return read(filename, sink);
}

bool Obj::Reader::read(const std::string &filename, std::ostream &log)
{
	bool status = false;
	std::ifstream file;
	log << "[OBJ] Opening " << filename << " for reading.\n";
	file.open(filename, std::ios::in);
	if (file.is_open()) {
		status = read(file, log);
		if (file.bad()) {
			log << "[OBJ] Error occured while reading " << filename << ".\n";
		}
		log << "[OBJ] Closing " << filename << ".\n";
		file.close();
	} else {
		log << "[OBJ] Failed to open " << filename << " for reading.\n";
	}
	log << std::flush;
	return status;
}

bool Obj::Reader::read(std::istream &source)
{
	std::ofstream sink;
	return read(source, sink);
}

bool Obj::Reader::read(std::istream &source, std::ostream &log)
{
	bool status = true;
	std::size_t count = 0;
	for (std::string line; std::getline(source, line); ) {
		count++;
		if (!readLine(line)) {
			log << "Invalid line " << count << ": " << line << "\n";
			status = false;
		}
	}
	return !source.bad() && status;
}

template<typename T>
bool Obj::Reader::parser(std::istream& in)
{
	T obj;
	in >> obj;
	if (in.fail()) return false;
	parse(obj);
	return true;
}

bool Obj::Reader::readLine(const std::string &line)
{
	std::size_t length = static_cast<std::size_t>(line.size());
	
	/* Copy line */
	std::vector<char> copy(line.size() + 1);
	for (std::size_t i = 0; i < length; i++) copy[i] = line[i];
	copy[length] = '\0';
	char* s = static_cast<char*>(&copy[0]);
	
	/* Remove comment */
	for (std::size_t i = 0; i < length; i++) {
		if (s[i] == '#') {
			length = i;
			s[i] = '\0';
		}
	}
	
	std::size_t pos = 0;
	
	/* Skip spaces and non-printable characters */
	while (pos < length && !std::isgraph(s[pos])) pos++;
	
	/* Retreive first token */
	std::size_t start = pos;
	while (pos < length && std::isgraph(s[pos])) pos++;
	if (pos <= start) return true;
	std::string t(static_cast<const char*>(s + start), pos - start);
	
	/* Skip spaces and non-printable characters */
	while (pos < length && !std::isgraph(s[pos])) pos++;
	
	/* Create istream */
	std::istringstream in(std::string(static_cast<const char*>(s + pos), length - pos));
	
	/* Vertex data */
	if (t.compare("v")  == 0) return parser<Obj::Vertex::Geometry>(in);
	if (t.compare("vn") == 0) return parser<Obj::Vertex::Normal>(in);
	if (t.compare("vt") == 0) return parser<Obj::Vertex::Texture>(in);
	
	/* Elements */
	if (t.compare("p")  == 0) return parser<Obj::Element::Point>(in);
	if (t.compare("l")  == 0) return parser<Obj::Element::Line>(in);
	if (t.compare("f")  == 0) return parser<Obj::Element::Face>(in);
	
	/* Grouping */
	if (t.compare("g")  == 0) return parser<Obj::Grouping::Groups>(in);
	if (t.compare("s")  == 0) return parser<Obj::Grouping::Smoothing>(in);
	if (t.compare("mg") == 0) return parser<Obj::Grouping::Merge>(in);
	if (t.compare("o")  == 0) return parser<Obj::Grouping::Object>(in);
	
	/* Display/render attributes */
	if (t.compare("bevel")    == 0) return parser<Obj::Render::Bevel>(in);
	if (t.compare("c_interp") == 0) return parser<Obj::Render::ColorInterpolation>(in);
	if (t.compare("d_interp") == 0) return parser<Obj::Render::DissolveInterpolation>(in);
	if (t.compare("lod")      == 0) return parser<Obj::Render::LevelOfDetail>(in);
	
	return false;
}
