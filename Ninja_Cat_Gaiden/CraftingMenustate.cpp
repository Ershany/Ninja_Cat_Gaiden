#include "CraftingMenustate.h"

CraftingMenustate::CraftingMenustate(Tilemap *map, Camera *camera, TextureManager *textureManager, Player *player, sf::RenderWindow *window)
	: Gamestate(map, camera, textureManager)
{	
	this->player = player;
	this->window = window;
	loadAssets();

	hPC = cPC = shC = sBC = false;
}

CraftingMenustate::CraftingMenustate(TextureManager *textureManager, Player * player)
	: Gamestate(NULL, NULL, textureManager)
{
	this->player = player;
	loadAssets();
}

CraftingMenustate::~CraftingMenustate() {

}

void CraftingMenustate::update(const sf::Time &deltaTime) {
	if (player->inventory.numSmokebombs == 0)
		sBA.setFillColor(sf::Color::Red);
	else
		sBA.setFillColor(sf::Color::Green);
	if (player->inventory.numShurikens == 0)
		shA.setFillColor(sf::Color::Red);
	else
		shA.setFillColor(sf::Color::Green);
	if (player->inventory.numHealthPotions == 0)
		hPA.setFillColor(sf::Color::Red);
	else
		hPA.setFillColor(sf::Color::Green);
	if (player->inventory.numCamoPotions == 0)
		cPA.setFillColor(sf::Color::Red);
	else
		cPA.setFillColor(sf::Color::Green);
	if (player->inventory.numHerb == 0)
		hA.setFillColor(sf::Color::Red);
	else
		hA.setFillColor(sf::Color::Green);
	if (player->inventory.numChemical == 0)
		chA.setFillColor(sf::Color::Red);
	else
		chA.setFillColor(sf::Color::Green);
	if (player->inventory.numScrapMetal == 0)
		mA.setFillColor(sf::Color::Red);
	else
		mA.setFillColor(sf::Color::Green);
	if (player->inventory.numContainer == 0)
		cA.setFillColor(sf::Color::Red);
	else
		cA.setFillColor(sf::Color::Green);

	sBA.setString(std::to_string(player->inventory.numSmokebombs));
	shA.setString(std::to_string(player->inventory.numShurikens));
	hPA.setString(std::to_string(player->inventory.numHealthPotions));
	cPA.setString(std::to_string(player->inventory.numCamoPotions));
	cA.setString(std::to_string(player->inventory.numContainer));
	chA.setString(std::to_string(player->inventory.numChemical));
	mA.setString(std::to_string(player->inventory.numScrapMetal));
	hA.setString(std::to_string(player->inventory.numHerb));

	sf::Mouse mouse;

	if (mouse.getPosition(*window).x > 203 && mouse.getPosition(*window).x < 308 && mouse.getPosition(*window).y > 500 && mouse.getPosition(*window).y < 553)
		sBC = true;
	else
		sBC = false;

	if (mouse.getPosition(*window).x > 403 && mouse.getPosition(*window).x < 508 && mouse.getPosition(*window).y > 500 && mouse.getPosition(*window).y < 553)
		shC = true;
	else
		shC = false;

	if (mouse.getPosition(*window).x > 603 && mouse.getPosition(*window).x < 708 && mouse.getPosition(*window).y > 500 && mouse.getPosition(*window).y < 553)
		hPC = true;
	else
		hPC = false;

	if (mouse.getPosition(*window).x > 803 && mouse.getPosition(*window).x < 908 && mouse.getPosition(*window).y > 500 && mouse.getPosition(*window).y < 553)
		cPC = true;
	else
		cPC = false;

	if (sBC && mouse.isButtonPressed(sf::Mouse::Button::Left) && onceProtect) {
		if (player->inventory.numScrapMetal >= 1 && player->inventory.numChemical >= 1) {
			player->inventory.numChemical--;
			player->inventory.numScrapMetal--;
			player->inventory.numSmokebombs++;
			onceProtect = false;
			timer.restart();
		}

		else {
			timer.restart();
			notEnoughMaterials = true;
		}
	}

	if (shC && mouse.isButtonPressed(sf::Mouse::Button::Left) && onceProtect) {
		if (player->inventory.numScrapMetal >= 2) {
			player->inventory.numScrapMetal-=2;
			player->inventory.numShurikens++;
			onceProtect = false;
			timer.restart();
		}

		else {
			timer.restart();
			notEnoughMaterials = true;
		}
	}

	if (hPC && mouse.isButtonPressed(sf::Mouse::Button::Left) && onceProtect) {
		if (player->inventory.numHerb >= 2 && player->inventory.numContainer >= 1) {
			player->inventory.numContainer--;
			player->inventory.numHerb-=2;
			player->inventory.numHealthPotions++;
			onceProtect = false;
			timer.restart();
		}

		else {
			timer.restart();
			notEnoughMaterials = true;
		}
	}

	if (cPC && mouse.isButtonPressed(sf::Mouse::Button::Left) && onceProtect) {
		if (player->inventory.numChemical >= 1 && player->inventory.numContainer >= 1) {
			player->inventory.numContainer--;
			player->inventory.numChemical--;
			player->inventory.numCamoPotions++;
			onceProtect = false;
			timer.restart();
		}

		else {
			timer.restart();
			notEnoughMaterials = true;
		}
	}

	if (timer.getElapsedTime().asSeconds() >= 2)
		notEnoughMaterials = false;
	
	if (timer.getElapsedTime().asSeconds() >= 0.5)
		onceProtect = true;
}

