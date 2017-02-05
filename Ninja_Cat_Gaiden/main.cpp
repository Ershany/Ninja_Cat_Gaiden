#include <SFML\Graphics.hpp>
#include "Game.h"

int main() {
	int width = 1200;
	int height = width / 16 * 9;
	Game game(width, height);
	game.launch();

	return 0;
}