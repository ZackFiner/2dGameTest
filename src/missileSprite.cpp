#include "missileSprite.h"

#define MISSILE_LIFETIME 10.0f

missile::missile(entityManager* em, const glm::vec2& origin, const glm::vec2& vel)
	: entity(em)
{
	setPos(origin);
	setRot(glm::degrees(glm::orientedAngle(glm::vec2(1.0f,0.0f), vel))); // point the missile towards it's target
	velocity = vel;
	lifetime = MISSILE_LIFETIME;
}

void missile::draw()
{
	ofPushMatrix();
	ofTranslate(getPos());
	ofRotate(getRot());
	glm::vec2 dim = glm::vec2(5.0f, 5.0f);
	ofDrawRectangle(dim / 2, dim.x, dim.y);
	ofPopMatrix();
}

void missile::update()
{
	auto dim = glm::vec2(ofGetScreenWidth(), ofGetScreenHeight());
	auto pos = getPos();
	dead = glm::abs(pos.x) > dim.x / 2 || glm::abs(pos.y) > dim.y / 2; // delete if we're out of screen range
	entity::update();
	setPos(getPos() + velocity);
}

bool missile::isDead() const
{
	return entity::isDead() || dead;
}
