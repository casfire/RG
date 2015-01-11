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
: engine(engine), camera(*this), lightDir(engine), lightPoint(engine),
  program      (engine.storage.grab<Asset::GLProgram>("/assets/engine/program.txt")),
  program_depth(engine.storage.grab<Asset::GLProgram>("/assets/engine/depth_program.txt"))
{
	
	/* Uniforms */
	uModelMat.locate(program, "uModelMat");
	uViewMat .locate(program, "uViewMat" );
	uProjMat .locate(program, "uProjMat" );
	uShadowVP.locate(program, "uShadowVP");
	uShadowDepthBias.locate(program, "uShadowDepthBias");
	uShadowTexelSize.locate(program, "uShadowTexelSize");
	uShadowSamples  .locate(program, "uShadowSamples"  );
	uDiffuseSampler .locate(program, "uDiffuseSampler" );
	uNormalSampler  .locate(program, "uNormalSampler"  );
	uSpecularSampler.locate(program, "uSpecularSampler");
	uMaskSampler    .locate(program, "uMaskSampler"    );
	uEmitSampler    .locate(program, "uEmitSampler"    );
	uShadowSampler  .locate(program, "uShadowSampler"  );
	uAmbient         .locate(program, "uAmbient"         );
	uModelSpecularExp.locate(program, "uModelSpecularExp");
	uDirLightColor    .locate(program, "uDirLightColor"    );
	uDirLightIntensity.locate(program, "uDirLightIntensity");
	uDirLightDirection.locate(program, "uDirLightDirection");
	uPointLightColor    .locate(program, "uPointLightColor"    );
	uPointLightIntensity.locate(program, "uPointLightIntensity");
	uPointLightSpread   .locate(program, "uPointLightSpread"   );
	uPointLightPosition .locate(program, "uPointLightPosition" );
	uDepthM.locate(program_depth, "uDepthM");
	uDepthV.locate(program_depth, "uDepthV");
	uDepthP.locate(program_depth, "uDepthP");
	
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
	engine.storage.release(program);
	engine.storage.release(program_depth);
}

void Scene::drawEverything(GL::Uniform &uModelMat) {
	
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
		uModelMat.set(matrices.top());
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
		program_depth.bind();
		
		/* Set depth matrices */
		shadowMatV = glm::lookAt(camera.getPosition() + lightDir.getDirection(), camera.getPosition(), glm::vec3(0,1,0));
		uDepthV.set(shadowMatV);
		uDepthP.set(shadowMatP);
		
		/* Draw shadow depth */
		glViewport(0, 0, shadowSizeX, shadowSizeY);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		drawEverything(uDepthM);
		
		/* Unbind shadow & depth program*/
		program_depth.unbind();
		shadowFB.unbind();
		
	}
	
	/* Bind program */
	program.bind();
	
	/* Set view matrix */
	uViewMat.set(camera.getViewMatrix());
	
	/* Set shadow sampler */
	glActiveTexture(GL_TEXTURE5);
	shadowTexture.bind();
	uShadowSampler.set1i(5);
	if (shadowEnable) {
		uShadowVP.set(
			glm::mat4(
				0.5, 0.0, 0.0, 0.0, 
				0.0, 0.5, 0.0, 0.0,
				0.0, 0.0, 0.5, 0.0,
				0.5, 0.5, 0.5, 1.0
			) * shadowMatP * shadowMatV
		);
	}
	
	/* Set directional light */
	uDirLightColor    .set   (lightDir.getColor());
	uDirLightIntensity.set1f (lightDir.getIntensity());
	uDirLightDirection.set   (lightDir.getDirection());
	
	/* Set point light */
	uPointLightColor    .set   (lightPoint.getColor());
	uPointLightIntensity.set1f (lightPoint.getIntensity());
	uPointLightSpread   .set1f (lightPoint.getSpread());
	uPointLightPosition .set   (lightPoint.getPosition());
	
	/* Draw scene */
	glViewport(0, 0, sceneWidth, sceneHeight);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	drawEverything(uModelMat);
	
	/* Unbind program */
	program.unbind();
	
}

void Scene::updateShadowTexelSize()
{
	program.bind();
	uShadowTexelSize.set(shadowSamplesSpread * glm::vec2(1. / shadowSizeX, 1. / shadowSizeY));
	program.unbind();
}

void Scene::setShadowSamples(int x, int y, float spread)
{
	shadowSamplesX = x;
	shadowSamplesY = y;
	shadowSamplesSpread = spread;
	program.bind();
	uShadowSamples.set2i(x, y);
	program.unbind();
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
	program.bind();
	uShadowDepthBias.set1f(bias);
	program.unbind();
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
	program.bind();
	uAmbient.set1f(amount);
	program.unbind();
}

void Scene::updateProjection()
{
	program.bind();
	uProjMat.set(camera.getProjectionMatrix());
	program.unbind();
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
