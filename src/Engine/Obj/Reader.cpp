#include "Reader.hpp"
#include <fstream>
#include <sstream>

namespace Obj = Engine::Obj;



/* Engine::Obj::TokenReader */

bool Obj::TokenReader::read(const std::string &filename)
{
	std::ofstream sink;
	return read(filename, sink);
}

bool Obj::TokenReader::read(const std::string &filename, std::ostream &log)
{
	bool status = false;
	std::ifstream file;
	log << "[" << prefix() << "] Opening " << filename << " for reading.\n";
	file.open(filename, std::ios::in);
	if (file.is_open()) {
		status = read(file, log);
		if (file.bad()) {
			log << "[" << prefix() << "] Error occured while reading " << filename << ".\n";
		}
		log << "[" << prefix() << "] Closing " << filename << ".\n";
		file.close();
	} else {
		log << "[" << prefix() << "] Failed to open " << filename << " for reading.\n";
	}
	log << std::flush;
	return status;
}

bool Obj::TokenReader::read(std::istream &source)
{
	std::ofstream sink;
	return read(source, sink);
}

bool Obj::TokenReader::read(std::istream &source, std::ostream &log)
{
	bool status = true;
	std::size_t count = 0;
	for (std::string line; std::getline(source, line); ) {
		count++;
		if (!this->line(line)) {
			log << "[" << prefix() << "] Invalid line " << count << ": " << line << "\n";
			status = false;
		}
	}
	done();
	return !source.bad() && status;
}

void Obj::TokenReader::done()
{}

bool Obj::TokenReader::line(const std::string &line)
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
	
	/* Call virtual token method */
	return token(t, in);
}



/* Engine::Obj::ObjectReader */

const char* Obj::ObjectReader::prefix()
{
	return "OBJ";
}

template<typename T>
bool Obj::ObjectReader::parser(std::istream& in)
{
	T obj;
	in >> obj;
	if (in.fail()) return false;
	return parse(obj);
}

bool Obj::ObjectReader::token(const std::string &t, std::istream &in)
{
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
	if (t.compare("bevel")      == 0) return parser<Obj::Render::Bevel>(in);
	if (t.compare("c_interp")   == 0) return parser<Obj::Render::ColorInterpolation>(in);
	if (t.compare("d_interp")   == 0) return parser<Obj::Render::DissolveInterpolation>(in);
	if (t.compare("lod")        == 0) return parser<Obj::Render::LevelOfDetail>(in);
	if (t.compare("usemtl")     == 0) return parser<Obj::Render::UseMaterial>(in);
	if (t.compare("mtllib")     == 0) return parser<Obj::Render::MaterialLib>(in);
	if (t.compare("shadow_obj") == 0) return parser<Obj::Render::ShadowObject>(in);
	if (t.compare("trace_obj")  == 0) return parser<Obj::Render::TraceObject>(in);
	
	return false;
}

bool Obj::ObjectReader::parse(Obj::Vertex::Geometry&) { return false; }
bool Obj::ObjectReader::parse(Obj::Vertex::Texture&) { return false; }
bool Obj::ObjectReader::parse(Obj::Vertex::Normal&) { return false; }
bool Obj::ObjectReader::parse(Obj::Element::Point&) { return false; }
bool Obj::ObjectReader::parse(Obj::Element::Line&) { return false; }
bool Obj::ObjectReader::parse(Obj::Element::Face&) { return false; }
bool Obj::ObjectReader::parse(Obj::Grouping::Groups&) { return false; }
bool Obj::ObjectReader::parse(Obj::Grouping::Smoothing&) { return false; }
bool Obj::ObjectReader::parse(Obj::Grouping::Merge&) { return false; }
bool Obj::ObjectReader::parse(Obj::Grouping::Object&) { return false; }
bool Obj::ObjectReader::parse(Obj::Render::Bevel&) { return false; }
bool Obj::ObjectReader::parse(Obj::Render::ColorInterpolation&) { return false; }
bool Obj::ObjectReader::parse(Obj::Render::DissolveInterpolation&) { return false; }
bool Obj::ObjectReader::parse(Obj::Render::LevelOfDetail&) { return false; }
bool Obj::ObjectReader::parse(Obj::Render::UseMaterial&) { return false; }
bool Obj::ObjectReader::parse(Obj::Render::MaterialLib&) { return false; }
bool Obj::ObjectReader::parse(Obj::Render::ShadowObject&) { return false; }
bool Obj::ObjectReader::parse(Obj::Render::TraceObject&) { return false;}



/* Engine::Obj::MaterialReader */

const char* Obj::MaterialReader::prefix()
{
	return "MTL";
}

template<typename T>
bool Obj::MaterialReader::parser(std::istream& in)
{
	T obj;
	in >> obj;
	if (in.fail()) return false;
	return parse(obj);
}

bool Obj::MaterialReader::token(const std::string &t, std::istream &in)
{
	if (t.compare("newmtl")   == 0) return parser<Obj::Material::NewMaterial>(in);
	if (t.compare("Ka")       == 0) return parser<Obj::Material::AmbientColor>(in);
	if (t.compare("Kd")       == 0) return parser<Obj::Material::DiffuseColor>(in);
	if (t.compare("Ks")       == 0) return parser<Obj::Material::SpecularColor>(in);
	if (t.compare("d")        == 0) return parser<Obj::Material::Dissolve>(in);
	if (t.compare("illum")    == 0) return parser<Obj::Material::IlluminationModel>(in);
	if (t.compare("map_Ka")   == 0) return parser<Obj::Material::AmbientMap>(in);
	if (t.compare("map_Kd")   == 0) return parser<Obj::Material::DiffuseMap>(in);
	if (t.compare("map_Ks")   == 0) return parser<Obj::Material::SpecularColorMap>(in);
	if (t.compare("map_Ns")   == 0) return parser<Obj::Material::SpeculaHighlightMap>(in);
	if (t.compare("map_d")    == 0) return parser<Obj::Material::AlphaMap>(in);
	if (t.compare("map_bump") == 0) return parser<Obj::Material::BumpMap>(in);
	return false;
}

bool Obj::MaterialReader::parse(Material::NewMaterial&) { return false; }
bool Obj::MaterialReader::parse(Material::AmbientColor&) { return false; }
bool Obj::MaterialReader::parse(Material::DiffuseColor&) { return false; }
bool Obj::MaterialReader::parse(Material::SpecularColor&) { return false; }
bool Obj::MaterialReader::parse(Material::Dissolve&) { return false; }
bool Obj::MaterialReader::parse(Material::IlluminationModel&) { return false; }
bool Obj::MaterialReader::parse(Material::AmbientMap&) { return false; }
bool Obj::MaterialReader::parse(Material::DiffuseMap&) { return false; }
bool Obj::MaterialReader::parse(Material::SpecularColorMap&) { return false; }
bool Obj::MaterialReader::parse(Material::SpeculaHighlightMap&) { return false; }
bool Obj::MaterialReader::parse(Material::AlphaMap&) { return false; }
bool Obj::MaterialReader::parse(Material::BumpMap&) { return false; }
