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
using Engine::DirectionalLight;
using Engine::PointLight;

Scene::Scene(MainEngine &engine)
: engine(engine), camera(*this),
  lightDir(engine), lightPoint(engine)
{
	program = &engine.storage.grab<Asset::GLProgram>("/assets/engine/program.txt");
	
	uModelMat = new GL::ProgramUniform(program->get(), "uModelMat");
	uViewMat  = new GL::ProgramUniform(program->get(), "uViewMat");
	uProjMat  = new GL::ProgramUniform(program->get(), "uProjMat");
	
	uDiffuseSampler  = new GL::ProgramUniform(program->get(), "uDiffuseSampler");
	uNormalSampler   = new GL::ProgramUniform(program->get(), "uNormalSampler");
	uSpecularSampler = new GL::ProgramUniform(program->get(), "uSpecularSampler");
	uMaskSampler     = new GL::ProgramUniform(program->get(), "uMaskSampler");
	uEmitSampler     = new GL::ProgramUniform(program->get(), "uEmitSampler");
	
	uAmbient          = new GL::ProgramUniform(program->get(), "uAmbient");
	uModelSpecularExp = new GL::ProgramUniform(program->get(), "uModelSpecularExp");
	
	uDirLightColor     = new GL::ProgramUniform(program->get(), "uDirLightColor");
	uDirLightIntensity = new GL::ProgramUniform(program->get(), "uDirLightIntensity");
	uDirLightDirection = new GL::ProgramUniform(program->get(), "uDirLightDirection");
	
	uPointLightColor     = new GL::ProgramUniform(program->get(), "uPointLightColor");
	uPointLightIntensity = new GL::ProgramUniform(program->get(), "uPointLightIntensity");
	uPointLightSpread    = new GL::ProgramUniform(program->get(), "uPointLightSpread");
	uPointLightPosition  = new GL::ProgramUniform(program->get(), "uPointLightPosition");
	
	/* Defaults */
	setAmbient(0.2);
	lightDir.setColor(glm::vec3(1, 1, 1));
	lightDir.setIntensity(0.5f);
	lightDir.setDirection(glm::vec3(0.5, 1, 0.5));
	lightPoint.setColor(glm::vec3(1, 1, 1));
	lightPoint.setIntensity(5.f);
	lightPoint.setSpread(0.25f);
	lightPoint.setPosition(glm::vec3(0, 0, 0));
	
}

Scene::~Scene()
{
	engine.storage.release(*program);
	
	delete uModelMat;
	delete uViewMat;
	delete uProjMat;
	
	delete uDiffuseSampler;
	delete uNormalSampler;
	delete uSpecularSampler;
	delete uMaskSampler;
	delete uEmitSampler;
	
	delete uAmbient;
	delete uModelSpecularExp;
	
	delete uDirLightColor;
	delete uDirLightIntensity;
	delete uDirLightDirection;
	
	delete uPointLightColor;
	delete uPointLightIntensity;
	delete uPointLightSpread;
	delete uPointLightPosition;
}

void Scene::draw()
{
	/* Clear screen */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	/* Bind program */
	program->get().bind();
	
	/* Set view matrix */
	uViewMat->set(camera.getViewMatrix());
	
	/* Set directional light */
	uDirLightColor     ->set   (lightDir.getColor());
	uDirLightIntensity ->set1f (lightDir.getIntensity());
	uDirLightDirection ->set   (lightDir.getDirection());
	
	/* Set point light */
	uPointLightColor     ->set   (lightPoint.getColor());
	uPointLightIntensity ->set1f (lightPoint.getIntensity());
	uPointLightSpread    ->set1f (lightPoint.getSpread());
	uPointLightPosition  ->set   (lightPoint.getPosition());
	
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
		top->draw(*this);
		if (!top->pushChildren(nodes)) {
			matrices.pop();
		}
	}
	
	/* Unbind program */
	program->get().unbind();
}

void Scene::setAmbient(float amount)
{
	program->get().bind();
	uAmbient->set1f(amount);
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

DirectionalLight& Scene::getDirectionalLight()
{
	return lightDir;
}

PointLight& Scene::getPointLight()
{
	return lightPoint;
}
