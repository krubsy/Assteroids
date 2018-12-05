#pragma once
#include "proj.win32/Entity.h"

class Asteroid : public Entity {
public:
	Asteroid() = default;
	Asteroid(MyVector position, std::string spritepath);
	Asteroid(MyVector position, MyVector size) : Asteroid(position, "images/asteroid.jpg") { this->size = size; }
	Asteroid(MyVector position, MyVector size, std::string spritepath) : Asteroid(position, spritepath) {
		this->size = size;
	}
private:
	MyVector size;
};