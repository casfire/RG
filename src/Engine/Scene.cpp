#include "Scene.hpp"
#include "MainEngine.hpp"
#include "Asset/Asset.hpp"
#include "GL/GL.hpp"
#include <stack>

using Engine::MainEngine;
using Engine::Node;
using Engine::Camera;
using Engine::Scene;
using Engine::Model;

Scene::Scene(MainEngine &engine)
: engine(engine), camera(*this)
{
	program = &engine.storage.grab<Asset::GLProgram>("/assets/engine/program.txt");
	uModelMat = new GL::ProgramUniform(program->get(), "uModelMat");
	uViewMat  = new GL::ProgramUniform(program->get(), "uViewMat");
	uProjMat  = new GL::ProgramUniform(program->get(), "uProjMat");
}

Scene::~Scene()
{
	engine.storage.release(*program);
	delete uModelMat;
	delete uViewMat;
	delete uProjMat;
}

void Scene::draw()
{
	/* Clear screen */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	/* Bind program */
	program->get().bind();
	
	/* Set view matrix */
	uViewMat->set(camera.getViewMatrix());
	
	/* Model matrix stack */
	std::stack<glm::mat4> matrices;
	matrices.push(getMatrix());
	
	/* Node stack */
	std::stack<Node*> nodes;
	pushChildren(nodes);
	
	/* Draw nodes */
	while (!nodes.empty()) {
		Node *top = nodes.top();
		matrices.push(matrices.top() * top->getMatrix());
		uModelMat->set(matrices.top());
		nodes.pop();
		top->draw();
		if (!top->pushChildren(nodes)) {
			matrices.pop();
		}
	}
	
	/* Unbind program */
	program->get().unbind();
}

void Scene::updateProjection()
{
	program->get().bind();
	uProjMat->set(camera.getProjectionMatrix());
	program->get().unbind();
}

void Scene::resize(int width, int height)
{
	glViewport(0, 0, width, height);
	camera.setAspect(width, height);
}

Camera& Scene::getCamera()
{
	return camera;
}
