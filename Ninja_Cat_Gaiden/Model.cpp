#include "Model.h"
#include "Samurai.h"
#include "Chandelier.h"
#include "Hideable.h"
#include "ScrapMetalObj.h"
#include "ContainerObj.h"
#include "ChemicalObj.h"
#include "HerbObj.h"
#include "EnterPortal.h"
#include "ExitPortal.h"

#include <iostream>

Model::Model() {
	// Initialize the opening gamestate
	player = new Player(sf::Vector2f(7 << 5, 67 << 5), gsm);
}

Model::~Model() {

}

void Model::initLevel1() {
	// Add enemies
	gsm.getCurrentState()->enemies.push_back(new Samurai(sf::Vector2f((20 << 5) + 20, (36 << 5) + 2), gsm, player));
	gsm.getCurrentState()->enemies.push_back(new Samurai(sf::Vector2f((59 << 5) + 20, (67 << 5) + 2), gsm, player));
	gsm.getCurrentState()->enemies.push_back(new Samurai(sf::Vector2f((27 << 5) + 20, (20 << 5) + 2), gsm, player));
	gsm.getCurrentState()->enemies[2]->maxMovement = 224;
	gsm.getCurrentState()->enemies.push_back(new Samurai(sf::Vector2f((3 << 5) + 20, (20 << 5) + 2), gsm, player));
	gsm.getCurrentState()->enemies[3]->maxMovement = 480;

	// Add Interactable Objects
	gsm.getCurrentState()->objects.push_back(new ExitPortal(sf::Vector2f((7 << 5) + 13, (67 << 5)), gsm, player));
	gsm.getCurrentState()->objects.push_back(new Chandelier(sf::Vector2f((20 << 5) - 15, (29 << 5)), gsm, player));
	gsm.getCurrentState()->objects.push_back(new Chandelier(sf::Vector2f((59 << 5) - 15, (50 << 5)), gsm, player));
	gsm.getCurrentState()->objects.push_back(new Hideable(sf::Vector2f((23 << 5) - 6, (20 << 5) - 12), gsm, player));
	gsm.getCurrentState()->objects.push_back(new ScrapMetalObj(sf::Vector2f((46 << 5), (59 << 5)), gsm, player));
	gsm.getCurrentState()->objects.push_back(new ScrapMetalObj(sf::Vector2f((23 << 5) + 16, (17 << 5)), gsm, player));
	gsm.getCurrentState()->objects.push_back(new ContainerObj(sf::Vector2f((90 << 5), (8 << 5)), gsm, player));
	gsm.getCurrentState()->objects.push_back(new ChemicalObj(sf::Vector2f((29 << 5), (40 << 5)), gsm, player));
	gsm.getCurrentState()->objects.push_back(new HerbObj(sf::Vector2f((15 << 5), (72 << 5)), gsm, player));
	gsm.getCurrentState()->objects.push_back(new EnterPortal(sf::Vector2f((95 << 5), (3 << 5)), gsm, player));
}

