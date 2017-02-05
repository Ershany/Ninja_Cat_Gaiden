#ifndef TILE_H
#define TILE_H

#include <SFML\Graphics.hpp>

#include "Updateable.h"
#include "Renderable.h"

class Tile : public Updateable, public Renderable {
public:
	static int width;
	static int height;

	Tile(int x, int y, bool solid = false, bool projectileSolid = false);
	~Tile();

	void update(sf::Time deltaTime);

	void setSolid(bool choice);
	void setProjectileSolid(bool choice);
	bool getSolid() const;
	bool getProjecitleSolid() const;
private:
	int x, y;
	bool solid;
	bool projectileSolid;
};

#endif