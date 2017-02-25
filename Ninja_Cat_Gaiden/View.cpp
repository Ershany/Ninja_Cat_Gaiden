#include "View.h"

#include "Levelstate.h"
#include "Defs.h"
#include <iostream>

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

	gsm.render();

	// Draw the player
	if (model->player->facingRight) {
		model->player->sprite.setTexture(textureManager.getTexture("Resources/Player/playerTestRight.png"));
	}
	else {
		model->player->sprite.setTexture(textureManager.getTexture("Resources/Player/playerTestLeft.png"));
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
#endif

	window.display();
}