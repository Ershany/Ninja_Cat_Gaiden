#pragma once

#include <SFML\Graphics.hpp>

#include "Updateable.h"
#include "Renderable.h"
#include "GamestateManager.h"

class Enemy : public Updateable, public Renderable {
public:
	Enemy(sf::Vector2f &position, GamestateManager &gsm);
	~Enemy();

	void update(const sf::Time &deltaTime) override;
protected:
	GamestateManager &gsm;

	sf::Vector2f speed;
	sf::Vector2f velocity;
	sf::Vector2u size;
	float health;
};