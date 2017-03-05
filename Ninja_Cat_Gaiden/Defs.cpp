#include "Defs.h"

sf::Vector2f normalize(const sf::Vector2f &vec) {
	float length = sqrt((vec.x * vec.x) + (vec.y * vec.y));

	if (length != 0) {
		return sf::Vector2f(vec.x / length, vec.y / length);
	}
	else {
		return vec;
	}
}

float length(const sf::Vector2f &vec) {
	return sqrt((vec.x * vec.x) + (vec.y * vec.y));
}

sf::Vector2f operator*(const sf::Vector2f &vec1, const sf::Vector2f &vec2) {
	return sf::Vector2f(vec1.x * vec2.x, vec1.y * vec2.y);
}