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
	// Update the input manager
	inputManager->update();
}