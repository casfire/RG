#include "Engine/Engine.hpp"
#include <SFML/Window.hpp>
#include <iostream>

namespace E = Engine;

int main() {
	
	/* Create window and OpenGL context */
	sf::Window window(sf::VideoMode(800, 600), "Engine", sf::Style::Default);
	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false);
	
	/* Create and initialize engine */
	E::MainEngine engine;
	engine.init();
	
	/* Print engine information */
	std::cout << "Engine initialized." << std::endl;
	std::cout << "OpenGL version: " << engine.getOpenGLVersion()  << std::endl;
	std::cout << "  GLSL version: " << engine.getShadingVersion() << std::endl;
	std::cout << "      Renderer: " << engine.getRendererName()   << std::endl;
	std::cout << "        Vendor: " << engine.getVendorName()     << std::endl;
	
	/* Create scene and retrieve camera */
	E::Scene& scene = engine.createScene(window.getSize().x, window.getSize().y);
	E::Camera& camera = scene.getCamera();
	
	/* Load model and attach to scene */
	E::Node& cube = engine.loadModel("assets/cube.cfrm");
	scene.attach(cube);
	cube.setPosition(glm::vec3(0, 0, -5));
	
	/* Main loop */
	bool running = true, cursorLocked = false;
	sf::Clock clock;
	sf::Time elapsedLast = sf::Time::Zero;
	while (running) {
		
		/* Timing */
		sf::Time elapsedNow = clock.getElapsedTime();
		sf::Time elapsedFrame = elapsedNow - elapsedLast;
		elapsedLast = elapsedNow;
		
		/* Handle events */
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			default: break;
			case sf::Event::Closed:
				running = false;
				break;
			case sf::Event::Resized:
				scene.resize(event.size.width, event.size.height);
				break;
			case sf::Event::KeyReleased:
				if (event.key.code == sf::Keyboard::Key::Escape) {
					if (cursorLocked) cursorLocked = false; else running = false;
				}
				break;
			case sf::Event::MouseButtonReleased:
				if (event.mouseButton.button == sf::Mouse::Button::Left && window.hasFocus()) {
					sf::Mouse::setPosition(sf::Vector2i(window.getSize().x / 2, window.getSize().y / 2), window);
					cursorLocked = true;
				}
				break;
			case sf::Event::LostFocus: cursorLocked = false; break;
			}
		}
		
		/* Camera movement */
		if (cursorLocked) {
			float cameraMoveSpeed = elapsedFrame.asSeconds() * 10;
			float cameraRotateSpeed = 0.004;
			float cameraRollSpeed = elapsedFrame.asSeconds();
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			sf::Vector2i windowMid = sf::Vector2i(window.getSize().x / 2, window.getSize().y / 2);
			if (mousePos != windowMid) {
				float moveX = cameraRotateSpeed * (mousePos.x - windowMid.x);
				float moveY = cameraRotateSpeed * (mousePos.y - windowMid.y);
				camera.yaw(-moveX);
				camera.setRotation(camera.getRotation() * glm::quat(glm::vec3(-moveY, 0, 0)));
				sf::Mouse::setPosition(windowMid, window);
			}
			
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
				camera.setPosition(camera.getPosition() + camera.getRotation() * glm::vec3(0, 0, -cameraMoveSpeed));
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
				camera.setPosition(camera.getPosition() + camera.getRotation() * glm::vec3(0, 0, +cameraMoveSpeed));
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				camera.setPosition(camera.getPosition() + camera.getRotation() * glm::vec3(-cameraMoveSpeed, 0, 0));
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
				camera.setPosition(camera.getPosition() + camera.getRotation() * glm::vec3(+cameraMoveSpeed, 0, 0));
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
				camera.setRotation(camera.getRotation() * glm::quat(glm::vec3(0, 0, +cameraRollSpeed)));
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
				camera.setRotation(camera.getRotation() * glm::quat(glm::vec3(0, 0, -cameraRollSpeed)));
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
				camera.translate(glm::vec3(0, cameraMoveSpeed, 0));
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
				camera.translate(glm::vec3(0, -cameraMoveSpeed, 0));
			}
		}
		
		/* Set light position */
		scene.setLightPosition(camera.getPosition() + glm::vec3(0, 5, 0));
		
		/* Rotate model */
		cube.yaw(elapsedFrame.asSeconds());
		
		/* Draw scene */
		scene.draw();
		
		/* Update window */
		window.display();
		
	}
	
	return 0;
}

