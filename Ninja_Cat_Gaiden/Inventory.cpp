#include "Inventory.h"

#include <iostream>

Inventory::Inventory() {
	// Non tweakable variables
	this->currentSelectedItem = 0;
	this->numOfUseableItems = 5;

	// Crafting Collectibles
	this->numChemical = 0;
	this->numContainer = 0;
	this->numHerb = 0;
	this->numScrapMetal = 0;

	// Crafted Items
	this->numShurikens = 2;
	this->numSmokebombs = 1;
	this->numCamoPotions = 1;
	this->numHealthPotions = 3;
	this->numKatana = -1;
}

Inventory::~Inventory() { }

void Inventory::changeSelectedItem(int indexIncremementAmount) {
	currentSelectedItem = (currentSelectedItem + indexIncremementAmount) % numOfUseableItems;
	if (currentSelectedItem < 0) currentSelectedItem = numOfUseableItems + currentSelectedItem;
}