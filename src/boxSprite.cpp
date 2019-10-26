#include "boxSprite.h"

/*H******************************************************************
 * FILENAME: boxSprite.cpp
 * AUTHOR: Zackary Finer
 * DATE: 10/26/2019
 *
 * DESCRIPTION:
 * This entity is essentially a debug entity used to test various
 * systems, such as the collision detection and entity management
 * system. It calculates it's own collisions, and jossles around the
 * screen.
 *
 ********************************************************************/

boxSprite::boxSprite(entityManager* _manager, float _size, collisionManager* h_manager) :
	entity(_manager),
	hit_manager(h_manager),
	size(_size)
{
	hitBox = new collisionHull();
	hitBox->owner = this;
	hit_manager->addEntity(hitBox);
}

void boxSprite::draw()
{
	ofPushMatrix();
	ofTranslate(glm::vec3(getPos().x, getPos().y, 0));
	ofRotateZ(glm::radians(getRot()));
	/*auto collides = hit_manager->queryCollision(hitBox);
	if (collides.size() > 1)
		ofSetColor(ofColor::green);
	else
		ofSetColor(ofColor::white);*/
	ofDrawRectangle(glm::vec2(0, 0), size, size);
	ofPopMatrix();
	ofSetColor(ofColor::red);
	hitBox->debugDrawAABB();
	ofSetColor(ofColor::white);
}
bool boxSprite::hasChanged()
{
	return changed;
}


void boxSprite::update()
{
	entity::update();
	setPos(getPos() + glm::diskRand(1.0f));
	auto hits = hit_manager->queryCollision(hitBox);
	//if (hits.size() > 1)
		//dead = true;
}

bool boxSprite::isDead() const { return dead; }

void boxSprite::setPos(const glm::vec2& _newPos)
{
	entity::setPos(_newPos);
	hitBox->changed = true;
}

void boxSprite::setRot(float _newRot)
{
	entity::setRot(_newRot);
	hitBox->changed = true;
}

boxSprite::~boxSprite()
{
	hit_manager->removeEntity(hitBox);
	delete hitBox;
}
