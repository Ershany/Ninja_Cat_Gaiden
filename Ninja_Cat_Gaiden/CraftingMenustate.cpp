#include "CraftingMenustate.h"

CraftingMenustate::CraftingMenustate(Tilemap *map, Camera *camera, TextureManager *textureManager, Player *player)
	: Gamestate(map, camera, textureManager)
{	
	this->player = player;
}

CraftingMenustate::CraftingMenustate(TextureManager *textureManager, Player * player)
	: Gamestate(NULL, NULL, textureManager)
{
	this->player = player;
}

CraftingMenustate::~CraftingMenustate() {

}

void CraftingMenustate::update(const sf::Time &deltaTime) {

}

void CraftingMenustate::render() {

}

void CraftingMenustate::keyPressed(int keycode) {
	if (keycode == sf::Keyboard::Return) { // If player hits enter then pop off the state
		popOffState = true;
	}
}

void CraftingMenustate::keyReleased(int keycode) {

}