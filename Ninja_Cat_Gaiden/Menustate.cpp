#include "Menustate.h"

Menustate::Menustate(Tilemap *map, Camera *camera, TextureManager *textureManager, sf::RenderWindow *window) 
	: Gamestate(map, camera, textureManager)
{
	this->window = window;
}

Menustate::Menustate(TextureManager *textureManager) 
	: Gamestate(NULL, NULL, textureManager)
{

}

Menustate::~Menustate() {

}

void Menustate::update(const sf::Time &deltaTime) {

}

void Menustate::render() {
	
}

void Menustate::keyPressed(int keycode) {
	if (keycode == sf::Keyboard::Return) { // If player hits enter then pop off the state
		popOffState = true;
	}
}

void Menustate::keyReleased(int keycode) {

}