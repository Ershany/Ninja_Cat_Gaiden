#include "Controller.h"

Controller::Controller(Model *model, View *view) {
	this->model = model;
	this->view = view;

	// Initialize required instances
	inputManager = new InputManager(view->window, model->gsm);
}

Controller::~Controller() {

}

void Controller::inputs() {
	// Check for mouse input
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		model->player->leftMouseButtonPressed = true;
		model->player->mousePos = sf::Mouse::getPosition(view->window);
	}
	else {
		model->player->leftMouseButtonPressed = false;
	}

	// Update the input manager
	inputManager->update();
}