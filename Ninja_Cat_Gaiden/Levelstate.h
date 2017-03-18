#pragma once

#include "Gamestate.h"

class Levelstate : public Gamestate {
public:
	Levelstate(Tilemap *map, Camera *camera, TextureManager *textureManager, Player *player);
	~Levelstate();

	void update(const sf::Time &deltaTime) override;
	void render() override;

	void keyPressed(int keycode) override;
	void keyReleased(int keycode) override;
private:
	Player *player;

	sf::Time gameoverTime, currentGameoverTime;
};
