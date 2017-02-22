#include "Game.h"

Game::Game(int width, int height)
	: window(sf::VideoMode(width, height), "Ninja Cat Gaiden")
{
	window.setFramerateLimit(60);

	// Initialize the opening gamestate
	Tilemap *tilemap = new Tilemap("Resources/Levels/test.png", textureManager, window);
	player = new Player(sf::Vector2f(0.0f, 0.0f), *tilemap);
	Camera *camera = new Camera(*player, *tilemap, window);
	this->gsm.addGamestate(new Gamestate(tilemap, player, camera, &textureManager));

	player->sprite.setTexture(textureManager.getTexture("Resources/Player/playerTest.png"));

	// Initialize required instances
	inputManager = new InputManager(window, gsm);
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
	gsm.update(deltaTime);
}

void Game::render() {
	window.clear();
	
	gsm.render();
	window.draw(player->sprite);
	
	window.display();
}