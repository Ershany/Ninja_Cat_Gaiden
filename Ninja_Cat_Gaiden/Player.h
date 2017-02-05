#ifndef PLAYER_H
#define PLAYER_H

#include <SFML\Graphics.hpp>

#include "Updateable.h"
#include "Renderable.h"
#include "Tilemap.h"

class Player : public Updateable, public Renderable {
public:
	Player(sf::Vector2f &position, Tilemap &map);
	~Player();

	void update(sf::Time deltaTime);

	sf::Vector2u getSize();
private:
	sf::Vector2f velocity;
	sf::Vector2u size;
	Tilemap &tilemap;
};

#endif