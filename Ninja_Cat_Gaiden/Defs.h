#pragma once

#include <SFML\Graphics.hpp>

#define DEBUG 0

sf::Vector2f normalize(const sf::Vector2f &vec);

sf::Vector2f operator*(const sf::Vector2f &vec1, const sf::Vector2f &vec2);