void CraftingMenustate::render() {
	window->clear(sf::Color::Black);
	
	window->draw(background);
	
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 4; ++j)
			window->draw(boxes[i][j]);
	}

	if (sBC)
		window->draw(sBCraft);
	else
		window->draw(sBCraftIdel);

	if (shC)
		window->draw(shCraft);
	else
		window->draw(shCraftIdel);

	if (hPC)
		window->draw(hPCraft);
	else
		window->draw(hPCraftIdel);

	if (cPC)
		window->draw(cPCraft);
	else
		window->draw(cPCraftIdel);

	window->draw(herb);
	window->draw(chem);
	window->draw(metal);
	window->draw(container);
	window->draw(smokeBomb);
	window->draw(shuriken);
	window->draw(healthPotion);
	window->draw(camoPotion);

	window->draw(inventory);
	window->draw(sB);
	window->draw(sh);
	window->draw(hP);
	window->draw(cP);
	window->draw(c);
	window->draw(h);
	window->draw(ch);
	window->draw(m);

	window->draw(sBA);
	window->draw(shA);
	window->draw(hPA);
	window->draw(cPA);
	window->draw(hA);
	window->draw(chA);
	window->draw(mA);
	window->draw(cA);

	for (int i = 0; i < 4; ++i) {
		window->draw(mat[i]);
		window->draw(craft[i]);
	}

	window->draw(sBM);
	window->draw(shM);
	window->draw(hPM);
	window->draw(cPM);

	if (notEnoughMaterials)
		window->draw(notEnoughMat);
}

void CraftingMenustate::keyPressed(int keycode) {
	if (keycode == sf::Keyboard::Return) { // If player hits enter then pop off the state
		popOffState = true;
	}
}

void CraftingMenustate::keyReleased(int keycode) {

}

