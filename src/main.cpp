#include <iostream>
#include "graphics/gl_core_3_3.h"
#include "graphics/Shader.hpp"
#include <SFML/Window.hpp>

int main() {
	
	/* Create window and load OpenGL */
	sf::Window window(sf::VideoMode(800, 800), "OpenGL", sf::Style::Default);
	window.setFramerateLimit(60);
	if(ogl_LoadFunctions() == ogl_LOAD_FAILED) {
		std::cout << "Failed to load OpenGL" << std::endl;
		return -1;	
	}
	std::cout << "OpenGL version " << glGetString(GL_VERSION) << " loaded." << std::endl;
	
	
	/* Shaders */
	GE::Program program = GE::Program(GE::ShaderFile("vertex.vert"), GE::ShaderFile("fragment.frag"));
	
	/* Vertex array */
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	
	/* Vertex buffer */
	const float vertexPositions[] = {
		0.75f, 0.75f, 0.0f, 1.0f,
		0.75f, -0.75f,0.0f, 1.0f,
		-0.75f, -0.75f, 0.0f, 1.0f, };
	GLuint positionBufferObject;
	glGenBuffers(1, &positionBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	bool run = true;
	while (run) {
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Resized:
				glViewport(0, 0, static_cast<GLsizei>(event.size.width), static_cast<GLsizei>(event.size.height));
				break;
			case sf::Event::Closed:
				run = false;
				break;
			default: break;
			}
		}
		
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		glUseProgram(program.getID());

		glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glDisableVertexAttribArray(0);
		glUseProgram(0);
		
		window.display();
	}
	
	return 0;
}
