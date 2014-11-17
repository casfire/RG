#include "Engine/Engine.hpp"
#include "Engine/Obj/TriangleReader.hpp"
#include <SFML/Window.hpp>
#include <iostream>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

#define M_PI    3.14159265358979323846
#define M_PI_2  1.57079632679489661923

namespace E = Engine;
namespace GL = Engine::GL;
namespace A = Engine::Asset;
namespace Obj = Engine::Obj;

class Mesh {
protected:
	
	GL::VAO vao;
	std::uint32_t triangleCount, vertexCount;
	std::vector<float> vertexBuffer;
	std::vector<std::uint32_t> elementBuffer;
	
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
	
	void addTriangle(std::uint32_t a, std::uint32_t b, std::uint32_t c) {
		elementBuffer.push_back(a);
		elementBuffer.push_back(b);
		elementBuffer.push_back(c);
		triangleCount++;
	}
	
public:
	
	Mesh() {
		vertexCount = 0;
		triangleCount = 0;
	}
	
	void create(const std::string& objfile) {
		
		Obj::TriangleReader obj;
		obj.read(objfile, std::cout);
		for (std::size_t i = 0; i < obj.vertices().size(); i++) {
			Obj::Vertex::Geometry position = obj.vertices()[i].geometry;
			Obj::Vertex::Normal normal = obj.vertices()[i].normal;
			addVertex(
				glm::vec3(position.x, position.y, position.z),
				glm::vec3(normal.i, normal.j, normal.k),
				glm::vec3(0.5, 0.8, 0.3)
			);
		}
		for (std::size_t i = 0; i < obj.triangles().size(); i++) {
			addTriangle(
				obj.triangles()[i].a,
				obj.triangles()[i].c,
				obj.triangles()[i].b
			);
		}
		obj.clear();
		
		GL::ArrayBuffer vertexBufferGL;
		GL::ElementBuffer32 elementBufferGL;
		vertexBufferGL.data(sizeof(float) * vertexBuffer.size(), &vertexBuffer[0]);
		elementBufferGL.elements(elementBuffer.size(), &elementBuffer[0]);
		
		vao.bind();
		elementBufferGL.bind();
		vertexBufferGL.enableVertexAttribute(0, 3, GL_FLOAT, 9 * sizeof(float), 0);
		vertexBufferGL.enableVertexAttribute(1, 3, GL_FLOAT, 9 * sizeof(float), 3 * sizeof(float));
		vertexBufferGL.enableVertexAttribute(2, 3, GL_FLOAT, 9 * sizeof(float), 6 * sizeof(float));
		vao.unbind();
	}
	
	void draw() {
		vao.bind();
		glDrawElements(GL_TRIANGLES, 3 * triangleCount, GL_UNSIGNED_INT, reinterpret_cast<const GLvoid*>(0));
		vao.unbind();
	}
	
};

class Camera {
	
	const GL::Program &program;
	GL::ProgramUniform viewMatrix;
	GL::ProgramUniform projectionMatrix;
	
public:

	glm::vec3 position;
	float rotX, rotY;
	
	Camera(const GL::Program &p);
	void setProjection(float fov, float aspect, float zNear, float zFar);
	void setView();
	
};

void initOpenGL();

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
	
	/* Assets */
	A::Storage storage;
	A::GLProgram* program = storage.grab<A::GLProgram>("assets/program.txt");
	GL::ProgramUniform modelMatrix = program->get().getUniform("uModelMat");
	
	/* Set up camera */
	Camera camera(program->get());
	camera.setProjection(M_PI_2,  window.getSize().x / (float) window.getSize().y, 0.1f, 100.0f);
	camera.setView();
	
	/* Load mesh */
	Mesh mesh;
	mesh.create("assets/monkey.obj");
	
	/* Initialize OpenGL parameters */
	initOpenGL();
	
	/* Main loop */
	sf::Clock clock;
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
				camera.setProjection(M_PI_2,  window.getSize().x / (float) window.getSize().y, 0.1f, 100.0f);
				break;
			default: break;
			}
		}
		
		float elapsedSeconds = clock.getElapsedTime().asSeconds();
		
		/* Draw */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		program->get().bind();
		
		modelMatrix.set(
			glm::translate(glm::vec3(0.f, 0.f, -7.f))
			* glm::rotate(elapsedSeconds * 1.f, glm::vec3(0.f, 1.f, 0.f))
			* glm::scale(glm::vec3(4.f, 4.f, 4.f))
		);
		
		mesh.draw();
		
		program->get().unbind();
		window.display();
	}
	
	storage.release(program);
	
	return 0;
}

Camera::Camera(const GL::Program &p)
: program(p),
viewMatrix(p.getUniform("uViewMat")), projectionMatrix(p.getUniform("uProjMat")),
position(glm::vec3(0)), rotX(0), rotY(0)
{}

void Camera::setProjection(float fov, float aspect, float zNear, float zFar) {
	program.bind();
	projectionMatrix.set(glm::perspective(fov, aspect, zNear, zFar));
	program.unbind();
}

void Camera::setView() {
	program.bind();
	viewMatrix.set(
		glm::translate(position)
		* glm::rotate(rotX, glm::vec3(1, 0, 0))
		* glm::rotate(rotY, glm::vec3(0, 1, 0))
	);
	program.unbind();
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
