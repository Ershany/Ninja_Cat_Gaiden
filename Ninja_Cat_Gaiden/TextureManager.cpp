#include <iostream>

#include "TextureManager.h"

TextureManager::TextureManager() {

}

TextureManager::~TextureManager() {

}

const sf::Texture& TextureManager::getTexture(std::string key, sf::Color mask) {
	// If the texture isn't loaded, then load it
	if (this->textures.count(key) == 0) {
		sf::Image image;
		image.loadFromFile(key);

		std::cout << key << " loaded from file" << std::endl;

		if (mask != sf::Color::Transparent) {
			image.createMaskFromColor(mask);
		}

		// Add the pair to the map and load the image for the texture
		this->textures.insert(std::pair<std::string, sf::Texture>(key, sf::Texture()));
		this->textures[key].loadFromImage(image);
		this->textures[key].setSmooth(true);
	}

	return this->textures[key];
}