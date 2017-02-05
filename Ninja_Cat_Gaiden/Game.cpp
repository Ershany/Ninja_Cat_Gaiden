#include "Game.h"

Game::Game(int width, int height)
	: window(sf::VideoMode(width, height), "Ninja Cat Gaiden")
{
	window.setFramerateLimit(60);

	// Temp Testing
	tilemap = new Tilemap("Resources/Levels/test.png", textureManager, window);
}

Game::~Game() {

}

void Game::launch() {
	sf::Time deltaTime;

	while (window.isOpen()) {
		deltaTime = clock.restart();

		inputs();
		update(deltaTime);
		render();
	}
}

void Game::inputs() {
	sf::Event event;

	while (window.pollEvent(event)) {
		switch (event.type) {
		case sf::Event::Closed:
			window.close();
			break;
		}
	}
}

void Game::update(sf::Time &deltaTime) {
	tilemap->update(deltaTime);
}

void Game::render() {
	window.clear();

	tilemap->render();
	
	window.display();
}