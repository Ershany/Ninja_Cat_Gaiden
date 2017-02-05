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

void Tilemap::render() {
	for (int row = 0; row < mapSize.y; ++row) {
		for (int col = 0; col < mapSize.x; ++col) {
			window.draw(tiles[row][col].sprite);
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