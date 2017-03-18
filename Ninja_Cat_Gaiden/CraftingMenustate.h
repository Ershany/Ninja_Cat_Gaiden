#pragma once

#include "Gamestate.h"
#include "Player.h"

class CraftingMenustate : public Gamestate {
public:
	CraftingMenustate(Tilemap *map, Camera *camera, TextureManager *textureManager, Player *player, sf::RenderWindow *window);
	CraftingMenustate(TextureManager *textureManager, Player * player);
	~CraftingMenustate();

	void update(const sf::Time &deltaTime) override;
	void render() override;

	void keyPressed(int keycode) override;
	void keyReleased(int keycode) override;
private:
	sf::RenderWindow *window;
	Player *player;
};