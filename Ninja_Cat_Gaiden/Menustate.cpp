#include "Menustate.h"

Menustate::Menustate(Tilemap *map, Camera *camera, TextureManager *textureManager, sf::RenderWindow *window) 
	: Gamestate(map, camera, textureManager)
{
	this->window = window;
	loadAssets();
}

Menustate::Menustate(TextureManager *textureManager) 
	: Gamestate(NULL, NULL, textureManager)
{
	loadAssets();
}

Menustate::~Menustate() {

}

void Menustate::update(const sf::Time &deltaTime) {
	sf::Mouse mouse;

	if (mouse.getPosition().x > 550 && mouse.getPosition().x < 760 && mouse.getPosition().y > 370 && mouse.getPosition().y < 475)
		play = true;
	else
		play = false;
	if (mouse.getPosition().x > 585 && mouse.getPosition().x < 725 && mouse.getPosition().y > 500 && mouse.getPosition().y < 575)
		quit = true;
	else
		quit = false;

	if (play && mouse.isButtonPressed(sf::Mouse::Button::Left))
		popOffState = true;

	if (quit && mouse.isButtonPressed(sf::Mouse::Button::Left))
		exit(1);
}

void Menustate::render() {
	window->draw(background);
	window->draw(logo);
	
	if (play)
		window->draw(playButton);
	else
		window->draw(playButtonIdel);
	if (quit)
		window->draw(quitButton);
	else
		window->draw(quitButtonIdel);

	window->draw(p);
	window->draw(q);
}

void Menustate::loadAssets() {
	//music.openFromFile("Resources/Audio/Music/menu.mp3");
	//music.setLoop(true);
	//music.play();

	impact.loadFromFile("Resources/HUD/fonts/impact.ttf");

	background.setTexture(textureManager->getTexture("Resources/Menus/menu-background.png"));
	background.setPosition(0, 0);

	logo.setTexture(textureManager->getTexture("Resources/Menus/logo.png"));
	logo.setPosition(330, 50);

	playButtonIdel.setTexture(textureManager->getTexture("Resources/Menus/button-idel.png"));
	playButtonIdel.setPosition(460, 300);
	playButtonIdel.setScale(0.7, 0.7);
	playButton.setTexture(textureManager->getTexture("Resources/Menus/button-pressed.png"));
	playButton.setPosition(460, 300);
	playButton.setScale(0.7, 0.7);

	quitButtonIdel.setTexture(textureManager->getTexture("Resources/Menus/button-idel.png"));
	quitButtonIdel.setPosition(490, 430);
	quitButtonIdel.setScale(0.5, 0.5);
	quitButton.setTexture(textureManager->getTexture("Resources/Menus/button-pressed.png"));
	quitButton.setPosition(490, 430);
	quitButton.setScale(0.5, 0.5);

	p.setFont(impact);
	p.setString("PLAY");
	p.setPosition(535, 330);

	q.setFont(impact);
	q.setString("QUIT");
	q.setPosition(535, 450);
}

void Menustate::keyPressed(int keycode) {

}

void Menustate::keyReleased(int keycode) {

}