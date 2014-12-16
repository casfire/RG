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
	
	struct UseMaterial {
		std::string name;
	};
	
	struct MaterialLib {
		std::vector<std::string> files;
	};
	
	struct ShadowObject {
		std::string file;
	};
	
	struct TraceObject {
		std::string file;
	};
	
}}} // namespace Engine::Obj::Render



/* Material objects */

namespace Engine { namespace Obj { namespace Material {
	
	struct NewMaterial {
		std::string name;
	};
	
	struct AmbientColor {
		float r, g, b;
	};
	
	struct DiffuseColor {
		float r, g, b;
	};
	
	struct SpecularColor {
		float r, g, b;
	};
	
	struct Dissolve {
		float value;
	};
	
	struct IlluminationModel {
		int model;
	};
	
	struct AmbientMap {
		std::string file;
	};
	
	struct DiffuseMap {
		std::string file;
	};
	
	struct SpecularColorMap {
		std::string file;
	};
	
	struct SpeculaHighlightMap {
		std::string file;
	};
	
	struct AlphaMap {
		std::string file;
	};
	
	struct BumpMap {
		std::string file;
	};
	
}}} // namespace Engine::Obj::Material



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
std::istream& operator>>(std::istream& in, Engine::Obj::Render::UseMaterial& obj);
std::istream& operator>>(std::istream& in, Engine::Obj::Render::MaterialLib& obj);
std::istream& operator>>(std::istream& in, Engine::Obj::Render::ShadowObject& obj);
std::istream& operator>>(std::istream& in, Engine::Obj::Render::TraceObject& obj);

std::istream& operator>>(std::istream& in, Engine::Obj::Material::NewMaterial& obj);
std::istream& operator>>(std::istream& in, Engine::Obj::Material::AmbientColor& obj);
std::istream& operator>>(std::istream& in, Engine::Obj::Material::DiffuseColor& obj);
std::istream& operator>>(std::istream& in, Engine::Obj::Material::SpecularColor& obj);
std::istream& operator>>(std::istream& in, Engine::Obj::Material::Dissolve& obj);
std::istream& operator>>(std::istream& in, Engine::Obj::Material::IlluminationModel& obj);
std::istream& operator>>(std::istream& in, Engine::Obj::Material::AmbientMap& obj);
std::istream& operator>>(std::istream& in, Engine::Obj::Material::DiffuseMap& obj);
std::istream& operator>>(std::istream& in, Engine::Obj::Material::SpecularColorMap& obj);
std::istream& operator>>(std::istream& in, Engine::Obj::Material::SpeculaHighlightMap& obj);
std::istream& operator>>(std::istream& in, Engine::Obj::Material::AlphaMap& obj);
std::istream& operator>>(std::istream& in, Engine::Obj::Material::BumpMap& obj);



#endif // _ENGINE_OBJ_OBJECTS_HPP_
