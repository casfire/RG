#include "Scene.hpp"
#include "MainEngine.hpp"
#include "Asset/Asset.hpp"
#include <stack>
#include <glm/gtc/matrix_transform.hpp>

using Engine::MainEngine;
using Engine::Node;
using Engine::Camera;
using Engine::Scene;
using Engine::Model;
using Engine::DirectionalLight;
using Engine::PointLight;

Scene::Scene(MainEngine &engine)
: engine(engine), camera(*this), lightDir(engine), lightPoint(engine)
{
	program = &engine.storage.grab<Asset::GLProgram>("/assets/engine/program.txt");
	
	uModelMat = new GL::ProgramUniform(program->get(), "uModelMat");
	uViewMat  = new GL::ProgramUniform(program->get(), "uViewMat");
	uProjMat  = new GL::ProgramUniform(program->get(), "uProjMat");
	uShadowVP = new GL::ProgramUniform(program->get(), "uShadowVP");
	
	uShadowDepthBias  = new GL::ProgramUniform(program->get(), "uShadowDepthBias");
	uShadowTexelSize  = new GL::ProgramUniform(program->get(), "uShadowTexelSize");
	uShadowSamples    = new GL::ProgramUniform(program->get(), "uShadowSamples");
	
	uDiffuseSampler  = new GL::ProgramUniform(program->get(), "uDiffuseSampler");
	uNormalSampler   = new GL::ProgramUniform(program->get(), "uNormalSampler");
	uSpecularSampler = new GL::ProgramUniform(program->get(), "uSpecularSampler");
	uMaskSampler     = new GL::ProgramUniform(program->get(), "uMaskSampler");
	uEmitSampler     = new GL::ProgramUniform(program->get(), "uEmitSampler");
	uShadowSampler   = new GL::ProgramUniform(program->get(), "uShadowSampler");
	
	uAmbient          = new GL::ProgramUniform(program->get(), "uAmbient");
	uModelSpecularExp = new GL::ProgramUniform(program->get(), "uModelSpecularExp");
	
	uDirLightColor     = new GL::ProgramUniform(program->get(), "uDirLightColor");
	uDirLightIntensity = new GL::ProgramUniform(program->get(), "uDirLightIntensity");
	uDirLightDirection = new GL::ProgramUniform(program->get(), "uDirLightDirection");
	
	uPointLightColor     = new GL::ProgramUniform(program->get(), "uPointLightColor");
	uPointLightIntensity = new GL::ProgramUniform(program->get(), "uPointLightIntensity");
	uPointLightSpread    = new GL::ProgramUniform(program->get(), "uPointLightSpread");
	uPointLightPosition  = new GL::ProgramUniform(program->get(), "uPointLightPosition");
	
	program_depth = &engine.storage.grab<Asset::GLProgram>("/assets/engine/depth_program.txt");
	uDepthM = new GL::ProgramUniform(program_depth->get(), "uDepthM");
	uDepthV = new GL::ProgramUniform(program_depth->get(), "uDepthV");
	uDepthP = new GL::ProgramUniform(program_depth->get(), "uDepthP");
	
	/* Default light properties */
	setAmbient(0.2);
	lightDir.setColor(glm::vec3(1, 1, 1));
	lightDir.setIntensity(0.5f);
	lightDir.setDirection(glm::vec3(0.5, 1, 0.5));
	lightPoint.setColor(glm::vec3(1, 1, 1));
	lightPoint.setIntensity(5.f);
	lightPoint.setSpread(0.25f);
	lightPoint.setPosition(glm::vec3(0, 0, 0));
	
	/* Default shadow properties */
	setShadowProjection(-300, 300, -300, 300, -100, 500);
	setShadowDepthBias(0.005);
	setShadowSize(1024, 1024);
	setShadowSamples(4, 4, 4.f);
	enableShadows();
}

