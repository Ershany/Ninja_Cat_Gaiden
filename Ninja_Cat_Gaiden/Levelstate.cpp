#include "Levelstate.h"

#include <iostream>

#include "Enemy.h"
#include "Projectile.h"
#include "Defs.h"

Levelstate::Levelstate(Tilemap *map, Camera *camera, TextureManager *textureManager, Player *player) 
	: Gamestate(map, camera, textureManager)
{
	this->player = player;
}

Levelstate::~Levelstate() {

}

void Levelstate::update(const sf::Time &deltaTime) {
	// Check if the player is dead, and if so end the game
	if (player->isDead) {
		gameover = true;
	}

	player->update(deltaTime);

	// Check if the player is attacking the AI
	if (player->shouldMelee) {
		std::vector<Enemy*>::iterator iterator = enemies.begin();
		while (iterator != enemies.end()) {
			// Check if the unit is in range of the melee
			if (squaredLength((player->position + sf::Vector2f(player->size.x * 0.5f, player->size.y * 0.5f)) - 
				((*iterator)->position + sf::Vector2f((*iterator)->size.x * 0.5f, (*iterator)->size.y * 0.5f))) <= player->meleeRange) 
			{
				// Make sure the player is facing the correct way to hit the enemy
				float difference = player->position.x - (*iterator)->position.x;
				if ((difference > 0 && !player->facingRight) || (difference < 0 && player->facingRight)) {
					player->score += player->meleeKillScore;
					(*iterator)->shouldRemove = true;
				}
			}

			iterator++;
		}
	}

	// Check if a projectile collides with an enemy
	std::vector<Projectile*>::iterator projectileIter = projectiles.begin();
	while (projectileIter != projectiles.end()) {
		// Make sure it is a shuriken
		if ((*projectileIter)->type != Projectile::Type::Shuriken) { projectileIter++; continue; }

		std::vector<Enemy*>::iterator enemyIter = enemies.begin();
		while (enemyIter != enemies.end()) {
			if (squaredLength(((*projectileIter)->position + sf::Vector2f((*projectileIter)->size.x * 0.5f, (*projectileIter)->size.y * 0.5f)) - 
			    ((*enemyIter)->position + sf::Vector2f((*enemyIter)->size.x * 0.5f, (*enemyIter)->size.y * 0.5f))) < 36 * 36) 
			{
				player->score += player->rangeKillScore;
				(*enemyIter)->shouldRemove = true;
				(*projectileIter)->shouldRemove = true;
			}

			enemyIter++;
		}

		projectileIter++;
	}

	// Check if the player is using a camo potion and act accordingly
	// Also check for if they are alert of the player
	std::vector<Enemy*>::iterator iterator = enemies.begin();
	while (iterator != enemies.end()) {
		if (player->camoPotion) {
			(*iterator)->sightRange = (*iterator)->reducedSightRange;
		}
		else {
			(*iterator)->sightRange = (*iterator)->maxSightRange;
		}

		if ((*iterator)->alertOfPlayer) {
			gameover = true;
		}

		iterator++;
	}

	// Set the player's gameFinished status
	if (gameover) {
		player->gameFinished = true;
	}

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
	case sf::Keyboard::F:
		player->fHeld = true;
		break;
	case sf::Keyboard::Q:
		player->inventory.changeSelectedItem(-1);
		break;
	case sf::Keyboard::E:
		player->inventory.changeSelectedItem(1);
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
	case sf::Keyboard::F:
		player->fHeld = false;
		break;
	}
}