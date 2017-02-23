#include "InputManager.h"

InputManager::InputManager(sf::RenderWindow &window, GamestateManager &gsm)
	: window(window), gsm(gsm)
{

}

InputManager::~InputManager() {

}

void InputManager::update() {
	sf::Event event;

	while (window.pollEvent(event)) {
		switch (event.type) {
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::KeyPressed:
			gsm.keyPressed(event.key.code);
			break;
		case sf::Event::KeyReleased:
			gsm.keyReleased(event.key.code);
			break;
		}
	}
}