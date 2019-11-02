#pragma once
#include "solidEntity.h"

/*H******************************************************************
 * FILENAME: missileSprite.h
 * AUTHOR: Zackary Finer
 * DATE: 10/26/2019
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

#define MISSILE_LIFETIME 5.0f
#define DEFAULT_DAMAGE 25.0f
class particleForce;
class missile : public solidEntity
{
	std::vector<particleForce*> forces;
	bool first_apply = true;
	bool dead = false;
	bool hit = false;
	glm::vec2 acc;
	glm::vec2 velocity;
	glm::vec2 dim;
	ofImage img;
	EID shotFrom;
	int team;
	int dmg = DEFAULT_DAMAGE;
	void applyParticleForces();
public:
	/*
	manager, origin, velocity
	*/
	missile(entityManager*, collisionManager*, const glm::vec2&, const glm::vec2&, EID);
	void draw();
	void update(); //right now, travels to the edge of the screen and dies
	bool isDead() const;
	glm::vec2 getVelocity() const;
	int getTeam() const;
	int getCollisionType() const;
	void setDamage(int);
	~missile();
	void addForce(particleForce* force) { forces.push_back(force); }
};