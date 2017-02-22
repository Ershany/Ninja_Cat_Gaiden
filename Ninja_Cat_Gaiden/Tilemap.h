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

	void update(const sf::Time &deltaTime);
	void render(const sf::Vector2f &renderPosition);

	void addOffset(sf::Vector2f &offset);
	void addOffset(int xOffset, int yOffset);
	void setOffset(sf::Vector2f &offset);
	void setOffset(int xOffset, int yOffset);

	sf::Vector2f getOffset();
private:
	void load(std::string levelPath);

	TextureManager &textureManager;
	sf::RenderWindow &window;
	Tile** tiles;
	sf::Vector2u mapSize;
	sf::Vector2f mapOffset;
};

#endif