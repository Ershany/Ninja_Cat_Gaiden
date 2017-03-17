#include "Camera.h"

#include <iostream>

Camera::Camera(Player &player, Tilemap &tilemap, sf::RenderWindow &window)
	: player(player), tilemap(tilemap), window(window)
{

}

Camera::~Camera() {

}

void Camera::update(const sf::Time &deltaTime) {
	// Set the offset so that the player is in the center of the screen
	tilemap.setOffset(player.position - sf::Vector2f((window.getSize().x >> 1) - (player.getSize().x >> 1), (window.getSize().y >> 1) - (player.getSize().y >> 1)));
	if (tilemap.getOffset().x < 0) {
		tilemap.setOffset(0, tilemap.getOffset().y);
	}
	else if (tilemap.getOffset().x > (tilemap.mapSize.x << 5) - 1200) {
		tilemap.setOffset((tilemap.mapSize.x << 5) - 1200, tilemap.getOffset().y);
	}
	if (tilemap.getOffset().y < 0) {
		tilemap.setOffset(tilemap.getOffset().x, 0);
	}
	else if (tilemap.getOffset().y > (tilemap.mapSize.y << 5) - 675) {
		tilemap.setOffset(tilemap.getOffset().x, (tilemap.mapSize.y << 5) - 675);
	}
}

void Camera::render() {
	tilemap.render(player.position - sf::Vector2f((window.getSize().x >> 1) - (player.getSize().x >> 1), (window.getSize().y >> 1) - (player.getSize().y >> 1)));
}