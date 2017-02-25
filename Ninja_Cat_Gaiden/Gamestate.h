#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SFML\Graphics.hpp>

#include "Tilemap.h"
#include "TextureManager.h"
#include "Player.h"
#include "Camera.h"

class Gamestate {
public:
	Gamestate(Tilemap *map, Camera *camera, TextureManager *textureManager); // Note Gamestate can't have a GamestateManager because that is a circular include
	virtual ~Gamestate();

	virtual void update(const sf::Time &deltaTime);
	virtual void render();

	virtual void keyPressed(int keycode);
	virtual void keyReleased(int keycode);

	Tilemap* getTilemap();
protected:
	Tilemap *map;
	TextureManager *textureManager;
	Camera *camera;
};

#endif