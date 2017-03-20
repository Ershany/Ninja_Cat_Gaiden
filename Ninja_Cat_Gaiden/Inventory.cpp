#include "Inventory.h"

#include <iostream>

Inventory::Inventory() {
	// Non tweakable variables
	this->currentSelectedItem = 0;
	this->numOfUseableItems = 5;

	// Crafting Collectibles
	this->numChemical = 3;
	this->numContainer = 3;
	this->numHerb = 3;
	this->numScrapMetal = 3;

	// Crafted Items
	this->numShurikens = 2;
	this->numSmokebombs = 1;
	this->numCamoPotions = 1;
	this->numHealthPotions = 1;
	this->numKatana = -1;
}

Inventory::~Inventory() { }

void Inventory::changeSelectedItem(int indexIncremementAmount) {
	currentSelectedItem = (currentSelectedItem + indexIncremementAmount) % numOfUseableItems;
	if (currentSelectedItem < 0) currentSelectedItem = numOfUseableItems + currentSelectedItem;
}