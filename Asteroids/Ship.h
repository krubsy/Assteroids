#pragma once
#include "proj.win32/Entity.h"


class Ship : public Entity 
{
public:
	Ship() = default;
	Ship(MyVector position, std::string spritePath);

	int shield = 4;
	int lives = 3;
};