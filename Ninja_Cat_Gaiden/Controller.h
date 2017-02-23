#pragma once

#include "Model.h"
#include "View.h"
#include "InputManager.h"

class Controller {
public:
	Controller(Model *model, View *view);
	~Controller();

	void inputs();
	

	Model *model;
	View *view;

	InputManager *inputManager;
};