#ifndef CAMERA_H
#define CAMERA_H

#include <SFML\Graphics.hpp>

#include "Updateable.h"
#include "Tilemap.h"
#include "Player.h"

class Camera : public Updateable {
public:
	Camera(Player &player, Tilemap &tilemap, sf::RenderWindow &window);
	~Camera();

	void update(sf::Time deltaTime);
	void render();
private:
	sf::RenderWindow &window;
	Tilemap &tilemap;
	Player &player;
};

#endif