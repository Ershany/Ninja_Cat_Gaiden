#pragma once

#include <SFML\Graphics.hpp>

#include "Updateable.h"
#include "Renderable.h"
#include "GamestateManager.h"

class Enemy : public Updateable, public Renderable {
public:
	enum Type { Samurai };

	Enemy(sf::Vector2f &position, GamestateManager &gsm, Player *player);
	virtual ~Enemy();

	void update(const sf::Time &deltaTime) override;

	sf::Vector2u size;
	bool shouldRemove;
	Type type;
	bool facingRight;
	bool alertOfPlayer;

	float maxMovement;
protected:
	float currentMovement;

	GamestateManager &gsm;
	Player *player;

	sf::Vector2f speed;
	sf::Vector2f velocity;
	int health;
};