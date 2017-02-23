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
	// Poll Events
	sf::Event event;
	while (view->window.pollEvent(event)) {
		switch (event.type) {
		case sf::Event::Closed:
			view->window.close();
			break;
		}
	}
}