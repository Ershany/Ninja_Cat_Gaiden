#pragma once

#include "Gamestate.h"

class Menustate : public Gamestate {
public:
	Menustate(Tilemap *map, Camera *camera, TextureManager *textureManager, sf::RenderWindow *window);
	Menustate(TextureManager *textureManager);
	~Menustate();

	void update(const sf::Time &deltaTime) override;
	void render() override;

	void keyPressed(int keycode) override;
	void keyReleased(int keycode) override;
private:
	sf::RenderWindow *window;
};