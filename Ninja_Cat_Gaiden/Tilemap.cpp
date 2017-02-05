#include "Tilemap.h"

#include <iostream>

Tilemap::Tilemap(std::string levelPath, TextureManager &textureManager, sf::RenderWindow &window)
	: window(window), textureManager(textureManager)
{
	load(levelPath);
}

Tilemap::~Tilemap() {

}

void Tilemap::update(sf::Time deltaTime) {
	// Set the tiles positions accordingly
	for (int row = 0; row < mapSize.y; ++row) {
		for (int col = 0; col < mapSize.x; ++col) {
			tiles[row][col].update(deltaTime);
		}
	}
}

void Tilemap::render(sf::Vector2f renderPosition) {
	// Calculate which tiles to render in the 2d array (bounds)
	int startRow = ((int)renderPosition.y >> 5) - 2;
	if (startRow < 0) startRow = 0;
	int endRow = (startRow + (window.getSize().y >> 5)) + 4;
	if (endRow > mapSize.y) endRow = mapSize.y;

	int startCol = ((int)renderPosition.x >> 5) - 2;
	if (startCol < 0) startCol = 0;
	int endCol = (startCol + (window.getSize().x >> 5)) + 4;
	if (endCol > mapSize.x) endCol = mapSize.x;

	// Render the tiles using the calculated bounds
	for (int row = startRow; row < endRow; ++row) {
		for (int col = startCol; col < endCol; ++col) {
			// Transform the tiles with offset
			tiles[row][col].sprite.move(-mapOffset);
			window.draw(tiles[row][col].sprite);
			tiles[row][col].sprite.move(mapOffset);
		}
	}
}

void Tilemap::load(std::string levelPath) {
	sf::Image image;
	image.loadFromFile(levelPath);

	sf::Vector2u imageSize = image.getSize();
	mapSize = imageSize;

	// Initialize the tiles
	tiles = new Tile*[imageSize.y];
	for (int row = 0; row < imageSize.y; ++row) {
		tiles[row] = new Tile[imageSize.x];
		for (int col = 0; col < imageSize.x; ++col) {
			sf::Color color = image.getPixel(col, row);
			
			if (color.r == 0 && color.g == 255 && color.b == 0) {
				tiles[row][col].sprite.setTexture(textureManager.getTexture("Resources/Tiles/grass.png"));
			}
			else if (color.r == 86 && color.g == 86 && color.b == 86) {
				tiles[row][col].sprite.setTexture(textureManager.getTexture("Resources/Tiles/stone.png"));
			}
			else {
				
			}

			tiles[row][col].setPosition(sf::Vector2f(col << 5, row << 5));
		}
	}
}

void Tilemap::addOffset(sf::Vector2f &offset) {
	this->mapOffset += offset;
}

void Tilemap::addOffset(int xOffset, int yOffset) {
	this->mapOffset.x += xOffset;
	this->mapOffset.y += yOffset;
}

void Tilemap::setOffset(sf::Vector2f &offset) {
	this->mapOffset = offset;
}

void Tilemap::setOffset(int xOffset, int yOffset) {
	this->mapOffset.x = xOffset;
	this->mapOffset.y = yOffset;
}

sf::Vector2f Tilemap::getOffset() {
	return mapOffset;
}