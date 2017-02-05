#ifndef TILEMAP_H
#define TILEMAP_H

#include <SFML\Graphics.hpp>

#include "Updateable.h"
#include "Tile.h"

class Tilemap : public Updateable {
public:
	Tilemap();
	~Tilemap();

	void update(sf::Time deltaTime);
private:
	void load();

	Tile** tiles;
};

#endif