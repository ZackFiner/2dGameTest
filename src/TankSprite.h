#pragma once
#include "solidEntity.h"
#include "motionPath.h"
#include "projectileEmitter.h"
#include "GameSettings.h"
/*H******************************************************************
 * FILENAME: tankSprite.h
 * AUTHOR: Zackary Finer
 * DATE: 10/26/2019
 *
 * DESCRIPTION:
 * Tank's are one of the basic entities in the game. They follow
 * a predetermined path of movement, and are spawned by a tank
 * -spawner. They shoot projectiles down towards the player at
 * random intervals.
 *
 *
 ********************************************************************/

class tankStaticData {
public:
	ofImage tank_sprite;
	ofImage spaa_sprite;
	tankStaticData()
	{
		tank_sprite.load("T90.png");
		tank_sprite.resize(70, 70);
		tank_sprite.mirror(true, false);
		spaa_sprite.load("9k22.png");
		spaa_sprite.resize(70, 70);
		spaa_sprite.mirror(true, false);
	}
};

class tankSprite : public solidEntity
{
protected:
	motionPath* pathManager;
	int hp;
	bool dead = false;
	float accuracy = 20.0f;
	glm::vec2 vel;
	float turretRot;
	//ofImage img;
	projectileEmitter* gun;
	float lastTurretRot = turretRot;
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

class spaaSprite : public tankSprite
{
protected:
	float burst_freq;
	unsigned long lst_burst;
public:
	spaaSprite(entityManager*, collisionManager*, motionPath*);
	void update();
	void draw();
	int getPoints() const;
	//~spaaSprite();
};