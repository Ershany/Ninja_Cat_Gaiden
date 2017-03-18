#include "View.h"

#include "Levelstate.h"
#include "Menustate.h"
#include "Defs.h"
#include <iostream>
#include "Projectile.h"
#include "Enemy.h"
#include "InteractableObject.h"

View::View(Model *model, GamestateManager &gsm)
	: gsm(gsm)
{
	this->model = model;
	
	// Setup the window
	int width = 1200;
	int height = width / 16 * 9;
	window.create(sf::VideoMode(width, height), "Ninja Cat Gaiden");
	window.setFramerateLimit(60);

	hud = new HUD(this->model, &window, &textureManager);

	// Setup the sprites
	model->player->sprite.setTexture(textureManager.getTexture("Resources/Player/playerTestRight.png"));

	// Setup the first level by making the gamestate manager for the model
	Tilemap *tilemap = new Tilemap("Resources/Levels/level1.png", textureManager, window);
	Camera *camera = new Camera(*(this->model->player), *tilemap, window);
	this->gsm.addGamestate(new Levelstate(tilemap, camera, &textureManager, model->player));
	model->initLevel1();

	this->gsm.addGamestate(new Menustate(NULL, NULL, &textureManager));
	this->gsm.getCurrentState()->inMenu = true;

	model->setGSM(gsm); // Set the models gsm to the one we just initialized
}

View::~View() {

}

