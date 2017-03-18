#pragma once

class Inventory {
public:
	enum Items { Katana = 0, Shuriken = 1, Smokebomb = 2, HealthPotion = 3, CamoPotion = 4 };
	int currentSelectedItem;
	int numOfUseableItems; // Used for math when switching items

	Inventory();
	~Inventory();

	int numScrapMetal, numHerb, numContainer, numChemical;
	int numShurikens, numSmokebombs, numKatana, numHealthPotions, numCamoPotions;

	
	void changeSelectedItem(int indexIncremementAmount);
};