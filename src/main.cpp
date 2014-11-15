#include "Engine/Engine.hpp"
#include <SFML/Window.hpp>
#include <iostream>

namespace E = Engine;
namespace GL = Engine::GL;
namespace A = Engine::Asset;

int main() {
	
	/* Create window and OpenGL context */
	sf::Window window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default);
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);
	
	/* Load OpenGL functions */
	if (ogl_LoadFunctions() == ogl_LOAD_FAILED) {
		std::cout << "Failed to load OpenGL" << std::endl;
		return -1;
	}
	std::cout << "OpenGL version " << glGetString(GL_VERSION) << " loaded." << std::endl;
	
	/* Create asset storage */
	A::Storage storage;
	
	/* Initialization */
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	A::GLProgram* program = storage.grab<A::GLProgram>("assets/program.txt");	
	
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
				break;
			default: break;
			}
		}
		
		/* Draw */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		program->get().bind();
		
		program->get().unbind();
		window.display();
	}
	
	storage.release(program);
	
	return 0;
}
