#ifndef TILEMAP_H
#define TILEMAP_H

#include <SFML\Graphics.hpp>

#include "Updateable.h"
#include "Tile.h"
#include "TextureManager.h"

class Tilemap : public Updateable {
public:
	Tilemap(std::string levelPath, TextureManager &textureManager, sf::RenderWindow &window);
	~Tilemap();

	void update(sf::Time deltaTime);
	void render();
private:
	void load(std::string levelPath);

	TextureManager &textureManager;
	sf::RenderWindow &window;
	Tile** tiles;
	sf::Vector2u mapSize;
};

#endif