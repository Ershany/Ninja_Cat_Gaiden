#include "Levelstate.h"

#include <iostream>

Levelstate::Levelstate(Tilemap *map, Camera *camera, TextureManager *textureManager, Player *player) 
	: Gamestate(map, camera, textureManager)
{
	this->player = player;
}

Levelstate::~Levelstate() {

}

void Levelstate::update(const sf::Time &deltaTime) {
	player->update(deltaTime);
	Gamestate::update(deltaTime);
}

void Levelstate::render() {
	Gamestate::render();
}

void Levelstate::keyPressed(int keycode) {
	switch(keycode) {
	case sf::Keyboard::W:
	case sf::Keyboard::Up:
		player->upHeld = true;
		break;
	case sf::Keyboard::S:
	case sf::Keyboard::Down:
		player->downHeld = true;
		break;
	case sf::Keyboard::D:
	case sf::Keyboard::Right:
		player->rightHeld = true;
		break;
	case sf::Keyboard::A:
	case sf::Keyboard::Left:
		player->leftHeld = true;
		break;
	}
}

void Levelstate::keyReleased(int keycode) {
	switch (keycode) {
	case sf::Keyboard::W:
	case sf::Keyboard::Up:
		player->upHeld = false;
		break;
	case sf::Keyboard::S:
	case sf::Keyboard::Down:
		player->downHeld = false;
		break;
	case sf::Keyboard::D:
	case sf::Keyboard::Right:
		player->rightHeld = false;
		break;
	case sf::Keyboard::A:
	case sf::Keyboard::Left:
		player->leftHeld = false;
		break;
	}
}