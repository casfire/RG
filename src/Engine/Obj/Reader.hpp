#pragma once
#ifndef _ENGINE_OBJ_READER_HPP_
#define _ENGINE_OBJ_READER_HPP_

#include "Objects.hpp"
#include <string>
#include <istream>
#include <ostream>

namespace Engine { namespace Obj {
	
	
	
	// See: http://paulbourke.net/dataformats/obj/
	// See: http://paulbourke.net/dataformats/mtl/
	
	
	
	/* Base obj reader */
	class Reader {
	public:
		
		bool read(const std::string &filename);
		bool read(const std::string &filename, std::ostream &log);
		bool read(std::istream &source);
		bool read(std::istream &source, std::ostream &log);
		bool readLine(const std::string &line);
		
	protected:
		
		/* Vertex data */
		virtual void parse(Vertex::Geometry &v) = 0;
		virtual void parse(Vertex::Texture &v) = 0;
		virtual void parse(Vertex::Normal &v) = 0;
		
		/* Elements */
		virtual void parse(Element::Point &e) = 0;
		virtual void parse(Element::Line &e) = 0;
		virtual void parse(Element::Face &e) = 0;
		
		/* Grouping */
		virtual void parse(Grouping::Groups &g) = 0;
		virtual void parse(Grouping::Smoothing &g) = 0;
		virtual void parse(Grouping::Merge &g) = 0;
		virtual void parse(Grouping::Object &g) = 0;
		
		/* Display/render attributes */
		virtual void parse(Render::Bevel &r) = 0;
		virtual void parse(Render::ColorInterpolation &r) = 0;
		virtual void parse(Render::DissolveInterpolation &r) = 0;
		virtual void parse(Render::LevelOfDetail &r) = 0;
		
	private:
		
		template<typename T>
		bool parser(std::istream& in);
		
	};
	
	
	
}} // namespace Engine::Obj

#endif // _ENGINE_OBJ_READER_HPP_
