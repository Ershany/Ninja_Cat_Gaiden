#include "Inventory.h"

#include <iostream>

Inventory::Inventory() {
	// Non tweakable variables
	this->currentSelectedItem = 0;
	this->numOfUseableItems = 3;

	// Crafting Collectibles
	this->numChemical = 0;
	this->numContainer = 0;
	this->numHerb = 0;
	this->numScrapMetal = 0;

	// Crafted Items
	this->numShurikens = 3;
	this->numSmokebombs = 2;
	this->numKatana = -1;
}

Inventory::~Inventory() { }

void Inventory::changeSelectedItem(int indexIncremementAmount) {
	currentSelectedItem = (currentSelectedItem + indexIncremementAmount) % numOfUseableItems;
	if (currentSelectedItem < 0) currentSelectedItem = numOfUseableItems + currentSelectedItem;
}