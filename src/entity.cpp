#include "entityManager.h"
#include "entity.h"

entity::entity(entityManager* sm)
{
	manager = sm;
	position = glm::vec2(0.0f, 0.0f);
	rot = 0.0f;

	manager->addSprite(this);
}

entity::entity(entityManager* sm, const glm::vec2 &initialPos, float _rot)
{
	manager = sm;
	position = initialPos;
	rot = _rot;

	manager->addSprite(this);
}

entity::entity(const entity& other)
{
	manager = other.manager;
	position = other.position;
	rot = other.rot;

	manager->addSprite(this);
}

entity& entity::operator=(const entity& other)
{
	manager = other.manager;
	position = other.position;
	rot = other.rot;

	//we don't add it to the manager, as our sprite must already be in the manager by now
	return *this;
}

entity::~entity()
{
}

glm::vec2 entity::getPos() const
{
	if (parent != nullptr)
		return glm::rotate(position, parent->getRot()) + parent->getPos();
	return position;
}

float entity::getRot() const
{
	if (parent != nullptr)
		return rot + parent->getRot();
	return rot;
}

entity* entity::getParent() const
{
	return parent;
}

void entity::setParent(entity* p)
{
	parent = p;
}

void entity::setPos(const glm::vec2& p)
{
	position = p;
}

void entity::update()
{
	age += ofGetLastFrameTime(); // add the elapse time since last frame call
	//we may want to use something else, as frame rates can vary from system to system
}

void entity::setRot(float r)
{
	rot = r;
}

EID entity::getID() const
{
	return id;
}

bool entity::hasChanged()
{
	return false;
}

bool entity::isDead() const
{
	return false;
}

float entity::getLifeTime() const { return lifetime; }
float entity::getAge() const { return age; }