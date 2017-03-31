#include "GamestateManager.h"

#include <iostream>

GamestateManager::GamestateManager() {
	
}

GamestateManager::GamestateManager(Gamestate *gameStart) {
	states.push(gameStart);
}

GamestateManager::~GamestateManager() {

}

void GamestateManager::update(const sf::Time &deltaTime) {
	if (states.empty()) {
		std::cout << "GamestateManager Stack is Empty: Can't Update" << std::endl;
		return;
	}
	states.top()->update(deltaTime);
}

void GamestateManager::render() {
	if (states.empty()) {
		std::cout << "GamestateManager Stack is Empty: Can't Render" << std::endl;
		return;
	}
	states.top()->render();
}

void GamestateManager::addGamestate(Gamestate *gamestate) {
	states.push(gamestate);
}

void GamestateManager::removeGamestate() {
	if (states.empty()) {
		std::cout << "GamestateManager Stack is Empty: Can't Remove State" << std::endl;
		return;
	}
	states.pop();
}

void GamestateManager::keyPressed(int keycode) {
	if (states.empty()) {
		std::cout << "GamestateManager Stack is Empty: Can't Activate A Keypress" << std::endl;
		return;
	}
	states.top()->keyPressed(keycode);
}

void GamestateManager::keyReleased(int keycode) {
	if (states.empty()) {
		std::cout << "GamestateManager Stack is Empty: Can't Activate A Keyrelease" << std::endl;
		return;
	}
	states.top()->keyReleased(keycode);
}

Gamestate* GamestateManager::getCurrentState() {
	if (states.empty()) {
		std::cout << "GamestateManager Stack is Empty: Can't Return Top" << std::endl;
		return NULL;
	}
	return states.top();
}