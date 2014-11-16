#include "NullReader.hpp"

namespace Obj = Engine::Obj;

/* Vertex data */

void Obj::NullReader::parse(Vertex::Geometry &v)
{
	(void) v;
}

void Obj::NullReader::parse(Vertex::Texture &v)
{
	(void) v;
}

void Obj::NullReader::parse(Vertex::Normal &v)
{
	(void) v;
}

/* Elements */

void Obj::NullReader::parse(Element::Point &e)
{
	(void) e;
}

void Obj::NullReader::parse(Element::Line &e)
{
	(void) e;
}

void Obj::NullReader::parse(Element::Face &e)
{
	(void) e;
}

/* Grouping */

void Obj::NullReader::parse(Grouping::Groups &g)
{
	(void) g;
}

void Obj::NullReader::parse(Grouping::Smoothing &g)
{
	(void) g;
}

void Obj::NullReader::parse(Grouping::Merge &g)
{
	(void) g;
}

void Obj::NullReader::parse(Grouping::Object &g)
{
	(void) g;
}

/* Display/render attributes */

void Obj::NullReader::parse(Render::Bevel &r)
{
	(void) r;
}

void Obj::NullReader::parse(Render::ColorInterpolation &r)
{
	(void) r;
}

void Obj::NullReader::parse(Render::DissolveInterpolation &r)
{
	(void) r;
}

void Obj::NullReader::parse(Render::LevelOfDetail &r)
{
	(void) r;
}
