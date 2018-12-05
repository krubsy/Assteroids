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
	Entity(vec2 position, std::string spritePath);
	void load(vec2 position, std::string spritePath);
	Sprite *getSprite();
	PhysicsBody* getBody();
	vec2 getPosition();
	void addForce(vec2 force);
	void update(float deltaTime);
	void kill(float delay = 0.0f);

	vec2 velocity;
	vec2 acceleration;
	
	
protected:
	Sprite* sprite;

	mat4 rotation;
	float theta = 0.0f;
	float maxVelocity = 10.0f;
	float maxAcceleration = 10.0f;
};