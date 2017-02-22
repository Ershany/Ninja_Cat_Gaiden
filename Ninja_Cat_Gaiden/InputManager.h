#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <SFML\Graphics.hpp>

#include "GamestateManager.h"

class InputManager {
public:
	InputManager(sf::RenderWindow &window, GamestateManager &gsm);
	~InputManager();

	void update(const sf::Time &deltaTime);
private:
	sf::RenderWindow &window;
	GamestateManager &gsm;
};

#endif