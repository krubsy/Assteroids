#include "Entity.h"

Sprite* Entity::getSprite() {
	return sprite;
}

PhysicsBody* Entity::getBody() {
	return sprite->getPhysicsBody();
}

vec2 Entity::getPosition() {
	return vec2::toOurVec(sprite->getPosition());
}

void Entity::addForce(vec2 force)
{
	acceleration += force;
}

void Entity::update(float deltaTime) {
	velocity += acceleration * deltaTime;
	vec2 position = vec2::toOurVec(sprite->getPosition());
	position += velocity * deltaTime;
	sprite->setPosition(*(Vec2*)&position);
	acceleration = vec2(0.0f);
}

Entity::Entity()
{
}

Entity::~Entity() {
	//delete sprite;
	sprite = NULL;
}

Entity::Entity(vec2 position, std::string spritePath)
{
	load(position, spritePath);
}

void Entity::load(vec2 position, std::string spritePath)
{
	sprite = Sprite::create(spritePath); //Load the handle
	sprite->setPosition(vec2::toCocVec(position));
	sprite->setScale(0.25f); //Scale the bird since it loads in quite large
	sprite->setAnchorPoint(Vec2(0.5f, 0.5f)); //Ensure the middle of the bird is the anchor point
	auto body = PhysicsBody::createCircle((sprite->getSpriteFrame()->getRectInPixels().size.height) * 0.5f * 0.65f); //use a circle since bird is roughly circular
	std::cout << sprite->getSpriteFrame()->getRectInPixels().size.height * sprite->getScale() * 0.5f << std::endl;
	body->setContactTestBitmask(0xFFFFFFFF);
	sprite->setPhysicsBody(body);
}

