#ifndef GAMESTATEMANAGER_H
#define GAMESTATEMANAGER_H

#include <SFML\Graphics.hpp>
#include <stack>

#include "Gamestate.h"

class GamestateManager {
public:
	GamestateManager();
	GamestateManager(Gamestate *gameStart);
	~GamestateManager();
	
	void update(const sf::Time &deltaTime);
	void render();
	void addGamestate(Gamestate *gamestate);
	void removeGamestate();

	void keyPressed(int keycode);
	void keyReleased(int keycode);
private:
	std::stack<Gamestate*> states;
};

#endif