#ifndef PLAYER_H
#define PLAYER_H

#include <SFML\Graphics.hpp>

#include "Updateable.h"
#include "Renderable.h"

// Forward declaration to get around the circular reference
class GamestateManager;

class Player : public Updateable, public Renderable {
public:
	Player(sf::Vector2f &position, GamestateManager &gsm);
	~Player();

	void update(const sf::Time &deltaTime);

	sf::Vector2u getSize();
private:
	sf::Vector2f velocity;
	sf::Vector2u size;
	GamestateManager &gsm;
};

#endif