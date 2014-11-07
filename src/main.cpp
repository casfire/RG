#include <iostream>
#include "graphics/gl_core_3_3.h"
#include "graphics/Shader.hpp"
#include <SFML/Window.hpp>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>


float xrand(float min, float max) {
	return min + (max - min) * ((std::rand()) / (float) RAND_MAX);
}

class Model {
	std::uint32_t vertexCount, triangleCount;
	std::vector<float> vertexBuffer;
	std::vector<std::uint32_t> elementBuffer;
	GLuint arrayBufferID, elementBufferID, vaoID;
public:

	Model() {
		vertexCount = 0;
		triangleCount = 0;
		arrayBufferID = 0; elementBufferID = 0; vaoID = 0;
	}
	
	std::uint32_t addVertex(float x, float y, float z, float r, float g, float b) {
		vertexBuffer.push_back(x);
		vertexBuffer.push_back(y);
		vertexBuffer.push_back(z);
		vertexBuffer.push_back(r);
		vertexBuffer.push_back(g);
		vertexBuffer.push_back(b);
		std::uint32_t ret = vertexCount;
		vertexCount++;
		return ret;
	}
	
	void addTriangle(std::uint32_t a, std::uint32_t b, std::uint32_t c) {
		elementBuffer.push_back(a);
		elementBuffer.push_back(b);
		elementBuffer.push_back(c);
		triangleCount++;
	}
	
	void addCube(float x, float y, float z, float sizeX = 1.0, float sizeY = 1.0, float sizeZ = 1.0) {
		sizeX /= 2.f;
		sizeY /= 2.f;
		sizeZ /= 2.f;
		std::uint32_t a = addVertex(x - sizeX, y - sizeY, z + sizeZ, xrand(0, 1), xrand(0, 1), xrand(0, 1));
		std::uint32_t b = addVertex(x + sizeX, y - sizeY, z + sizeZ, xrand(0, 1), xrand(0, 1), xrand(0, 1));
		std::uint32_t c = addVertex(x + sizeX, y - sizeY, z - sizeZ, xrand(0, 1), xrand(0, 1), xrand(0, 1));
		std::uint32_t d = addVertex(x - sizeX, y - sizeY, z - sizeZ, xrand(0, 1), xrand(0, 1), xrand(0, 1));
		std::uint32_t e = addVertex(x - sizeX, y + sizeY, z + sizeZ, xrand(0, 1), xrand(0, 1), xrand(0, 1));
		std::uint32_t f = addVertex(x + sizeX, y + sizeY, z + sizeZ, xrand(0, 1), xrand(0, 1), xrand(0, 1));
		std::uint32_t g = addVertex(x + sizeX, y + sizeY, z - sizeZ, xrand(0, 1), xrand(0, 1), xrand(0, 1));
		std::uint32_t h = addVertex(x - sizeX, y + sizeY, z - sizeZ, xrand(0, 1), xrand(0, 1), xrand(0, 1));
		addTriangle(a, f, b);
		addTriangle(a, e, f);
		addTriangle(b, g, c);
		addTriangle(b, f, g);
		addTriangle(c, g, d);
		addTriangle(d, g, h);
		addTriangle(d, e, a);
		addTriangle(d, h, e);
		addTriangle(e, g, f);
		addTriangle(e, h, g);
		addTriangle(a, b, c);
		addTriangle(a, c, d);
	}
	
	void create() {
		
		glGenBuffers(1, &arrayBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, arrayBufferID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexBuffer.size(), static_cast<const GLvoid*>(&vertexBuffer[0]), GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		
		glGenBuffers(1, &elementBufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(std::uint32_t) * elementBuffer.size(), static_cast<const GLvoid*>(&elementBuffer[0]), GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		
		glGenVertexArrays(1, &vaoID);
		glBindVertexArray(vaoID);
		glBindBuffer(GL_ARRAY_BUFFER, arrayBufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferID);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*) 0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*) (3 * sizeof(float)));
		glBindVertexArray(0);
	}
	
	void draw() {
		
		glBindVertexArray(vaoID);
		glDrawElements(GL_TRIANGLES, 3 * triangleCount, GL_UNSIGNED_INT, (GLvoid*) 0);
		glBindVertexArray(0);
		
	}
	

};

int main() {
	
	/* Create window and load OpenGL */
	sf::Window window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default);
	window.setFramerateLimit(60);
	if(ogl_LoadFunctions() == ogl_LOAD_FAILED) {
		std::cout << "Failed to load OpenGL" << std::endl;
		return -1;	
	}
	std::cout << "OpenGL version " << glGetString(GL_VERSION) << " loaded." << std::endl;
	
	
	/* Shaders */
	GE::Program program = GE::Program(GE::ShaderFile("vertex.vert"), GE::ShaderFile("fragment.frag"));
	
	/* Model */
	Model model;
	model.addCube(0, 0, 0, 4, 4, 4);
	model.create();
	
	/* MVP */
	glm::mat4 MVP_m = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, -7.f)) * glm::rotate(0.6f, glm::vec3(1.f, 1.f, 0.f));
	glm::mat4 MVP_v = glm::mat4(1.0f); // identity
	glm::mat4 MVP_p = glm::perspective(1.57079632f, window.getSize().x / (float) window.getSize().y, 0.1f, 100.0f);
	GLuint MVP_m_ID = glGetUniformLocation(program.getID(), "MVP_m");
	GLuint MVP_v_ID = glGetUniformLocation(program.getID(), "MVP_v");
	GLuint MVP_p_ID = glGetUniformLocation(program.getID(), "MVP_p");
	glUseProgram(program.getID());
	glUniformMatrix4fv(MVP_m_ID, 1, GL_FALSE, glm::value_ptr(MVP_m));
	glUniformMatrix4fv(MVP_v_ID, 1, GL_FALSE, glm::value_ptr(MVP_v));
	glUniformMatrix4fv(MVP_p_ID, 1, GL_FALSE, glm::value_ptr(MVP_p));
	glUseProgram(0);
	
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);
	
	sf::Clock clock;
	bool run = true;
	while (run) {
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Resized:
				glViewport(0, 0, static_cast<GLsizei>(event.size.width), static_cast<GLsizei>(event.size.height));
				MVP_p = glm::perspective(1.57079632f, window.getSize().x / (float) window.getSize().y, 0.1f, 100.0f);
				glUseProgram(program.getID());
				glUniformMatrix4fv(MVP_p_ID, 1, GL_FALSE, glm::value_ptr(MVP_p));
				glUseProgram(0);
				break;
			case sf::Event::Closed:
				run = false;
				break;
			default: break;
			}
		}
		float elapsedSeconds = clock.getElapsedTime().asSeconds();
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glUseProgram(program.getID());
		
		/* Update MVP_m */
		MVP_m = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, -7.f)) * glm::rotate(elapsedSeconds * 4.f, glm::vec3(-0.1f, 1.f, 0.6f));
		glUniformMatrix4fv(MVP_m_ID, 1, GL_FALSE, glm::value_ptr(MVP_m));
		
		/* Draw */
		model.draw();
		
		glUseProgram(0);
		
		window.display();
	}
	
	return 0;
}
