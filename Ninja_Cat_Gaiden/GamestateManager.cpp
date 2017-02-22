#include "GamestateManager.h"

GamestateManager::GamestateManager() {

}

GamestateManager::GamestateManager(Gamestate *gameStart) {
	states.push(gameStart);
}

GamestateManager::~GamestateManager() {

}

void GamestateManager::update(const sf::Time &deltaTime) {
	if (states.empty()) return;
	states.top()->update(deltaTime);
}

void GamestateManager::render() {
	if (states.empty()) return;
	states.top()->render();
}

void GamestateManager::addGamestate(Gamestate *gamestate) {
	states.push(gamestate);
}

void GamestateManager::removeGamestate() {
	if (states.empty()) return;
	states.pop();
}

void GamestateManager::keyPressed(int keycode) {

}

void GamestateManager::keyReleased(int keycode) {

}