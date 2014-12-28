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
	const GL::VAO& vao = storage.grab<A::CFRGeometry>("assets/cube.cfrg").get();
	
	/* Texture */
	const GL::Texture2D& texture = storage.grab<A::CFRTexture2D>("assets/texture.cfrt").get();
	texture.bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	texture.unbind();
	
	/* Uniforms */
	GL::ProgramUniform uModelMat = program.getUniform("uModelMat");
	GL::ProgramUniform uViewMat  = program.getUniform("uViewMat");
	GL::ProgramUniform uProjMat  = program.getUniform("uProjMat");
	GL::ProgramUniform uTexture  = program.getUniform("uTexture");
	
	/* Set up camera */
	E::Camera camera;
	camera.setAspect(window.getSize().x, window.getSize().y);
	program.bind();
	uProjMat.set(camera.getProjectionMatrix());
	uViewMat.set(glm::mat4(1));
	program.unbind();
	
	/* Load mesh */
	E::Transformation modelMatrix;
	modelMatrix.setPosition(glm::vec3(0, 0, -20));
	modelMatrix.setScale(glm::vec3(10, 10, 10));
	
	/* Initialize OpenGL parameters */
	initOpenGL();
	
	/* Main loop */
	bool running = true, cursorLocked = false;
	sf::Clock clock;
	sf::Time elapsedLast = sf::Time::Zero;
	while (running) {
		
		sf::Time elapsedNow = clock.getElapsedTime();
		sf::Time elapsedFrame = elapsedNow - elapsedLast;
		elapsedLast = elapsedNow;
		
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
			case sf::Event::KeyReleased:
				if (event.key.code == sf::Keyboard::Key::Escape) {
					if (cursorLocked) cursorLocked = false; else running = false;
				}
			case sf::Event::MouseButtonReleased:
				if (event.mouseButton.button == sf::Mouse::Button::Left && window.hasFocus()) {
					sf::Mouse::setPosition(sf::Vector2i(window.getSize().x / 2, window.getSize().y / 2), window);
					cursorLocked = true;
				}
				break;
			case sf::Event::LostFocus: cursorLocked = false; break;
			default: break;
			}
		}
		
		if (cursorLocked) {
			float cameraMoveSpeed = elapsedFrame.asSeconds() * 30;
			float cameraRotateSpeed = 0.004;
			float cameraRollSpeed = elapsedFrame.asSeconds();
			
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			sf::Vector2i windowMid = sf::Vector2i(window.getSize().x / 2, window.getSize().y / 2);
			if (mousePos != windowMid) {
				float moveX = cameraRotateSpeed * (mousePos.x - windowMid.x);
				float moveY = cameraRotateSpeed * (mousePos.y - windowMid.y);
				camera.yaw(-moveX);
				camera.pitchLocal(-moveY);
				sf::Mouse::setPosition(windowMid, window);
			}
			
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) camera.translateLocal(glm::vec3(0, 0, -cameraMoveSpeed));
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) camera.translateLocal(glm::vec3(0, 0,  cameraMoveSpeed));
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) camera.translateLocal(glm::vec3(-cameraMoveSpeed, 0, 0));
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) camera.translateLocal(glm::vec3( cameraMoveSpeed, 0, 0));
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) camera.rollLocal( cameraRollSpeed);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) camera.rollLocal(-cameraRollSpeed);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))  camera.translate(glm::vec3(0,  cameraMoveSpeed, 0));
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) camera.translate(glm::vec3(0, -cameraMoveSpeed, 0));
		}
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		program.bind();
		glActiveTexture(GL_TEXTURE0);
		texture.bind();
		uTexture.set1i(GL_TEXTURE0);
		
		uModelMat.set(modelMatrix.getMatrix());
		uViewMat.set(camera.getViewMatrix());
		vao.drawTriangles();
		
		texture.unbind();
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
