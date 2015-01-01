#include "Node.hpp"

using Engine::MainEngine;
using Engine::Node;
using Engine::Camera;
using Engine::Scene;
using Engine::Model;

Node::Node()
: parent(nullptr)
{}

Node::~Node()
{
	if (parent != nullptr) {
		parent->detach(*this);
	}
}

void Node::attach(Node& node)
{
	node.parent = this;
	children.insert(&node);
}

void Node::detach(Node& node)
{
	std::set<Node*>::iterator i = children.find(&node);
	if (i != children.end()) {
		children.erase(i);
	}
}

bool Node::pushChildren(std::stack<Node*> &stack)
{
	if (children.empty()) return false;
	std::set<Node*>::iterator end = children.end();
	for (std::set<Node*>::iterator i = children.begin(); i != end; i++) {
		stack.push(*i);
	}
	return true;
}

void Node::draw(Scene&)
{}
