#pragma once
#ifndef _ENGINE_MODEL_HPP_
#define _ENGINE_MODEL_HPP_

#include "Forward.hpp"
#include "Node.hpp"
#include <string>

namespace Engine {
	
	
	
	class Model : public Node {
	private:
		
		friend class MainEngine;
		friend class Node;
		friend class Camera;
		friend class Scene;
		
		Model(MainEngine &engine, const std::string &file);
		~Model();
		
		void draw() override;
		
		MainEngine &engine;
		Asset::CFRGeometry *geometry;
		
	};
	
	
	
} // namespace Engine

#endif // _ENGINE_MODEL_HPP_
