#include "Objects.hpp"
#include <sstream>

namespace Obj = Engine::Obj;



/* Vertex data */

std::istream& operator>>(std::istream& in, Obj::Vertex::Geometry& obj)
{
	in >> obj.x >> obj.y >> obj.z;
	if (in.rdstate() & std::ios::failbit) return in;
	in >> obj.w;
	if (in.rdstate() & std::ios::failbit) {
		in.clear(in.rdstate() & (~std::ios::failbit));
		obj.w = 1.0;
	}
	return in;
}

std::istream& operator>>(std::istream& in, Obj::Vertex::Texture& obj)
{
	in >> obj.u;
	if (in.rdstate() & std::ios::failbit) return in;
	in >> obj.v;
	if (in.rdstate() & std::ios::failbit) {
		in.clear(in.rdstate() & (~std::ios::failbit));
		obj.v = 0.0;
		obj.w = 0.0;
		return in;
	}
	in >> obj.w;
	if (in.rdstate() & std::ios::failbit) {
		in.clear(in.rdstate() & (~std::ios::failbit));
		obj.w = 0.0;
	}
	return in;
}

std::istream& operator>>(std::istream& in, Obj::Vertex::Normal& obj)
{
	in >> obj.i >> obj.j >> obj.k;
	return in;
}



/* Elements */

std::istream& operator>>(std::istream& in, Engine::Obj::Element::PointVertex& obj)
{
	return in >> obj.v;
}

std::istream& operator>>(std::istream& in, Obj::Element::Point& obj)
{
	while (true) {
		Obj::Element::PointVertex v;
		in >> v;
		if (in.rdstate() & std::ios::failbit) {
			in.clear(in.rdstate() & (~std::ios::failbit));
			break;
		}
		obj.push_back(v);
	}
	if (obj.empty()) in.setstate(std::ios::failbit);
	return in;
}

std::istream& operator>>(std::istream& in, Obj::Element::LineVertex& obj)
{
	in >> obj.v;
	if (in.rdstate() & std::ios::failbit) return in;
	if (in.peek() == '/') {
		in.get();
		in >> obj.vt;
		obj.hasTexture = true;
	} else {
		in.clear(in.rdstate() & (~std::ios::failbit));
		obj.vt = 0;
		obj.hasTexture = false;
	}
	return in;
}

std::istream& operator>>(std::istream& in, Obj::Element::Line& obj)
{
	while (true) {
		std::string token;
		in >> token;
		if (in.rdstate() & std::ios::failbit) {
			in.clear(in.rdstate() & (~std::ios::failbit));
			break;
		}
		Obj::Element::LineVertex v;
		std::istringstream tin(token);
		tin >> v;
		if (tin.fail()) {
			in.setstate(std::ios::failbit);
			break;
		}
		obj.push_back(v);
	}
	if (obj.empty()) in.setstate(std::ios::failbit);
	return in;
}

std::istream& operator>>(std::istream& in, Obj::Element::FaceVertex& obj)
{
	in >> obj.v;
	if (in.rdstate() & std::ios::failbit) return in;
	if (in.peek() == '/') {
		in.get();
		if (in.peek() == '/') {
			in.get();
			in >> obj.vn;
			obj.vt = 0;
			obj.hasTexture = false;
			obj.hasNormal = true;
		} else {
			in >> obj.vt;
			if (in.rdstate() & std::ios::failbit) return in;
			if (in.peek() == '/') {
				in.get();
				in >> obj.vn;
				obj.hasTexture = true;
				obj.hasNormal = true;
			} else {
				in.clear(in.rdstate() & (~std::ios::failbit));
				obj.vn = 0;
				obj.hasTexture = true;
				obj.hasNormal = false;
			}
		}
	} else {
		in.clear(in.rdstate() & (~std::ios::failbit));
		obj.vt = 0;
		obj.vn = 0;
		obj.hasTexture = false;
		obj.hasNormal = false;
	}
	return in;
}

std::istream& operator>>(std::istream& in, Obj::Element::Face& obj)
{
	while (true) {
		std::string token;
		in >> token;
		if (in.rdstate() & std::ios::failbit) {
			in.clear(in.rdstate() & (~std::ios::failbit));
			break;
		}
		Obj::Element::FaceVertex v;
		std::istringstream tin(token);
		tin >> v;
		if (tin.fail()) {
			in.setstate(std::ios::failbit);
			break;
		}
		obj.push_back(v);
	}
	if (obj.empty()) in.setstate(std::ios::failbit);
	return in;
}



/* Grouping */

std::istream& operator>>(std::istream& in, Obj::Grouping::Groups& obj)
{
	while (true) {
		std::string group;
		in >> group;
		if (in.rdstate() & std::ios::failbit) {
			in.clear(in.rdstate() & (~std::ios::failbit));
			break;
		}
		obj.names.push_back(group);
	}
	if (obj.names.empty()) in.setstate(std::ios::failbit);
	return in;
}

std::istream& operator>>(std::istream& in, Obj::Grouping::Smoothing& obj)
{
	in >> obj.group_number;
	if (in.rdstate() & std::ios::failbit) {
		in.clear(in.rdstate() & (~std::ios::failbit));
		std::istream::pos_type pos = in.tellg();
		std::string off;
		in >> off;
		if (off.compare("off") == 0) {
			obj.group_number = 0;
		} else {
			in.seekg(pos);
			in.setstate(std::ios::failbit);
		}
	}
	return in;
}

std::istream& operator>>(std::istream& in, Obj::Grouping::Merge& obj)
{
	return in >> obj.group_number >> obj.res;
}

std::istream& operator>>(std::istream& in, Obj::Grouping::Object& obj)
{
	return in >> obj.name;
}



/* Display/render attributes */

std::istream& operator>>(std::istream& in, Obj::Render::Bevel& obj)
{
	std::istream::pos_type pos = in.tellg();
	std::string state;
	in >> state;
	if (in.rdstate() & std::ios::failbit) return in;
	if (state.compare("on") == 0) {
		obj.enabled = true;
	} else if (state.compare("off") == 0) {
		obj.enabled = false;
	} else {
		in.seekg(pos);
		in.setstate(std::ios::failbit);
	}
	return in;
}

std::istream& operator>>(std::istream& in, Obj::Render::ColorInterpolation& obj)
{
	std::istream::pos_type pos = in.tellg();
	std::string state;
	in >> state;
	if (in.rdstate() & std::ios::failbit) return in;
	if (state.compare("on") == 0) {
		obj.enabled = true;
	} else if (state.compare("off") == 0) {
		obj.enabled = false;
	} else {
		in.seekg(pos);
		in.setstate(std::ios::failbit);
	}
	return in;
}

std::istream& operator>>(std::istream& in, Obj::Render::DissolveInterpolation& obj)
{
	std::istream::pos_type pos = in.tellg();
	std::string state;
	in >> state;
	if (in.rdstate() & std::ios::failbit) return in;
	if (state.compare("on") == 0) {
		obj.enabled = true;
	} else if (state.compare("off") == 0) {
		obj.enabled = false;
	} else {
		in.seekg(pos);
		in.setstate(std::ios::failbit);
	}
	return in;
}

std::istream& operator>>(std::istream& in, Obj::Render::LevelOfDetail& obj)
{
	return in >> obj.level;
}
