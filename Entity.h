#pragma once
#include "cocos2d.h"
#include "Math/Vector.h"
#include "Math/Matrix.h"

using namespace cocos2d;
class Entity
{
public:
	Entity();
	virtual ~Entity();
	Entity(MyVector position, std::string spritePath);
	void load(MyVector position, std::string spritePath);
	Sprite *getSprite();
	PhysicsBody* getBody();
	MyVector getPosition();

	void addForce(MyVector force);
	void update(float deltaTime);
	void kill(float delay = 0.0f);

	void setTheta(float theta) { this->theta = theta; }
	float getTheta() { return theta; }

	MyVector velocity;
	MyVector acceleration;
	mat4 rotation;
	
protected:
	Sprite* sprite;
	
	float theta = 0.0f;
	float maxVelocity = 100.0f;
	float maxAcceleration = 100.0f;
};