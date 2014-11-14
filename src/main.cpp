#include "Graphics/Graphics.hpp"

#include <SFML/Window.hpp>
#include <iostream>

namespace G = Graphics;
namespace GL = Graphics::GL;
namespace A = Graphics::Asset;

int main() {
	
	/* Create window and OpenGL context */
	sf::Window window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default);
	window.setFramerateLimit(60);
	
	/* Load OpenGL functions */
	if (ogl_LoadFunctions() == ogl_LOAD_FAILED) {
		std::cout << "Failed to load OpenGL" << std::endl;
		return -1;
	}
	std::cout << "OpenGL version " << glGetString(GL_VERSION) << " loaded." << std::endl;
	
	/* Create asset storage */
	A::Storage storage;
	
	/* Grab and release GLProgram from the storage */
	A::GLProgram* program1 = storage.grab<A::GLProgram>("assets/program.txt");
	A::GLProgram* program2 = storage.grab<A::GLProgram>("assets/program.txt");
	storage.release(program1);
	storage.release(program2);
	
	return 0;
}
