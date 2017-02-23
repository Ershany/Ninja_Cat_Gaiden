#include "View.h"

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
	model->player->sprite.setTexture(textureManager.getTexture("Resources/Player/playerTest.png"));

	// Setup the first  by adding it to the gamestate
	Tilemap *tilemap = new Tilemap("Resources/Levels/test.png", textureManager, window);
	Camera *camera = new Camera(*(this->model->player), *tilemap, window);
	this->gsm.addGamestate(new Gamestate(tilemap, model->player, camera, &textureManager));
	// Set the models gsm to the one we just initialized
	model->setGSM(gsm);
}

View::~View() {

}

void View::render() {
	window.clear();

	gsm.render();
	window.draw(model->player->sprite);

	window.display();
}