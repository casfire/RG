#include "Engine/Engine.hpp"
#include <SFML/Window.hpp>
#include <iostream>

namespace E = Engine;
namespace GL = Engine::GL;
namespace A = Engine::Asset;

void initOpenGL();

int main() {
	
	/* Create window and OpenGL context */
	sf::Window window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default);
	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false);
	
	/* Load OpenGL functions */
	if (ogl_LoadFunctions() == ogl_LOAD_FAILED) {
		std::cout << "Failed to load OpenGL" << std::endl;
		return -1;
	}
	std::cout << "OpenGL version " << glGetString(GL_VERSION) << " loaded." << std::endl;
	
	/* Assets */
	A::Storage storage;
	const GL::Program& program = storage.grab<A::GLProgram>("assets/program.txt").get();
	const GL::Texture2D& texture = storage.grab<A::CFRTexture2D>("assets/texture.cfrt").get();
	
	/* Uniforms */
	GL::ProgramUniform uModelMat = program.getUniform("uModelMat");
	GL::ProgramUniform uViewMat = program.getUniform("uViewMat");
	GL::ProgramUniform uProjMat = program.getUniform("uProjMat");
	
	/* Set up camera */
	E::Camera camera;
	camera.setAspect(window.getSize().x, window.getSize().y);
	program.bind();
	uProjMat.set(camera.getProjectionMatrix());
	uViewMat.set(glm::mat4(1));
	program.unbind();
	
	/* Load mesh */
	E::Transformation modelMatrix;
	
	/* Initialize OpenGL parameters */
	initOpenGL();
	
	/* Main loop */
	bool running = true;
	while (running) {
		
		/* Events */
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				running = false;
				break;
			case sf::Event::Resized:
				glViewport(0, 0, event.size.width, event.size.height);
				program.bind();
				camera.setAspect(window.getSize().x, window.getSize().y);
				uProjMat.set(camera.getProjectionMatrix());
				program.unbind();
				break;
			default: break;
			}
		}
		
		/* Draw */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		program.bind();
		uModelMat.set(modelMatrix.getMatrix());
		uViewMat.set(camera.getViewMatrix());
		program.unbind();
		
		window.display();
	}
	
	return 0;
}

void initOpenGL() {
	
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
