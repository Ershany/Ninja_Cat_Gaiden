#pragma once

#include "Gamestate.h"

class Menustate : public Gamestate {
public:
	Menustate(Tilemap *map, Camera *camera, TextureManager *textureManager, sf::RenderWindow *window);
	Menustate(TextureManager *textureManager);
	~Menustate();

	void update(const sf::Time &deltaTime) override;
	void render() override;

	void loadAssets();

	void keyPressed(int keycode) override;
	void keyReleased(int keycode) override;
private:
	sf::RenderWindow *window;

	sf::Sprite background;
	sf::Sprite logo;
	sf::Sprite playButtonIdel;
	sf::Sprite playButton;
	sf::Sprite quitButtonIdel;
	sf::Sprite quitButton;
	bool play, quit;
	sf::Text p, q;
	sf::Font impact;

	//sf::Music music;
};