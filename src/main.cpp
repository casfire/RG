#include "Engine/Engine.hpp"
#include <SFML/Window.hpp>
#include <iostream>
#include <glm/gtx/rotate_vector.hpp>

namespace E = Engine;
typedef sf::Keyboard Key;

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
	
	/* Create scene, retrieve camera and lights */
	E::Scene& scene = engine.createScene(window.getSize().x, window.getSize().y);
	E::Camera&           camera     = scene.getCamera();
	E::PointLight&       lightPoint = scene.getPointLight();
	E::DirectionalLight& lightDir   = scene.getDirectionalLight();
	
	/* Set directional light properties */
	lightDir.setDirection(glm::vec3(0, 1, 0)); // Direction (up)
	lightDir.setColor    (glm::vec3(1, 1, 1)); // Color (white)
	lightDir.setIntensity(0.5f);               // Intensity
	
	/* Set point light properties */
	lightPoint.setPosition (glm::vec3(1, 3, 1)); // Position
	lightPoint.setColor    (glm::vec3(1, 1, 1)); // Color (white)
	lightPoint.setIntensity(5.f);                // Intensity
	lightPoint.setSpread   (0.25f);              // Inverse spread
	
	/* Load and attach skydome */
	E::Node& skydome = engine.loadModel("assets/skydome/skydome.cfrm");
	scene.attach(skydome);
	skydome.setScale(glm::vec3(200, 200, 200));
	
	/* Load and attach sphere */
	E::Node& sphere = engine.loadModel("assets/sphere/sphere.cfrm");
	scene.attach(sphere);
	sphere.setPosition(glm::vec3(0, 0, 0));
	
	/* Move camera back */
	camera.setPosition(glm::vec3(0, 0, 2));
	
	/* Main loop */
	bool running = true, cursorLocked = false;
	sf::Clock clock;
	sf::Time elapsedLast = sf::Time::Zero;
	while (running) {
		
		/* Timing */
		sf::Time elapsedNow = clock.getElapsedTime();
		sf::Time elapsedFrame = elapsedNow - elapsedLast;
		elapsedLast = elapsedNow;
		float elapsedSeconds = elapsedFrame.asSeconds();
		
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
			float cameraSpeedMove   = elapsedSeconds * 10;
			float cameraSpeedRotate = 0.004;
			float cameraSoeedRoll   = elapsedSeconds;
			sf::Vector2i mousePos   = sf::Mouse::getPosition(window);
			sf::Vector2i windowMid  = sf::Vector2i(window.getSize()) / 2;
			if (mousePos != windowMid) {
				glm::vec2 move = glm::vec2(windowMid.x, windowMid.y) - glm::vec2(mousePos.x, mousePos.y);
				camera.rotateY(move.x * cameraSpeedRotate);
				camera.rotateX(move.y * cameraSpeedRotate, camera);
				sf::Mouse::setPosition(windowMid, window);
			}
			if (Key::isKeyPressed(sf::Keyboard::W)) camera.translateZ(-cameraSpeedMove, camera);
			if (Key::isKeyPressed(sf::Keyboard::S)) camera.translateZ(+cameraSpeedMove, camera);
			if (Key::isKeyPressed(sf::Keyboard::A)) camera.translateX(-cameraSpeedMove, camera);
			if (Key::isKeyPressed(sf::Keyboard::D)) camera.translateX(+cameraSpeedMove, camera);
			if (Key::isKeyPressed(sf::Keyboard::Q)) camera.roll(+cameraSoeedRoll, camera);
			if (Key::isKeyPressed(sf::Keyboard::E)) camera.roll(-cameraSoeedRoll, camera);
			if (Key::isKeyPressed(sf::Keyboard::Space))  camera.translateY(+cameraSpeedMove, camera);
			if (Key::isKeyPressed(sf::Keyboard::LShift)) camera.translateY(-cameraSpeedMove, camera);
		}
		
		/* Rotate directional light */
		lightDir.setDirection(glm::rotateZ(lightDir.getDirection(), elapsedSeconds));
		
		/* Draw scene */
		scene.draw();
		
		/* Update window */
		window.display();
		
	}
	
	return 0;
}

