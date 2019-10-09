#pragma once
#include "ofMain.h"
#include "EID.h"

#define VEL_TIME_CONST 150.0f
/*H**********************************************************************
 * FILENAME: entity.h
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


class entityManager;
class entity
{
protected:
	EID id; // id initialization is automatic.
	entityManager* manager;
	glm::vec2 position;
	float rot;
	float lifetime = 0.0f;
	float age = 0.0f;
	entity* parent = nullptr;
public:
	entity(entityManager*);
	entity(entityManager*, const glm::vec2&, float);
	entity(const entity&);
	entity& operator=(const entity&);
	EID getID() const;
	float getLifeTime() const;
	float getAge() const;
	void setParent(entity*);
	entity* getParent() const;

	virtual bool hasChanged();
	virtual void draw() = 0;
	virtual ~entity();
	virtual glm::vec2 getPos() const;
	virtual float getRot() const;
	virtual void update();
	virtual void setPos(const glm::vec2&);
	virtual void setRot(float);
	virtual bool isDead() const;
	virtual void setHealth(int);
	virtual int getHealth() const;
	virtual glm::vec2 getVelocity() const;
	virtual int getPoints() const;
	virtual void setScore(int);

};