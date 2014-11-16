#pragma once
#ifndef _ENGINE_OBJ_OBJECTS_HPP_
#define _ENGINE_OBJ_OBJECTS_HPP_

#include <vector>
#include <string>
#include <cstddef> // std::size_t
#include <istream>



/* Vertex data */

namespace Engine { namespace Obj { namespace Vertex {
	
	struct Geometry {
		float x, y, z, w = 1.f;
	};
	
	struct Texture {
		float u, v = 0.f, w = 0.f;
	};
	
	struct Normal {
		float i, j, k;
	};
	
}}} // namespace Engine::Obj::Vertex



/* Elements */

namespace Engine { namespace Obj { namespace Element {
	
	struct PointVertex {
		std::size_t v;
	};
	
	typedef std::vector<PointVertex> Point;
	
	struct LineVertex {
		std::size_t v, vt;
		bool hasTexture;
	};
	
	typedef std::vector<LineVertex> Line;
	
	struct FaceVertex {
		std::size_t v, vt, vn;
		bool hasTexture, hasNormal;
	};
	
	typedef std::vector<FaceVertex> Face;
	
}}} // namespace Engine::Obj::Element



/* Grouping */

namespace Engine { namespace Obj { namespace Grouping {
	
	struct Groups {
		std::vector<std::string> names;
	};
	
	struct Smoothing {
		int group_number;
	};
	
	struct Merge {
		int group_number, res;
	};
	
	struct Object {
		std::string name;
	};
	
}}} // namespace Engine::Obj::Grouping



/* Display/render attributes */

namespace Engine { namespace Obj { namespace Render {
	
	struct Bevel {
		bool enabled;
	};
	
	struct ColorInterpolation {
		bool enabled;
	};
	
	struct DissolveInterpolation {
		bool enabled;
	};
	
	struct LevelOfDetail {
		int level;
	};
	
}}} // namespace Engine::Obj::Render



std::istream& operator>>(std::istream& in, Engine::Obj::Vertex::Geometry& obj);
std::istream& operator>>(std::istream& in, Engine::Obj::Vertex::Texture& obj);
std::istream& operator>>(std::istream& in, Engine::Obj::Vertex::Normal& obj);

std::istream& operator>>(std::istream& in, Engine::Obj::Element::PointVertex& obj);
std::istream& operator>>(std::istream& in, Engine::Obj::Element::Point& obj);
std::istream& operator>>(std::istream& in, Engine::Obj::Element::LineVertex& obj);
std::istream& operator>>(std::istream& in, Engine::Obj::Element::Line& obj);
std::istream& operator>>(std::istream& in, Engine::Obj::Element::FaceVertex& obj);
std::istream& operator>>(std::istream& in, Engine::Obj::Element::Face& obj);

std::istream& operator>>(std::istream& in, Engine::Obj::Grouping::Groups& obj);
std::istream& operator>>(std::istream& in, Engine::Obj::Grouping::Smoothing& obj);
std::istream& operator>>(std::istream& in, Engine::Obj::Grouping::Merge& obj);
std::istream& operator>>(std::istream& in, Engine::Obj::Grouping::Object& obj);

std::istream& operator>>(std::istream& in, Engine::Obj::Render::Bevel& obj);
std::istream& operator>>(std::istream& in, Engine::Obj::Render::ColorInterpolation& obj);
std::istream& operator>>(std::istream& in, Engine::Obj::Render::DissolveInterpolation& obj);
std::istream& operator>>(std::istream& in, Engine::Obj::Render::LevelOfDetail& obj);



#endif // _ENGINE_OBJ_OBJECTS_HPP_
