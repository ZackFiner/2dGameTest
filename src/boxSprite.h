#pragma once
#include "ofMain.h"
#include "entity.h"
#include "collisionHull.h"
#include "collisionManager.h"
/*H******************************************************************
 * FILENAME: boxSprite.h
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
class boxSprite : public entity
{
private:
	collisionManager * hit_manager;
	collisionHull * hitBox;
	bool changed;
	float size;
	bool dead = false;
public:
	boxSprite(entityManager*, float, collisionManager*);
	void draw();
	bool hasChanged();
	void setPos(const glm::vec2&);
	void setRot(float);
	void update();
	bool isDead() const;
	~boxSprite();
};