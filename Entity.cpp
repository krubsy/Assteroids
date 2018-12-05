#include "Entity.h"

Sprite* Entity::getSprite() {
	return sprite;
}

PhysicsBody* Entity::getBody() {
	return sprite->getPhysicsBody();
}

MyVector Entity::getPosition() {
	return MyVector::toOurVec(sprite->getPosition());
}

void Entity::addForce(MyVector force)
{
	acceleration += force;
}

void Entity::update(float deltaTime) {

	rotation = mat4::Identity;
	rotation.RotateZ(theta);
	velocity += acceleration * deltaTime;
	MyVector position = MyVector::toOurVec(sprite->getPosition());

	position += velocity * deltaTime;
	sprite->setPosition(*(Vec2*)&position);
	acceleration = MyVector(0.0f);
}

Entity::Entity()
{
}

Entity::~Entity() {
	//delete sprite;
	sprite = NULL;
}

Entity::Entity(MyVector position, std::string spritePath)
{
	load(position, spritePath);
}

void Entity::load(MyVector position, std::string spritePath)
{
	sprite = Sprite::create(spritePath); //Load the handle
	sprite->setPosition(MyVector::toCocVec(position));
	sprite->setScale(0.25f); //Scale the bird since it loads in quite large
	sprite->setAnchorPoint(Vec2(0.5f, 0.5f)); //Ensure the middle of the bird is the anchor point
	auto body = PhysicsBody::createCircle((sprite->getSpriteFrame()->getRectInPixels().size.height) * 0.5f * 0.65f); //use a circle since bird is roughly circular
	//std::cout << sprite->getSpriteFrame()->getRectInPixels().size.height * sprite->getScale() * 0.5f << std::endl;
	body->setContactTestBitmask(0xFFFFFFFF);
	sprite->setPhysicsBody(body);
	sprite->getPhysicsBody()->setDynamic(false);
}