void CraftingMenustate::loadAssets() {	
	impact.loadFromFile("Resources/HUD/fonts/impact.ttf");
	cent_gothic.loadFromFile("Resources/HUD/fonts/century_gothic.ttf");

	inventory.setString("Inventory");
	inventory.setFont(impact);
	inventory.setPosition(470, 30);
	inventory.setScale(1.5, 1.5);

	notEnoughMat.setFont(impact);
	notEnoughMat.setScale(2, 2);
	notEnoughMat.setPosition(300, 300);
	notEnoughMat.setString("NOT ENOUGH MATERIALS");

	sBA.setFont(cent_gothic);
	sBA.setPosition(240, 290);
	sBA.setScale(2, 2);
	shA.setFont(cent_gothic);
	shA.setPosition(440, 290);
	shA.setScale(2, 2);
	hPA.setFont(cent_gothic);
	hPA.setPosition(640, 290);
	hPA.setScale(2, 2);
	cPA.setFont(cent_gothic);
	cPA.setPosition(840, 290);
	cPA.setScale(2, 2);
	hA.setFont(cent_gothic);
	hA.setPosition(240, 140);
	hA.setScale(1.7, 1.7);
	mA.setFont(cent_gothic);
	mA.setPosition(640, 140);
	mA.setScale(1.7, 1.7);
	chA.setFont(cent_gothic);
	chA.setPosition(440, 140);
	chA.setScale(1.7, 1.7);
	cA.setFont(cent_gothic);
	cA.setPosition(840, 140);
	cA.setScale(1.7, 1.7);

	sB.setString("Smoke Bomb");
	sB.setFont(impact);
	sB.setPosition(225, 260);
	sB.setScale(0.5, 0.5);
	sh.setString("Shuriken");
	sh.setFont(impact);
	sh.setPosition(425, 260);
	sh.setScale(0.5, 0.5);
	hP.setString("Health Potion");
	hP.setFont(impact);
	hP.setPosition(615, 260);
	hP.setScale(0.5, 0.5);
	cP.setString("Camoflague Potion");
	cP.setFont(impact);
	cP.setPosition(800, 260);
	cP.setScale(0.5, 0.5);
	h.setString("Herb");
	h.setFont(impact);
	h.setPosition(240, 110);
	h.setScale(0.5, 0.5);
	ch.setString("Chemical");
	ch.setFont(impact);
	ch.setPosition(425, 110);
	ch.setScale(0.5, 0.5);
	m.setString("Scrap Metal");
	m.setFont(impact);
	m.setPosition(625, 110);
	m.setScale(0.5, 0.5);
	c.setString("Container");
	c.setFont(impact);
	c.setPosition(825, 110);
	c.setScale(0.5, 0.5);

	for (int i = 0; i < 4; ++i) {
		mat[i].setFont(impact);
		mat[i].setString("Materials Required:");
		mat[i].setScale(0.4, 0.4);
		mat[i].setPosition((i*200) + 205, 410);
		craft[i].setFont(impact);
		craft[i].setString("CRAFT");
		craft[i].setScale(0.5, 0.5);
		craft[i].setPosition((i * 200) + 235, 515);
	}

	sBM.setFont(cent_gothic);
	sBM.setString("- 1 Scrap Metal\n- 1 Chemical");
	sBM.setScale(0.4, 0.4);
	sBM.setPosition(220, 425);

	shM.setFont(cent_gothic);
	shM.setString("- 2 Scrap Metal");
	shM.setScale(0.4, 0.4);
	shM.setPosition(420, 425);

	hPM.setFont(cent_gothic);
	hPM.setString("- 1 Container\n- 2 Herb");
	hPM.setScale(0.4, 0.4);
	hPM.setPosition(620, 425);

	cPM.setFont(cent_gothic);
	cPM.setString("- 1 Container\n- 1 Chemical");
	cPM.setScale(0.4, 0.4);
	cPM.setPosition(820, 425);

	background.setTexture(textureManager->getTexture("Resources/Menus/menu-background.png"));
	background.setPosition(0, 0);

	sBCraftIdel.setTexture(textureManager->getTexture("Resources/Menus/button-idel.png"));
	sBCraftIdel.setPosition(205, 500);
	sBCraftIdel.setScale(0.35, 0.35);
	sBCraft.setTexture(textureManager->getTexture("Resources/Menus/button-pressed.png"));
	sBCraft.setPosition(205, 500);
	sBCraft.setScale(0.35, 0.35);
	shCraftIdel.setTexture(textureManager->getTexture("Resources/Menus/button-idel.png"));
	shCraftIdel.setPosition(405, 500);
	shCraftIdel.setScale(0.35, 0.35);
	shCraft.setTexture(textureManager->getTexture("Resources/Menus/button-pressed.png"));
	shCraft.setPosition(405, 500);
	shCraft.setScale(0.35, 0.35);
	hPCraftIdel.setTexture(textureManager->getTexture("Resources/Menus/button-idel.png"));
	hPCraftIdel.setPosition(605, 500);
	hPCraftIdel.setScale(0.35, 0.35);
	hPCraft.setTexture(textureManager->getTexture("Resources/Menus/button-pressed.png"));
	hPCraft.setPosition(605, 500);
	hPCraft.setScale(0.35, 0.35);
	cPCraftIdel.setTexture(textureManager->getTexture("Resources/Menus/button-idel.png"));
	cPCraftIdel.setPosition(805, 500);
	cPCraftIdel.setScale(0.35, 0.35);
	cPCraft.setTexture(textureManager->getTexture("Resources/Menus/button-pressed.png"));
	cPCraft.setPosition(805, 500);
	cPCraft.setScale(0.35, 0.35);

	herb.setTexture(textureManager->getTexture("Resources/Collectibles/herb.png"));
	herb.setPosition(225, 140);
	herb.setScale(2, 2);
	chem.setTexture(textureManager->getTexture("Resources/Collectibles/chemical.png"));
	chem.setPosition(425, 140);
	chem.setScale(2, 2);
	metal.setTexture(textureManager->getTexture("Resources/Collectibles/scrapMetal.png"));
	metal.setPosition(625, 140);
	metal.setScale(2, 2);
	container.setTexture(textureManager->getTexture("Resources/Collectibles/container.png"));
	container.setPosition(825, 140);
	container.setScale(2, 2);

	smokeBomb.setTexture(textureManager->getTexture("Resources/Player/craftables/smokeBomb.png"));
	smokeBomb.setPosition(215, 295);
	smokeBomb.setScale(1.5, 1.5);
	shuriken.setTexture(textureManager->getTexture("Resources/Player/craftables/shuriken.png"));
	shuriken.setPosition(415, 295);
	shuriken.setScale(1.5, 1.5);
	healthPotion.setTexture(textureManager->getTexture("Resources/Player/craftables/healthPotion.png"));
	healthPotion.setPosition(615, 295);
	healthPotion.setScale(1.5, 1.5);
	camoPotion.setTexture(textureManager->getTexture("Resources/Player/craftables/camoPotion.png"));
	camoPotion.setPosition(815, 295);
	camoPotion.setScale(1.5, 1.5);

	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 4; ++j) {
			boxes[i][j].setTexture(textureManager->getTexture("Resources/Menus/box.png"));
			
			if (i == 0) {
				boxes[i][j].setPosition((j * 200) + 215, (i * 200) + 130);
				boxes[i][j].setScale(0.3, 0.3);
			}
			else {
				boxes[i][j].setScale(0.4, 0.4);
				boxes[i][j].setPosition((j * 200) + 200, (i * 150) + 130);
			}
		}
	}
}