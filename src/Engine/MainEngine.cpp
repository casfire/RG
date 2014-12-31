#include "MainEngine.hpp"
#include "Exception.hpp"
#include "Scene.hpp"
#include "Model.hpp"
#include "GL/GL.hpp"

using Engine::MainEngine;
using Engine::Node;
using Engine::Camera;
using Engine::Scene;
using Engine::Model;
using Engine::EngineInitException;

MainEngine::MainEngine()
{}

MainEngine::~MainEngine()
{
	deleteAllNodes();
	deleteAllScenes();
}

void MainEngine::init()
{
	/* Load OpenGL */
	if (ogl_LoadFunctions() == ogl_LOAD_FAILED) {
		throw EngineInitException("Failed to load OpenGL.");
	}
	
	/* Clear parameters */
	glClearColor(0.f, 0.f, 0.f, 0.f);
	glClearDepth(1.0f);
	
	/* Enable depth mask */
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LEQUAL);
	glDepthRange(0.f, 1.f);
	
	/* Enable depth clamping */
	glEnable(GL_DEPTH_CLAMP);
	
	/* Enable face culling */
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);
}

std::string MainEngine::getOpenGLVersion() const
{
	return GL::getVersion();
}

std::string MainEngine::getShadingVersion() const
{
	return GL::getGLSLVersion();
}

std::string MainEngine::getRendererName() const
{
	return GL::getRenderer();
}

std::string MainEngine::getVendorName() const
{
	return GL::getVendor();
}

Scene& MainEngine::createScene(int width, int height)
{
	Scene* scene = new Scene(*this);
	scenes.insert(scene);
	scene->resize(width, height);
	return *scene;
}

Node& MainEngine::createNode()
{
	Node* node = new Node;
	nodes.insert(node);
	return *node;
}

Model& MainEngine::loadModel(const std::string &file)
{
	Model* model = new Model(*this, file);
	nodes.insert(model);
	return *model;
}

void MainEngine::deleteNode(Node &node)
{
	std::set<Node*>::iterator i = nodes.find(&node);
	if (i != nodes.end()) {
		nodes.erase(i);
		delete &node;
	}
}

void MainEngine::deleteAllNodes()
{
	std::set<Node*>::iterator end = nodes.end();
	for (std::set<Node*>::iterator i = nodes.begin(); i != end; i++) {
		delete *i;
	}
	nodes.clear();
}

void MainEngine::deleteScene(Scene &scene)
{
	std::set<Scene*>::iterator i = scenes.find(&scene);
	if (i != scenes.end()) {
		scenes.erase(i);
		delete &scene;
	}
}

void MainEngine::deleteAllScenes()
{
	std::set<Scene*>::iterator end = scenes.end();
	for (std::set<Scene*>::iterator i = scenes.begin(); i != end; i++) {
		delete *i;
	}
	scenes.clear();
}
