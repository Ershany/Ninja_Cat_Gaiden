#include "Camera.h"

Camera::Camera(Player &player, Tilemap &tilemap, sf::RenderWindow &window)
	: player(player), tilemap(tilemap), window(window)
{

}

Camera::~Camera() {

}

void Camera::update(const sf::Time &deltaTime) {
	// Set the offset so that the player is in the center of the screen
	tilemap.setOffset(player.position - sf::Vector2f((window.getSize().x >> 1) - (player.getSize().x >> 1), (window.getSize().y >> 1) - (player.getSize().y >> 1)));
}

void Camera::render() {
	tilemap.render(player.position - sf::Vector2f((window.getSize().x >> 1) - (player.getSize().x >> 1), (window.getSize().y >> 1) - (player.getSize().y >> 1)));
}