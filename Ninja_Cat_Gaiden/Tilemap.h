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

	Tile* getTileByIndex(int row, int col);
	Tile* getTileByIndex(sf::Vector2f pos);
	bool isSolidByIndex(int row, int col);
	Tile* getTileByCoordinates(int x, int y);
	Tile* getTileByCoordinates(sf::Vector2f pos);
	bool isSolidByCoordinates(int row, int col);

	sf::Vector2f getOffset();

	sf::Vector2u mapSize;
private:
	void load(std::string levelPath);

	TextureManager &textureManager;
	sf::RenderWindow &window;
	Tile** tiles;
	sf::Vector2f mapOffset;
};

#endif