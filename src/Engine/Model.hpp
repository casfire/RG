#pragma once
#ifndef _ENGINE_MODEL_HPP_
#define _ENGINE_MODEL_HPP_

#include "Forward.hpp"
#include "Node.hpp"
#include <string>
#include <vector>

namespace Engine {
	
	
	
	struct ModelObject {
		Asset::CFRGeometry *geometry = nullptr;
		std::size_t start, end;
		Asset::CFRTexture2D *diffuseCFRT  = nullptr;
		const GL::Texture2D *diffuse      = nullptr;
		Asset::CFRTexture2D *normalCFRT   = nullptr;
		const GL::Texture2D *normal       = nullptr;
		Asset::CFRTexture2D *specularCFRT = nullptr;
		const GL::Texture2D *specular     = nullptr;
		Asset::CFRTexture2D *maskCFRT     = nullptr;
		const GL::Texture2D *mask         = nullptr;
		Asset::CFRTexture2D *emitCFRT     = nullptr;
		const GL::Texture2D *emit         = nullptr;
		float specular_exp;
	};
	
	
	
	class Model : public Node {
	private:
		
		friend class MainEngine;
		friend class Node;
		friend class Camera;
		friend class Scene;
		
		Model(MainEngine &engine, const std::string &file);
		~Model();
		
		void draw(Scene &scene) override;
		
		MainEngine &engine;
		Asset::CFRModel *model;
		std::vector<ModelObject> objects;
		
	};
	
	
	
} // namespace Engine

#endif // _ENGINE_MODEL_HPP_
