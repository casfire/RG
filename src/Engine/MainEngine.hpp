#pragma once
#ifndef _ENGINE_MAINENGINE_HPP_
#define _ENGINE_MAINENGINE_HPP_

#include "Asset/Storage.hpp"
#include "Forward.hpp"
#include <set>
#include <string>

namespace Engine {
	
	
	
	class MainEngine {
	public:
		
		/* Constructor */
		MainEngine();
		
		/* Destructor */
		~MainEngine();
		
		/* Initialize engine - throws EngineInitException */
		void init();
		
		/* Get engine information */
		std::string getOpenGLVersion() const;
		std::string getShadingVersion() const;
		std::string getRendererName() const;
		std::string getVendorName() const;
		
		/* Create scene */
		Scene& createScene(int width = 1, int height = 1);
		
		/* Create empty node */
		Node& createNode();
		
		/* Load and create model */
		Model& loadModel(const std::string &file);
		
		/* Delete objects */
		void deleteNode(Node &node);
		void deleteAllNodes();
		void deleteScene(Scene &scene);
		void deleteAllScenes();
		
	private:
		
		friend class Camera;
		friend class Scene;
		friend class Model;
		
		MainEngine(const MainEngine&) = delete;
		MainEngine& operator=(const MainEngine&) = delete;
		
		std::set<Scene*> scenes;
		std::set<Node*> nodes;
		Asset::Storage storage;
		
	};
	
	
	
} // namespace Engine

#endif // _ENGINE_MAINENGINE_HPP_
