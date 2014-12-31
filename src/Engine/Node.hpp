#pragma once
#ifndef _ENGINE_NODE_HPP_
#define _ENGINE_NODE_HPP_

#include "Forward.hpp"
#include "Transform.hpp"
#include <set>
#include <stack>

namespace Engine {
	
	
	
	class Node : public Transform {
	public:
		
		/* Attach node */
		void attach(Node& node);
		
		/* Detach node */
		void detach(Node& node);
		
	private:
		
		friend class MainEngine;
		friend class Camera;
		friend class Scene;
		friend class Model;
		
		Node();
		virtual ~Node();
		Node(const Node&) = delete;
		Node& operator=(const Node&) = delete;
		
		virtual void draw();
		bool pushChildren(std::stack<Node*> &stack);
		
		Node* parent;
		std::set<Node*> children;
		
	};
	
	
	
} // namespace Engine

#endif // _ENGINE_NODE_HPP_
