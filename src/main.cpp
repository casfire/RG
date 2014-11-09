#include <iostream>
#include "Graphics/Graphics.hpp"
#include <SFML/Window.hpp>
#include <cstdint> // std::uint32_t
#include <vector>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

namespace GL = Graphics::GL;

float xrand(float min, float max) {
	return min + (max - min) * (std::rand() / (float) RAND_MAX);
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
	
	std::uint32_t addVertex(glm::vec3 position, glm::vec3 normal, glm::vec3 color) {
		vertexBuffer.push_back(position.x);
		vertexBuffer.push_back(position.y);
		vertexBuffer.push_back(position.z);
		vertexBuffer.push_back(normal.x);
		vertexBuffer.push_back(normal.y);
		vertexBuffer.push_back(normal.z);
		vertexBuffer.push_back(color.x);
		vertexBuffer.push_back(color.y);
		vertexBuffer.push_back(color.z);
		return vertexCount++;
	}
	
	glm::vec3 getVertexPosition(std::uint32_t v) {
		return glm::vec3(vertexBuffer[9 * v + 0], vertexBuffer[9 * v + 1], vertexBuffer[9 * v + 2]);	
	}
	
	std::uint32_t addVertex(glm::vec3 position, glm::vec3 normal) {
		return addVertex(position, normal, glm::vec3(xrand(0, 1), xrand(0, 1), xrand(0, 1)));
	}
	
	std::uint32_t addVertex(glm::vec3 position) {
		return addVertex(position, position, glm::vec3(xrand(0, 1), xrand(0, 1), xrand(0, 1)));
	}
	
	void addTriangle(std::uint32_t a, std::uint32_t b, std::uint32_t c) {
		elementBuffer.push_back(a);
		elementBuffer.push_back(b);
		elementBuffer.push_back(c);
		triangleCount++;
	}
	
	void addCube() {
		std::uint32_t a = addVertex(glm::vec3(-0.5f, -0.5f, +0.5f));
		std::uint32_t b = addVertex(glm::vec3(+0.5f, -0.5f, +0.5f));
		std::uint32_t c = addVertex(glm::vec3(+0.5f, -0.5f, -0.5f));
		std::uint32_t d = addVertex(glm::vec3(-0.5f, -0.5f, -0.5f));
		std::uint32_t e = addVertex(glm::vec3(-0.5f, +0.5f, +0.5f));
		std::uint32_t f = addVertex(glm::vec3(+0.5f, +0.5f, +0.5f));
		std::uint32_t g = addVertex(glm::vec3(+0.5f, +0.5f, -0.5f));
		std::uint32_t h = addVertex(glm::vec3(-0.5f, +0.5f, -0.5f));
		addTriangle(a, f, b); addTriangle(a, e, f);
		addTriangle(b, g, c); addTriangle(b, f, g);
		addTriangle(c, g, d); addTriangle(d, g, h);
		addTriangle(d, e, a); addTriangle(d, h, e);
		addTriangle(e, g, f); addTriangle(e, h, g);
		addTriangle(a, b, c); addTriangle(a, c, d);
	}
	
	void addIcosphere(int subdivisions = 5) {
		float t = (std::sqrt(5.f) + 1.f) / 2.f;
		std::vector<glm::vec3> v(12);
		std::vector<glm::vec3> c(12);
		std::vector<glm::ivec3> f;
		v[0]  = glm::vec3( 0,  t, -1);
		v[1]  = glm::vec3( 0,  t,  1);
		v[2]  = glm::vec3( 0, -t, -1);
		v[3]  = glm::vec3( 0, -t,  1);
		v[4]  = glm::vec3( t, -1,  0);
		v[5]  = glm::vec3( t,  1,  0);
		v[6]  = glm::vec3(-t, -1,  0);
		v[7]  = glm::vec3(-t,  1,  0);
		v[8]  = glm::vec3(-1,  0,  t);
		v[9]  = glm::vec3( 1,  0,  t);
		v[10] = glm::vec3(-1,  0, -t);
		v[11] = glm::vec3( 1,  0, -t);
		for (unsigned i = 0; i < 12; i++) c[i] = glm::vec3(xrand(0, 1), xrand(0, 1), xrand(0, 1));
		f.push_back(glm::ivec3(0, 11, 5));
		f.push_back(glm::ivec3(0, 5, 1));
		f.push_back(glm::ivec3(0, 1, 7));
		f.push_back(glm::ivec3(0, 7, 10));
		f.push_back(glm::ivec3(0, 10, 11));
		f.push_back(glm::ivec3(1, 5, 9));
		f.push_back(glm::ivec3(5, 11, 4));
		f.push_back(glm::ivec3(11, 10, 2));
		f.push_back(glm::ivec3(10, 7, 6));
		f.push_back(glm::ivec3(7, 1, 8));
		f.push_back(glm::ivec3(3, 9, 4));
		f.push_back(glm::ivec3(3, 4, 2));
		f.push_back(glm::ivec3(3, 2, 6));
		f.push_back(glm::ivec3(3, 6, 8));
		f.push_back(glm::ivec3(3, 8, 9));
		f.push_back(glm::ivec3(4, 9, 5));
		f.push_back(glm::ivec3(2, 4, 11));
		f.push_back(glm::ivec3(6, 2, 10));
		f.push_back(glm::ivec3(8, 6, 7));
		f.push_back(glm::ivec3(9, 8, 1));
		while (subdivisions-- > 0) {
			std::vector<glm::ivec3> nf;
			std::vector<glm::ivec3> nc;
			for (unsigned i = 0; i < f.size(); i++) {
				glm::ivec3 face = f[i];
				int s = (int) v.size();
				v.push_back(glm::mix(v[face.x], v[face.y], 0.5));
				v.push_back(glm::mix(v[face.y], v[face.z], 0.5));
				v.push_back(glm::mix(v[face.z], v[face.x], 0.5));
				c.push_back(glm::mix(c[face.x], c[face.y], 0.5));
				c.push_back(glm::mix(c[face.y], c[face.z], 0.5));
				c.push_back(glm::mix(c[face.z], c[face.x], 0.5));
				nf.push_back(glm::ivec3(face.x, s + 0, s + 2));
				nf.push_back(glm::ivec3(s + 0, face.y, s + 1));
				nf.push_back(glm::ivec3(s + 2, s + 1, face.z));
				nf.push_back(glm::ivec3(s + 0, s + 1, s + 2));
			}
			f = nf;
		}
		std::vector<std::uint32_t> index(v.size());
		for (unsigned i = 0; i < v.size(); i++) {
			v[i] = glm::normalize(v[i]);
			index[i] = addVertex(v[i], v[i], c[i]);
		}
		for (unsigned i = 0; i < f.size(); i++) {
			glm::ivec3 face = f[i];
			addTriangle(index[face.x], index[face.y], index[face.z]);
		}
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
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (GLvoid*) 0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (GLvoid*) (3 * sizeof(float)));
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (GLvoid*) (6 * sizeof(float)));
		glBindVertexArray(0);
		
	}
	
	void draw() {
		
		glBindVertexArray(vaoID);
		glDrawElements(GL_TRIANGLES, 3 * triangleCount, GL_UNSIGNED_INT, (GLvoid*) 0);
		glBindVertexArray(0);
		
	}
	
};

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
	
	/* Create GLSL Program */
	GL::Program program;
	try {
		program.attach(GL::VertexShader(GL::ShaderFile("vertex.vert")));
		program.attach(GL::FragmentShader(GL::ShaderFile("fragment.frag")));
		program.link();
	} catch (GL::ProgramLinkException &fail) {
		std::cout << fail.what() << "\nLog:" << fail.log() << std::endl;
		return -1;
	} catch (GL::ShaderCompileException &fail) {
		std::cout << fail.what()  << "\nLog: " << fail.log() << std::endl;
		return -1;
	}
	
	/* Model */
	Model model;
	model.addIcosphere();
	model.create();
	
	/* MVP */
	GL::ProgramUniform MVP_m = program.getUniform("mat_M");
	GL::ProgramUniform MVP_v = program.getUniform("mat_V");
	GL::ProgramUniform MVP_p = program.getUniform("mat_P");
	program.bind();
	MVP_v.set(glm::mat4(1.0f));
	MVP_p.set(glm::perspective(1.57079632f, window.getSize().x / (float) window.getSize().y, 0.1f, 100.0f));
	
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

	/* Main loop */
	sf::Clock clock;
	bool run = true;
	while (run) {
		
		/* Handle events */
		
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				run = false;
				break;
			case sf::Event::Resized:
				glViewport(0, 0, event.size.width, event.size.height);
				program.bind();
				MVP_p.set(glm::perspective(1.57079632f, window.getSize().x / (float) window.getSize().y, 0.1f, 100.0f));
				break;
			default: break;
			}
		}
		
		float elapsedSeconds = clock.getElapsedTime().asSeconds();
		MVP_m.set(
			  glm::translate(glm::vec3(0.f, 0.f, -7.f))
			* glm::rotate(elapsedSeconds * 1.f, glm::vec3(0.f, 1.f, 0.f))
			* glm::rotate(0.05f, glm::vec3(1.f, 0.f, 0.f))
			* glm::scale(glm::vec3(4.f, 4.f, 4.f))
		);

		/* Draw */
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		program.bind();
		model.draw();
		
		window.display();
		
	}
	
	return 0;
}
