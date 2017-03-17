#include "Tilemap.h"

#include <iostream>

Tilemap::Tilemap(std::string levelPath, TextureManager &textureManager, sf::RenderWindow &window)
	: window(window), textureManager(textureManager)
{
	load(levelPath);
}

Tilemap::~Tilemap() {

}

void Tilemap::update(const sf::Time &deltaTime) {
	// Set the tiles positions accordingly
	for (int row = 0; row < mapSize.y; ++row) {
		for (int col = 0; col < mapSize.x; ++col) {
			tiles[row][col].update(deltaTime);
		}
	}
}

void Tilemap::render(const sf::Vector2f &renderPosition) {
	// Calculate which tiles to render in the 2d array (bounds)
	int startRow = ((int)renderPosition.y >> 5) - 10;
	if (startRow < 0) startRow = 0;
	int endRow = (startRow + (window.getSize().y >> 5)) + 20;
	if (endRow > mapSize.y) endRow = mapSize.y;

	int startCol = ((int)renderPosition.x >> 5) - 20;
	if (startCol < 0) startCol = 0;
	int endCol = (startCol + (window.getSize().x >> 5)) + 40;
	if (endCol > mapSize.x) endCol = mapSize.x;

	// Render the tiles using the calculated bounds
	for (int row = startRow; row < endRow; ++row) {
		for (int col = startCol; col < endCol; ++col) {
			// If the tile is transparent, don't draw it
			if (tiles[row][col].getTransparent()) continue;

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
			
			// Set the default transparency to false
			tiles[row][col].setTransparent(false);
			if (color.r == 0 && color.g == 255 && color.b == 0) {
				tiles[row][col].sprite.setTexture(textureManager.getTexture("Resources/Tiles/grass.png"));
			}
			else if (color.r == 86 && color.g == 86 && color.b == 86) {
				tiles[row][col].sprite.setTexture(textureManager.getTexture("Resources/Tiles/stone.png"));
				tiles[row][col].setSeeAble(false);
				tiles[row][col].setSolid(true);
			}
			else if (color.r == 255 && color.g == 153 && color.b == 0) {
				tiles[row][col].sprite.setTexture(textureManager.getTexture("Resources/Tiles/spikes.png"));
				tiles[row][col].setDamaging(true);
				tiles[row][col].setDamageAmount(4);
			}
			else if (color.r == 0 && color.g == 0 && color.b == 0) {
				tiles[row][col].setTransparent(true);
			}
			else if (color.r == 91 && color.g == 36 && color.b == 0) {
				tiles[row][col].sprite.setTexture(textureManager.getTexture("Resources/Tiles/woodenBackground.png"));
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

Tile* Tilemap::getTileByIndex(int row, int col) {
	if (row < 0 || row >= mapSize.y || col < 0 || col >= mapSize.x) {
#if DEBUG
		std::cout << "Row/Column Index Is Out Of Bounds: Can't Access" << std::endl;
#endif
		return NULL;
	}
	return &(tiles[row][col]);
}

Tile* Tilemap::getTileByIndex(sf::Vector2f pos) {
	return getTileByIndex((int)pos.x, (int)pos.y);
}

// Return true if the tile is out of the map
bool Tilemap::isSolidByIndex(int row, int col) {
	Tile* temp = getTileByIndex(row, col);
	if (temp != NULL) {
		return temp->getSolid();
	}
	return true;
}

Tile* Tilemap::getTileByCoordinates(int x, int y) {
	if (y < 0 || y >= mapSize.y << 5 || x < 0 || x >= mapSize.x << 5) {
#if DEBUG
		std::cout << "Row/Column Index Is Out Of Bounds: Can't Access" << std::endl;
#endif
		return NULL;
	}
	return &(tiles[y >> 5][x >> 5]);
}

Tile* Tilemap::getTileByCoordinates(sf::Vector2f pos) {
	return getTileByCoordinates((int)pos.x, (int)pos.y);
}

// Return true if the tile is out of the map
bool Tilemap::isSolidByCoordinates(int row, int col) {
	Tile* temp = getTileByCoordinates(row, col);
	if (temp != NULL) {
		return temp->getSolid();
	}
	return true;
}