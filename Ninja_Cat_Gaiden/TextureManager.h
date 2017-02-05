#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SFML\Graphics.hpp>

class TextureManager {
public:
	TextureManager();
	~TextureManager();

	const sf::Texture& getTexture(std::string key, sf::Color mask = sf::Color::Transparent);
private:
	std::map<std::string, sf::Texture> textures;
};

#endif