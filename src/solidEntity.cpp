#include "solidEntity.h"

solidEntity::solidEntity(entityManager* _manager, collisionManager* _hitManager, collisionHull hitBox) :
	entity(_manager)
{
	this->hitManager = _hitManager;
	this->hitBox = hitBox;
	this->hitBox.owner = (entity*)this;
	this->hitManager->addEntity(&(this->hitBox));
}

void solidEntity::update()
{
	entity::update();
}

void solidEntity::draw() const {/*we don't draw these*/}

std::vector<entity*> solidEntity::getCollisions()
{
	auto result = hitManager->queryCollision(&hitBox);
	std::vector<entity*> _return;
	for (auto hull : result)
		_return.push_back(hull->owner);
	return _return;
}

solidEntity::~solidEntity()
{
	hitManager->removeEntity(&hitBox);
}

void solidEntity::setPos(const glm::vec2& newPos) { entity::setPos(newPos); hitBox.changed = true; }
void solidEntity::setRot(float newRot) { entity::setRot(newRot); hitBox.changed = true; }