void Model::initLevel2() {
	// Add enemies
	gsm.getCurrentState()->enemies.push_back(new Samurai(sf::Vector2f((52 << 5), (307 << 5) + 2), gsm, player));
	gsm.getCurrentState()->enemies[0]->maxMovement = 18 << 5;
	gsm.getCurrentState()->enemies.push_back(new Samurai(sf::Vector2f((81 << 5), (307 << 5) + 2), gsm, player));
	gsm.getCurrentState()->enemies[1]->maxMovement = 18 << 5;
	gsm.getCurrentState()->enemies.push_back(new Samurai(sf::Vector2f((35 << 5), (283 << 5) + 2), gsm, player));
	gsm.getCurrentState()->enemies[2]->maxMovement = 1 << 5;
	gsm.getCurrentState()->enemies.push_back(new Samurai(sf::Vector2f((97 << 5), (202 << 5) + 2), gsm, player));
	gsm.getCurrentState()->enemies[3]->maxMovement = 1 << 5;
	gsm.getCurrentState()->enemies.push_back(new Samurai(sf::Vector2f((114 << 5), (151 << 5) + 2), gsm, player));
	gsm.getCurrentState()->enemies[4]->maxMovement = 10 << 5;
	gsm.getCurrentState()->enemies.push_back(new Samurai(sf::Vector2f((68 << 5), (137 << 5) + 2), gsm, player));
	gsm.getCurrentState()->enemies[5]->maxMovement = 16 << 5;
	gsm.getCurrentState()->enemies.push_back(new Samurai(sf::Vector2f((1 << 5), (129 << 5) + 2), gsm, player));
	gsm.getCurrentState()->enemies[6]->maxMovement = 5 << 5;
	gsm.getCurrentState()->enemies.push_back(new Samurai(sf::Vector2f((65 << 5), (51 << 5) + 2), gsm, player));
	gsm.getCurrentState()->enemies[7]->maxMovement = 19 << 5;

	// Add Interactable Objects
	gsm.getCurrentState()->objects.push_back(new ExitPortal(sf::Vector2f((5 << 5) + 13, (306 << 5) - 10), gsm, player));
	gsm.getCurrentState()->objects.push_back(new Hideable(sf::Vector2f((51 << 5) - 16, (303 << 5) - 2), gsm, player));
	gsm.getCurrentState()->objects.push_back(new Hideable(sf::Vector2f((78 << 5) - 16, (51 << 5) - 10), gsm, player));
	gsm.getCurrentState()->objects.push_back(new Chandelier(sf::Vector2f((63 << 5) - 15, (301 << 5)), gsm, player));
	gsm.getCurrentState()->objects.push_back(new Chandelier(sf::Vector2f((5 << 5) - 15, (116 << 5)), gsm, player));
	gsm.getCurrentState()->objects.push_back(new ScrapMetalObj(sf::Vector2f((60 << 5), (298 << 5)), gsm, player));
	gsm.getCurrentState()->objects.push_back(new ScrapMetalObj(sf::Vector2f((65 << 5), (298 << 5)), gsm, player));
	gsm.getCurrentState()->objects.push_back(new ScrapMetalObj(sf::Vector2f((70 << 5), (298 << 5)), gsm, player));
	gsm.getCurrentState()->objects.push_back(new ScrapMetalObj(sf::Vector2f((111 << 5), (142 << 5)), gsm, player));
	gsm.getCurrentState()->objects.push_back(new ContainerObj(sf::Vector2f((85 << 5), (302 << 5)), gsm, player));
	gsm.getCurrentState()->objects.push_back(new ContainerObj(sf::Vector2f((57 << 5), (203 << 5)), gsm, player));
	gsm.getCurrentState()->objects.push_back(new ContainerObj(sf::Vector2f((51 << 5), (50 << 5)), gsm, player));
	gsm.getCurrentState()->objects.push_back(new HerbObj(sf::Vector2f((94 << 5), (302 << 5)), gsm, player)); 
	gsm.getCurrentState()->objects.push_back(new HerbObj(sf::Vector2f((146 << 5), (189 << 5)), gsm, player));
	gsm.getCurrentState()->objects.push_back(new HerbObj(sf::Vector2f((44 << 5), (147 << 5)), gsm, player)); 
	gsm.getCurrentState()->objects.push_back(new ChemicalObj(sf::Vector2f((41 << 5), (291 << 5)), gsm, player));
	gsm.getCurrentState()->objects.push_back(new ChemicalObj(sf::Vector2f((119 << 5), (243 << 5)), gsm, player));
	gsm.getCurrentState()->objects.push_back(new ChemicalObj(sf::Vector2f((52 << 5), (144 << 5)), gsm, player));
	gsm.getCurrentState()->objects.push_back(new ChemicalObj(sf::Vector2f((128 << 5), (87 << 5)), gsm, player));
	gsm.getCurrentState()->objects.push_back(new EnterPortal(sf::Vector2f((146 << 5), (18 << 5)), gsm, player));
}

void Model::update(sf::Time deltaTime) {
	gsm.update(deltaTime);
}

void Model::setGSM(GamestateManager &gsm) {
	this->gsm = gsm;
}