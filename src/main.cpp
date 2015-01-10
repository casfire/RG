#include "Engine/Engine.hpp"
#include <SFML/Window.hpp>
#include <iostream>
#include <glm/gtx/rotate_vector.hpp>

namespace E = Engine;
typedef sf::Keyboard Key;

int main() {
	
	/* Create window and OpenGL context */
	sf::Window window(sf::VideoMode(800, 600), "Engine", sf::Style::Default);
	window.setVerticalSyncEnabled(true);
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
	
	/* Enable shadows */
	scene.setShadowSize(2048, 2048);
	scene.setShadowDepthBias(0.005);
	scene.setShadowSamples(4, 4, 3.f);
	scene.setShadowProjection(-300, 300, -300, 300, -500, 1000);
	scene.enableShadows();
	
	/* Set light properties */
	lightDir.setDirection  (glm::vec3(0.5, 1, 0.5)); // Direction 
	lightDir.setColor      (glm::vec3(1, 1, 1));     // Color
	lightDir.setIntensity  (0.5f);                   // Intensity
	lightPoint.setPosition (glm::vec3(1, 3, 1));     // Position
	lightPoint.setColor    (glm::vec3(0.8, 0.8, 1)); // Color
	lightPoint.setIntensity(1.f);                    // Intensity
	lightPoint.setSpread   (0.001f);                 // Inverse spread
	scene.setAmbient(0.3);
	
	/* Load and attach skydome */
	E::Node& skydome = engine.loadModel("assets/skydome/skydome.cfrm");
	scene.attach(skydome);
	skydome.setScale(glm::vec3(2000, 2000, 2000));
	
	/* Load and attach light model */
	E::Node& lightModel = engine.loadModel("assets/light/light.cfrm");
	scene.attach(lightModel);
	
	/* Load and attach sphere */
	E::Node& sphere = engine.loadModel("assets/sphere/sphere.cfrm");
	scene.attach(sphere);
	sphere.setScale(glm::vec3(10, 10, 10));
	
	/* Move camera back */
	camera.setPosition(glm::vec3(0, 0, 2));
	
	/* Main loop */
	bool running = true, cursorLocked = false;
	sf::Clock clock;
	sf::Time elapsedLast = sf::Time::Zero;
	float fpsTime = 0, fpsFrames = 0;
	while (running) {
		
		/* Timing */
		sf::Time elapsedNow = clock.getElapsedTime();
		sf::Time elapsedFrame = elapsedNow - elapsedLast;
		elapsedLast = elapsedNow;
		float elapsedSeconds = elapsedFrame.asSeconds();
		fpsTime += elapsedSeconds;
		fpsFrames++;
		if (fpsTime > 1) {
			window.setTitle("Engine - " + std::to_string(fpsFrames / fpsTime) + " fps");
			fpsFrames = fpsTime = 0.f;
		}
		
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
			float cameraSpeedMove   = elapsedSeconds * 100;
			float cameraSpeedRotate = 0.004;
			float cameraSoeedRoll   = elapsedSeconds;
			sf::Vector2i mousePos   = sf::Mouse::getPosition(window);
			sf::Vector2i windowMid  = sf::Vector2i(window.getSize()) / 2;
			if (mousePos != windowMid) {
				glm::vec2 move = glm::vec2(windowMid.x, windowMid.y) - glm::vec2(mousePos.x, mousePos.y);
				if (Key::isKeyPressed(sf::Keyboard::F)) {
					lightDir.setDirection(glm::rotateX(lightDir.getDirection(), move.x * cameraSpeedRotate));
					lightDir.setDirection(glm::rotateZ(lightDir.getDirection(), move.y * cameraSpeedRotate));
					float ambient = glm::normalize(lightDir.getDirection()).y;
					if (ambient < 0.) ambient = 0.f;
					scene.setAmbient(0.1 + ambient * 0.3);
				} else {
					camera.rotateY(move.x * cameraSpeedRotate);
					camera.rotateX(move.y * cameraSpeedRotate, camera);
				}
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
		
		/* Set point light position*/
		if (Key::isKeyPressed(sf::Keyboard::V)) {
			lightPoint.setPosition(camera.getPosition() + camera.getRotation() * glm::vec3(0, 0, -10));
			lightModel.setPosition(lightPoint.getPosition());
		}
		
		/* Draw scene */
		scene.draw();
		
		/* Update window */
		window.display();
		
	}
	
	return 0;
}

