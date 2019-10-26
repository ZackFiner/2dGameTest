#pragma once
#include "solidEntity.h"
#include "motionPath.h"
#include "projectileEmitter.h"
/*H******************************************************************
 * FILENAME: tankSprite.h
 * AUTHOR: Zackary Finer
 *
 * DESCRIPTION:
 *
 *
 ********************************************************************/

#define TANK_DEFAULT_HP 100
#define TANK_LIFETIME 10.0f
#define TANK_POINTS 20
#define DESPAWN_RADIUS 100
class tankSprite : public solidEntity
{
	motionPath* pathManager;
	int hp;
	bool dead = false;
	glm::vec2 vel;
	float turretRot;
	ofImage img;
	projectileEmitter* gun;
public:
	tankSprite(entityManager*, collisionManager*, motionPath*);
	void update();
	void draw();
	bool isDead() const;
	glm::vec2 getVelocity() const;
	void setHealth(int);
	int getHealth() const;
	int getPoints() const;
	~tankSprite();
	int getTeam() const;
};