Scene::~Scene()
{
	delete uModelMat;
	delete uViewMat;
	delete uProjMat;
	delete uShadowVP;
	
	delete uShadowDepthBias;
	delete uShadowTexelSize;
	delete uShadowSamples;
	
	delete uDiffuseSampler;
	delete uNormalSampler;
	delete uSpecularSampler;
	delete uMaskSampler;
	delete uEmitSampler;
	delete uShadowSampler;
	
	delete uAmbient;
	delete uModelSpecularExp;
	
	delete uDirLightColor;
	delete uDirLightIntensity;
	delete uDirLightDirection;
	
	delete uPointLightColor;
	delete uPointLightIntensity;
	delete uPointLightSpread;
	delete uPointLightPosition;
	
	delete uDepthM;
	delete uDepthV;
	delete uDepthP;
	engine.storage.release(*program);
	engine.storage.release(*program_depth);
}

void Scene::drawEverything(GL::ProgramUniform *uModelMat) {
	
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
	
}

void Scene::draw()
{
	glm::mat4 shadowMatV;
	if (shadowEnable) {
		
		/* Bind shadow & depth program*/
		shadowFB.bind();
		program_depth->get().bind();
		
		/* Set depth matrices */
		shadowMatV = glm::lookAt(camera.getPosition() + lightDir.getDirection(), camera.getPosition(), glm::vec3(0,1,0));
		uDepthV->set(shadowMatV);
		uDepthP->set(shadowMatP);
		
		/* Draw shadow depth */
		glViewport(0, 0, shadowSizeX, shadowSizeY);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		drawEverything(uDepthM);
		
		/* Unbind shadow & depth program*/
		program_depth->get().unbind();
		shadowFB.unbind();
		
	}
	
	/* Bind program */
	program->get().bind();
	
	/* Set view matrix */
	uViewMat->set(camera.getViewMatrix());
	
	/* Set shadow sampler */
	glActiveTexture(GL_TEXTURE5);
	shadowTexture.bind();
	uShadowSampler->set1i(5);
	if (shadowEnable) {
		uShadowVP->set(
			glm::mat4(
				0.5, 0.0, 0.0, 0.0, 
				0.0, 0.5, 0.0, 0.0,
				0.0, 0.0, 0.5, 0.0,
				0.5, 0.5, 0.5, 1.0
			) * shadowMatP * shadowMatV
		);
	}
	
	/* Set directional light */
	uDirLightColor     ->set   (lightDir.getColor());
	uDirLightIntensity ->set1f (lightDir.getIntensity());
	uDirLightDirection ->set   (lightDir.getDirection());
	
	/* Set point light */
	uPointLightColor     ->set   (lightPoint.getColor());
	uPointLightIntensity ->set1f (lightPoint.getIntensity());
	uPointLightSpread    ->set1f (lightPoint.getSpread());
	uPointLightPosition  ->set   (lightPoint.getPosition());
	
	/* Draw scene */
	glViewport(0, 0, sceneWidth, sceneHeight);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	drawEverything(uModelMat);
	
	/* Unbind program */
	program->get().unbind();
	
}

void Scene::updateShadowTexelSize()
{
	program->get().bind();
	uShadowTexelSize->set(shadowSamplesSpread * glm::vec2(1. / shadowSizeX, 1. / shadowSizeY));
	program->get().unbind();
}

void Scene::setShadowSamples(int x, int y, float spread)
{
	shadowSamplesX = x;
	shadowSamplesY = y;
	shadowSamplesSpread = spread;
	program->get().bind();
	uShadowSamples->set2i(x, y);
	program->get().unbind();
	updateShadowTexelSize();
}

void Scene::enableShadows()
{
	shadowEnable = true;
}

void Scene::disableShadows()
{
	shadowEnable = false;
	shadowFB.bind();
	glViewport(0, 0, shadowSizeX, shadowSizeY);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	shadowFB.unbind();
}

void Scene::setShadowSize(int x, int y)
{
	shadowSizeX = x;
	shadowSizeY = y;
	shadowFB.bind();
	shadowTexture.bind();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, x, y, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, shadowTexture.getObjectID(), 0);
	glDrawBuffer(GL_NONE);
	shadowTexture.unbind();
	shadowFB.unbind();
	updateShadowTexelSize();
}

void Scene::setShadowDepthBias(float bias)
{
	program->get().bind();
	uShadowDepthBias->set1f(bias);
	program->get().unbind();
}

void Scene::setShadowProjection(
	float left,   float right,
	float bottom, float top,
	float near,   float far)
{
	shadowMatP = glm::ortho<float>(left, right, bottom, top, near, far);
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
	sceneWidth  = width;
	sceneHeight = height;
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
