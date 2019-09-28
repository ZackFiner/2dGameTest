#pragma once
#include "entity.h"

/*H******************************************************************
 * FILENAME: missileSprite.h
 * AUTHOR: Zackary Finer
 *
 * DESCRIPTION:
 * missileSprite is what is sounds like: a sprite for a missile.
 * it is an entity with an image associated with it, that moves through
 * space along a straight line (however, i make change the "straight
 * line" part of this). 
 *
 * Right now, this entity is non-solid, meaning it will not have any
 * presence in collision detection calculations. However, I plan
 * to change this soon.
 *
 ********************************************************************/

class missile : public entity
{
	bool dead = false;
	glm::vec2 velocity;
	glm::vec2 dim;
	ofImage img;
public:
	/*
	manager, origin, velocity
	*/
	missile(entityManager*, const glm::vec2&, const glm::vec2&);
	void draw();
	void update(); //right now, travels to the edge of the screen and dies
	bool isDead() const;
	glm::vec2 getVelocity() const;
};