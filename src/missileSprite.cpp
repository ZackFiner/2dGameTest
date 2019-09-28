#include "missileSprite.h"

#define MISSILE_LIFETIME 5.0f

missile::missile(entityManager* em, const glm::vec2& origin, const glm::vec2& vel)
	: entity(em),
	img("bullet.png")
{
	setPos(origin);
	float theta = glm::orientedAngle(glm::vec2(0.0, 1.0f), glm::normalize(vel));
	setRot(glm::degrees(glm::orientedAngle(glm::vec2(0.0,1.0f), glm::normalize(vel)))); // point the missile towards it's target
	velocity = vel;
	lifetime = MISSILE_LIFETIME;
	dim = glm::vec2(32.0f, 128.0f);
	img.mirror(true, false);
	img.resize(dim.x, dim.y);
}

void missile::draw()
{
	ofPushMatrix();
	ofTranslate(getPos());
	ofRotate(getRot());
	img.draw(-dim / 2);
	ofPopMatrix();
}

void missile::update()
{
	auto dim = glm::vec2(ofGetWidth(), ofGetHeight());
	auto pos = getPos();
	dead = glm::abs(pos.x) > dim.x / 2 || glm::abs(pos.y) > dim.y / 2; // delete if we're out of screen range
	entity::update();
	setPos(getPos() + velocity);
}

bool missile::isDead() const
{
	return entity::isDead() || dead;
}

glm::vec2 missile::getVelocity() const
{
	return velocity;
}