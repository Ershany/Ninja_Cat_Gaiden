#ifndef GAME_H
#define GAME_H

#include <SFML\Graphics.hpp>

class Game {
public:
	Game(int width, int height);
	~Game();

	void launch();
	void inputs();
	void update(sf::Time &deltaTime);
	void render();
private:
	sf::RenderWindow window;
	sf::Clock clock;
};

#endif