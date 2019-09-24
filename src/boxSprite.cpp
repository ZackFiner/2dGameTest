#include "boxSprite.h"


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
	auto collides = hit_manager->queryCollision(hitBox);
	if (collides.size() > 1)
		ofSetColor(ofColor::green);
	else
		ofSetColor(ofColor::white);
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
