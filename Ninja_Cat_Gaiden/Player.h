#ifndef PLAYER_H
#define PLAYER_H

#include <SFML\Graphics.hpp>

#include "Updateable.h"
#include "Renderable.h"

class Player : public Updateable, public Renderable {
public:
	Player(sf::Vector2f position, Tilemap &map);
	~Player();

	void update(sf::Time deltaTime);
	void render();
private:
	sf::Vector2f velocity;
};

#endif