void View::render() {
	window.clear(sf::Color(0, 0, 50));

	// Render the map
	gsm.render();

	// Render projectiles
	std::vector<Projectile*>::iterator iterator = gsm.getCurrentState()->projectiles.begin();
	while (iterator != gsm.getCurrentState()->projectiles.end()) {
		// Set the projectiles sprite position
		(*iterator)->sprite.setPosition((*iterator)->position - gsm.getCurrentState()->getTilemap()->getOffset());

		// Set the projectiles sprite texture
		if ((*iterator)->type == Projectile::Type::Shuriken) {
			(*iterator)->sprite.setTexture(textureManager.getTexture("Resources/Player/shuriken.png"));
		}
		else if ((*iterator)->type == Projectile::Type::Smokebomb) {
			(*iterator)->sprite.setTexture(textureManager.getTexture("Resources/Player/smokeBomb.png"));
		}

		// Finally draw it and iterate to the next
		window.draw((*iterator)->sprite);
		iterator++;
	}

	// Render the enemies
	std::vector<Enemy*>::iterator enemyIterator = gsm.getCurrentState()->enemies.begin();
	while (enemyIterator != gsm.getCurrentState()->enemies.end()) {
		// Set the enemies sprite position
		(*enemyIterator)->sprite.setPosition((*enemyIterator)->position - gsm.getCurrentState()->getTilemap()->getOffset());

		// Set the enemies sprite texture
		if ((*enemyIterator)->type == Enemy::Samurai) {
			if ((*enemyIterator)->facingRight) {
				(*enemyIterator)->sprite.setTexture(textureManager.getTexture("Resources/Enemy/Samurai/samuraiRatRight.png"));
			}
			else {
				(*enemyIterator)->sprite.setTexture(textureManager.getTexture("Resources/Enemy/Samurai/samuraiRatLeft.png"));
			}
		}

		// Render the sight lines
		if ((*enemyIterator)->alertOfPlayer) {
			sf::Vertex line[2];
			line[0].position = (model->player->position + sf::Vector2f(model->player->size.x * 0.5f, model->player->size.y * 0.5f)) - gsm.getCurrentState()->getTilemap()->getOffset();
			line[0].color = sf::Color::Red;
			line[1].position = ((*enemyIterator)->position + sf::Vector2f((*enemyIterator)->size.x * 0.5f, (*enemyIterator)->size.y * 0.2f)) - gsm.getCurrentState()->getTilemap()->getOffset();
			line[1].color = sf::Color::Red;
			window.draw(line, 2, sf::Lines);
		}

		window.draw((*enemyIterator)->sprite);
		enemyIterator++;
	}

	// Draw the player
	if (!gsm.getCurrentState()->inMenu) {
		if (model->player->isDead) {
			model->player->deadSprite.setTexture(textureManager.getTexture("Resources/Player/playerDead.png"));
			model->player->deadSprite.setPosition(model->player->sprite.getPosition() + sf::Vector2f(0.0f, 32.0f));
			window.draw(model->player->deadSprite);
		}
		else {
			if (model->player->facingRight) {
				if (model->player->leftMouseButtonPressed && model->player->inventory.currentSelectedItem == 0) {
					model->player->sprite.setTexture(textureManager.getTexture("Resources/Player/playerAttackRight.png"));
				}
				else {
					model->player->sprite.setTexture(textureManager.getTexture("Resources/Player/playerTestRight.png"));
				}
			}
			else {
				if (model->player->leftMouseButtonPressed && model->player->inventory.currentSelectedItem == 0) {
					model->player->sprite.setTexture(textureManager.getTexture("Resources/Player/playerAttackLeft.png"));
				}
				else {
					model->player->sprite.setTexture(textureManager.getTexture("Resources/Player/playerTestLeft.png"));
				}
			}
			window.draw(model->player->sprite);
		}
	}
	

	// Render the objects
	std::vector<InteractableObject*>::iterator objectIterator = gsm.getCurrentState()->objects.begin();
	while (objectIterator != gsm.getCurrentState()->objects.end()) {
		// Set the objects position
		(*objectIterator)->sprite.setPosition((*objectIterator)->position - gsm.getCurrentState()->getTilemap()->getOffset());

		// Set the objects sprite texture
		if ((*objectIterator)->type == InteractableObject::Chandelier) {
			if ((*objectIterator)->activated) {
				(*objectIterator)->sprite.setTexture(textureManager.getTexture("Resources/Tiles/brokenChandelier.png"));
			}
			else {
				(*objectIterator)->sprite.setTexture(textureManager.getTexture("Resources/Tiles/chandelier.png"));
			}
		}
		else if ((*objectIterator)->type == InteractableObject::Smoke) {
			(*objectIterator)->sprite.setTexture(textureManager.getTexture("Resources/Tiles/smoke.png"));
		}
		else if ((*objectIterator)->type == InteractableObject::Hideable) {
			(*objectIterator)->sprite.setTexture(textureManager.getTexture("Resources/Tiles/shrub.png"));
		}
		else if ((*objectIterator)->type == InteractableObject::ScrapMetal) {
			(*objectIterator)->sprite.setTexture(textureManager.getTexture("Resources/Collectibles/scrapMetal.png"));
		}
		else if ((*objectIterator)->type == InteractableObject::Container) {
			(*objectIterator)->sprite.setTexture(textureManager.getTexture("Resources/Collectibles/container.png"));
		}
		else if ((*objectIterator)->type == InteractableObject::Chemical) {
			(*objectIterator)->sprite.setTexture(textureManager.getTexture("Resources/Collectibles/chemical.png"));
		}
		else if ((*objectIterator)->type == InteractableObject::Herb) {
			(*objectIterator)->sprite.setTexture(textureManager.getTexture("Resources/Collectibles/herb.png"));
		}
		else if ((*objectIterator)->type == InteractableObject::EnterPortal) {
			(*objectIterator)->sprite.setTexture(textureManager.getTexture("Resources/Tiles/enterPortal.png"));
		}
		else if ((*objectIterator)->type == InteractableObject::ExitPortal) {
			(*objectIterator)->sprite.setTexture(textureManager.getTexture("Resources/Tiles/exitPortal.png"));
		}

		window.draw((*objectIterator)->sprite);
		objectIterator++;
	}

	if (!gsm.getCurrentState()->inMenu) {
		hud->draw();
	}
	
#if DEBUG
	// Draw Player Collision Points
	for (int i = 0; i < sizeof(model->player->collisionPoints) / sizeof(sf::Vector2f); ++i) {
		sf::RectangleShape shape;
		shape.setPosition(sf::Vector2f(model->player->collisionPoints[i].x, model->player->collisionPoints[i].y));
		shape.setSize(sf::Vector2f(2, 2));
		shape.setFillColor(sf::Color::Red);
		// Transform and draw
		shape.move(-gsm.getCurrentState()->getTilemap()->getOffset());
		window.draw(shape);
		shape.move(gsm.getCurrentState()->getTilemap()->getOffset());
	}

	// Draw Projectile Collision Points
	iterator = gsm.getCurrentState()->projectiles.begin();
	while (iterator != gsm.getCurrentState()->projectiles.end()) {
		for (int i = 0; i < 4; ++i) {
			sf::RectangleShape shape;
			shape.setPosition(sf::Vector2f((*iterator)->collisionPoints[i]));
			shape.setSize(sf::Vector2f(2, 2));
			shape.setFillColor(sf::Color::Red);
			// Transform and draw
			shape.move(-gsm.getCurrentState()->getTilemap()->getOffset());
			window.draw(shape);
			shape.move(gsm.getCurrentState()->getTilemap()->getOffset());
		}
		iterator++;
	}
#endif

	window.display();

	checkForTransition();
}

void View::checkForTransition() {
	if (model->player->transitioningToNextLevel) {
		model->player->transitioningToNextLevel = false;
		if (model->player->currentLevel == 1) {
			// Tilemap, Camera, new state
			delete gsm.getCurrentState();
			Tilemap *tilemap = new Tilemap("Resources/Levels/level2.png", textureManager, window);
			Camera *camera = new Camera(*(this->model->player), *tilemap, window);
			model->player->position = sf::Vector2f(5 << 5, 307 << 5);
			model->player->currentLevel = 2;
			this->gsm.removeGamestate();
			this->gsm.addGamestate(new Levelstate(tilemap, camera, &textureManager, model->player));
			
			model->initLevel2();
		}
		else if (model->player->currentLevel == 2) {
			// Tilemap, Camera, new state
			delete gsm.getCurrentState();
			Tilemap *tilemap = new Tilemap("Resources/Levels/level3.png", textureManager, window);
			Camera *camera = new Camera(*(this->model->player), *tilemap, window);
			model->player->position = sf::Vector2f(3 << 5, 6 << 5);
			model->player->currentLevel = 3;
			this->gsm.removeGamestate();
			this->gsm.addGamestate(new Levelstate(tilemap, camera, &textureManager, model->player));

			model->initLevel3();
		}
		else {
			// The player beat the game
			model->player->gameFinished = true;
		}
	}
}