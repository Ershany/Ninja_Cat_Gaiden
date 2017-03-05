#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SFML\Graphics.hpp>
#include <vector>

#include "Tilemap.h"
#include "TextureManager.h"
#include "Player.h"
#include "Camera.h"

class Projectile;
class Enemy;

class Gamestate {
public:
	Gamestate(Tilemap *map, Camera *camera, TextureManager *textureManager); // Note Gamestate can't have a GamestateManager because that is a circular include
	virtual ~Gamestate();

	virtual void update(const sf::Time &deltaTime);
	virtual void render();

	virtual void keyPressed(int keycode);
	virtual void keyReleased(int keycode);

	// Gamestate function
	void updateProjectiles(const sf::Time &deltaTime);
	void updateEnemies(const sf::Time &deltaTime);

	Tilemap* getTilemap();

	std::vector<Projectile*> projectiles;
	std::vector<Enemy*> enemies;
protected:
	Tilemap *map;
	TextureManager *textureManager;
	Camera *camera;
};

#endif