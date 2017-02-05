#include "Game.h"

Game::Game(int width, int height)
	: window(sf::VideoMode(width, height), "Ninja Cat Gaiden")
{
	window.setFramerateLimit(60);
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

}

void Game::render() {
	window.clear();



	window.display();
}