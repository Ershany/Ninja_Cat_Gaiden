#ifndef UPDATEABLE_H
#define UPDATEABLE_H

#include <SFML\Graphics.hpp>

class Updateable {
public:
	virtual void update(const sf::Time &deltaTime) = 0;

	sf::Vector2f position;
};

#endif