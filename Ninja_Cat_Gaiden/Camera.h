#ifndef CAMERA_H
#define CAMERA_H

#include "Updateable.h"
#include "Tilemap.h"

class Camera : public Updateable {
public:
	Camera(Tilemap &tilemap);
	~Camera();

	void update(sf::Time deltaTime);
	void render();
private:
	Tilemap &tilemap;
};

#endif