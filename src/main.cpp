#include "Engine/Engine.hpp"
#include "Engine/Obj/TriangleReader.hpp"
#include <SFML/Window.hpp>
#include <iostream>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

#define M_PI    3.14159265358979323846
#define M_PI_2  1.57079632679489661923
#define M_2_PI  (M_PI * 2)

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
	
	GL::ProgramUniform viewMatrix;
	GL::ProgramUniform projectionMatrix;
	
public:

	glm::vec3 position;
	float rotX, rotY;
	
	Camera(GL::ProgramUniform view, GL::ProgramUniform proj);
	void setProjection(float fov, float aspect, float zNear, float zFar);
	void setView();
	void moveRelative(glm::vec3 amount);
	void rotateRelative(float x, float y);
	
};

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
	GL::ProgramUniform modelMatrix = program.getUniform("uModelMat");
	
	/* Set up camera */
	Camera camera(program.getUniform("uViewMat"), program.getUniform("uProjMat"));
	program.bind();
	camera.setProjection(M_PI_2,  window.getSize().x / (float) window.getSize().y, 0.1f, 100.0f);
	camera.setView();
	program.unbind();
	
	/* Load mesh */
	Mesh mesh;
	mesh.create("assets/monkey.obj");
	
	/* Initialize OpenGL parameters */
	initOpenGL();
	
	/* Main loop */
	sf::Clock clock;
	bool running = true, cursorLocked = false, isFocused = true;
	while (running) {
		float elapsedSeconds = clock.getElapsedTime().asSeconds();
		clock.restart();
		float cameraMoveSpeed = elapsedSeconds * 20;
		float cameraRotateSpeed = elapsedSeconds * 60;
		
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
				camera.setProjection(M_PI_2,  window.getSize().x / (float) window.getSize().y, 0.1f, 100.0f);
				program.unbind();
				break;
			case sf::Event::KeyReleased:
				if (event.key.code == sf::Keyboard::Key::Escape) {
					if (cursorLocked) cursorLocked = false; else running = false;
				}
			case sf::Event::MouseButtonReleased:
				if (event.mouseButton.button == sf::Mouse::Button::Left && isFocused) {
					sf::Mouse::setPosition(sf::Vector2i(window.getSize().x / 2, window.getSize().y / 2), window);
					cursorLocked = true;
				}
				break;
			case sf::Event::GainedFocus: isFocused = true; break;
			case sf::Event::LostFocus: isFocused = false; cursorLocked = false; break;
			case sf::Event::MouseMoved:
				if (cursorLocked) {
					int midX = window.getSize().x / 2;
					int midY = window.getSize().y / 2;
					int diffX = event.mouseMove.x - midX;
					int diffY = event.mouseMove.y - midY;
					if (diffX != 0 || diffY != 0) {
						sf::Mouse::setPosition(sf::Vector2i(midX, midY), window);
						camera.rotateRelative(cameraRotateSpeed * diffY / (float) midY, cameraRotateSpeed * diffX / (float) midX);
					}
				}
				break;
			default: break;
			}
		}
		
		if (cursorLocked) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) camera.moveRelative(glm::vec3(0, 0, -cameraMoveSpeed));
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) camera.moveRelative(glm::vec3(0, 0, cameraMoveSpeed));
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) camera.moveRelative(glm::vec3(-cameraMoveSpeed, 0, 0));
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) camera.moveRelative(glm::vec3(cameraMoveSpeed, 0, 0));
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) camera.moveRelative(glm::vec3(0, cameraMoveSpeed, 0));
		}
		
		/* Draw */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		program.bind();
		camera.setView();
		modelMatrix.set(
			glm::translate(glm::vec3(0.f, 0.f, -7.f))
			* glm::scale(glm::vec3(4.f, 4.f, 4.f))
		);
		mesh.draw();
		program.unbind();
		window.display();
	}
	
	return 0;
}

Camera::Camera(GL::ProgramUniform view, GL::ProgramUniform proj)
: viewMatrix(view), projectionMatrix(proj), position(glm::vec3(0)), rotX(0), rotY(0)
{}

void Camera::setProjection(float fov, float aspect, float zNear, float zFar) {
	projectionMatrix.set(glm::perspective(fov, aspect, zNear, zFar));
}

void Camera::setView() {
	glm::vec3 direction = glm::vec3(0, 0, -1);
	direction = glm::rotateX(direction, rotX);
	direction = glm::rotateY(direction, rotY);
	viewMatrix.set(glm::lookAt(position, position + direction, glm::vec3(0, 1, 0)));
}

void Camera::moveRelative(glm::vec3 amount) {
	amount = glm::rotateX(amount, rotX);
	amount = glm::rotateY(amount, rotY);
	position = position + amount;
}

void Camera::rotateRelative(float x, float y) {
	rotX -= x;
	rotY -= y;
	if (rotX > M_PI_2) rotX = M_PI_2;
	if (rotX < -M_PI_2) rotX = -M_PI_2;
	if (rotY > M_PI) rotY -= M_2_PI;
	if (rotY < -M_PI) rotY += M_2_PI;
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
