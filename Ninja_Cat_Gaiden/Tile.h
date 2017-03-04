#ifndef TILE_H
#define TILE_H

#include <SFML\Graphics.hpp>

#include "Updateable.h"
#include "Renderable.h"

class Tile : public Updateable, public Renderable {
public:
	static int width;
	static int height;

	Tile();
	Tile(sf::Vector2f &position, bool solid = false, bool projectileSolid = false);
	~Tile();

	void update(const sf::Time &deltaTime);

	void setPosition(sf::Vector2f &position);
	void setSolid(bool choice);
	void setProjectileSolid(bool choice);
	void setTransparent(bool choice);
	void setDamaging(bool choice);
	void setDamageAmount(int amount);

	bool getSolid() const;
	bool getProjecitleSolid() const;
	bool getTransparent() const;
	bool getDamaging() const;
	int getDamageAmount() const;
	sf::Vector2f getPosition() const;
private:
	bool solid;
	bool projectileSolid;

	bool damaging;
	int damageAmount;

	bool transparent;
};

#endif