#pragma once
#ifndef _ENGINE_OBJ_NULLREADER_HPP_
#define _ENGINE_OBJ_NULLREADER_HPP_

#include "Reader.hpp"

namespace Engine { namespace Obj {
	
	
	
	/* Reader that discards everything */
	class NullReader : public virtual Reader {
	protected:
		
		/* Vertex data */
		virtual void parse(Vertex::Geometry &v) override;
		virtual void parse(Vertex::Texture &v) override;
		virtual void parse(Vertex::Normal &v) override;
		
		/* Elements */
		virtual void parse(Element::Point &e) override;
		virtual void parse(Element::Line &e) override;
		virtual void parse(Element::Face &e) override;
		
		/* Grouping */
		virtual void parse(Grouping::Groups &g) override;
		virtual void parse(Grouping::Smoothing &g) override;
		virtual void parse(Grouping::Merge &g) override;
		virtual void parse(Grouping::Object &g) override;
		
		/* Display/render attributes */
		virtual void parse(Render::Bevel &r) override;
		virtual void parse(Render::ColorInterpolation &r) override;
		virtual void parse(Render::DissolveInterpolation &r) override;
		virtual void parse(Render::LevelOfDetail &r) override;
		
	};
	
	
	
}} // namespace Engine::Obj

#endif // _ENGINE_OBJ_NULLREADER_HPP_
