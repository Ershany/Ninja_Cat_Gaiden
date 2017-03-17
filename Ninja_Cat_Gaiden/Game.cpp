#include "Game.h"

Game::Game() {
	// Initialize the model, view, and controller
	model = new Model();
	view = new View(model, model->gsm);
	controller = new Controller(model, view);
	model->initLevel1();
}

Game::~Game() {

}

void Game::launch() {
	sf::Time deltaTime;

	while (view->window.isOpen()) {
		deltaTime = clock.restart();

		controller->inputs();
		model->update(deltaTime);
		view->render();
	}
}