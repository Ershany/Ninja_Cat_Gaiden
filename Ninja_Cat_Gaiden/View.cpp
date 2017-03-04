#include "View.h"

#include "Levelstate.h"
#include "Defs.h"
#include <iostream>
#include "Projectile.h"

View::View(Model *model, GamestateManager &gsm)
	: gsm(gsm)
{
	this->model = model;

	// Setup the window
	int width = 1200;
	int height = width / 16 * 9;
	window.create(sf::VideoMode(width, height), "Ninja Cat Gaiden");
	window.setFramerateLimit(60);

	// Setup the sprites
	model->player->sprite.setTexture(textureManager.getTexture("Resources/Player/playerTestRight.png"));

	// Setup the first level by making the gamestate manager for the model
	Tilemap *tilemap = new Tilemap("Resources/Levels/test.png", textureManager, window);
	Camera *camera = new Camera(*(this->model->player), *tilemap, window);
	this->gsm.addGamestate(new Levelstate(tilemap, camera, &textureManager, model->player));
	// Set the models gsm to the one we just initialized
	model->setGSM(gsm);
}

View::~View() {

}

void View::render() {
	window.clear();

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

		// Finally draw it and iterate to the next
		window.draw((*iterator)->sprite);
		iterator++;
	}

	// Draw the player
	if (model->player->isDead) {
		model->player->sprite.setTexture(textureManager.getTexture("Resources/Player/playerDead.png"));
	}
	else {
		if (model->player->facingRight) {
			model->player->sprite.setTexture(textureManager.getTexture("Resources/Player/playerTestRight.png"));
		}
		else {
			model->player->sprite.setTexture(textureManager.getTexture("Resources/Player/playerTestLeft.png"));
		}
	}

	window.draw(model->player->sprite);

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
}