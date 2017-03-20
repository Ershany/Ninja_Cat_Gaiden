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

	void loadAssets();

	void keyPressed(int keycode) override;
	void keyReleased(int keycode) override;

private:
	sf::RenderWindow *window;
	Player *player;

	sf::Sprite background;
	sf::Sprite boxes[2][4];
	sf::Sprite herb, container, metal, chem;
	sf::Sprite smokeBomb, shuriken, healthPotion, camoPotion;

	sf::Sprite sBCraftIdel, sBCraft;
	sf::Sprite shCraftIdel, shCraft;
	sf::Sprite hPCraftIdel, hPCraft;
	sf::Sprite cPCraftIdel, cPCraft;

	sf::Text craft[4];
	bool hPC, cPC, sBC, shC, notEnoughMaterials, onceProtect;

	sf::Text notEnoughMat;
	sf::Clock timer;

	sf::Text inventory;
	sf::Text sB, sh, hP, cP, h, c, m, ch;
	sf::Text sBA, shA, hPA, cPA, hA, cA, mA, chA;
	sf::Font impact, cent_gothic;

	sf::Text mat[4];
	sf::Text sBM, shM, hPM, cPM;
};