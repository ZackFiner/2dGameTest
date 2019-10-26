#include "entityManager.h"
#include "entity.h"

/*H**********************************************************************
 * FILENAME: entity.cpp
 * AUTHOR: Zackary Finer
 *
 * DESCRIPTION:
 * Entities are at the center of this game engine. An entity represents
 * an object that exists at somepoint in space and performs some function.
 *
 * Player's, missiles, enemies, and emitters are all entities, as they
 * all exist at some point in space and perform some function (move, shoot,
 * etc.)
 *
 * When an entity is created, it must be assigned an entity manager, which
 * will be used to manage it throughout it's lifetime. Entities have
 * various attributes (position, rotation, health, lifetime, velocity,
 * etc.) and various methods (draw(), setPos(), setRot(), etc.). Not all
 * of these methods are used during an entities lifetime (for example, an
 * emitter entity doesn't need to be drawn, as it simply represents a point
 * in space from which other entities are to be created).
 *
 * Finally, entity is an abstract class, and as such you must inherit
 * from entity in order to create instances of entities (heliSprite,
 * missile, projectileEmitter are all examples of concrete entities).
 *
 ************************************************************************/

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
		return glm::rotate(position,glm::radians( parent->getRot())) + parent->getPos();
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

void entity::setScore(int amnt) {}

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

void entity::setHealth(int hp) {/*child class implements this*/}
int entity::getHealth() const { return 0; }
glm::vec2 entity::getVelocity() const { return glm::vec2(); }
float entity::getLifeTime() const { return lifetime; }
float entity::getAge() const { return age; }
int entity::getPoints() const { return 0; }
void entity::onKeyPress(int key) {}
void entity::onKeyRelease(int key) {}
int entity::getCollisionType() const { return COLLISION_TYPE_SOLID; }
int entity::getTeam() const { return TEAM_0; }