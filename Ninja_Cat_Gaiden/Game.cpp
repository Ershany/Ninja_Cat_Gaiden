#include "Game.h"

Game::Game(int width, int height)
	: window(sf::VideoMode(width, height), "Ninja Cat Gaiden")
{
	window.setFramerateLimit(60);

	// Temp Testing
	tilemap = new Tilemap("Resources/Levels/test.png", textureManager, window);
	player = new Player(sf::Vector2f(0.0f, 0.0f), *tilemap);
	player->sprite.setTexture(textureManager.getTexture("Resources/Player/playerTest.png"));
	camera = new Camera(*player, *tilemap, window);
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
	player->update(deltaTime);
	camera->update(deltaTime);
}

void Game::render() {
	window.clear();

	camera->render();
	window.draw(player->sprite);
	
	window.display();
}