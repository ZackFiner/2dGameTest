#pragma once
#include "solidEntity.h"
#include "emitter.h"
#include "projectileEmitter.h"
#include "spriteSheet.h"

/*H******************************************************************
 * FILENAME: heliSprite.h
 * AUTHOR: Zackary Finer
 *
 * DESCRIPTION:
 * heliSprite is the sprite controlled by the player. It takes input
 * from the keyboard to move, and has a projectile launcher to shoot
 * bullets at things.
 *
 * heliSprite is a solidEntity, meaning it will be considered during
 * collision detection calculations. This will allow it to take damage
 * when hit by enemy projectiles.
 *
 ********************************************************************/

class heliSprite : public solidEntity
{
	int health = 100;
	projectileEmitter* gun;
	glm::vec2 vel;
	float f=0.0f, l = 0.0f, r = 0.0f, b = 0.0f;
	float angAcc, angV;
	ofImage img;
	spriteSheet rotor;
	ofSoundPlayer main, whine;
	glm::vec2 dim;
	bool updateCannon = true;
public:
	heliSprite(entityManager*, collisionManager*);
	void draw();
	bool isDead() const;
	void update();
	int getHealth() const;
	void setHealth(int);
	void handleKeyInput(int);
	void handleKeyRelease(int);
	void setUpdateCannonDir(bool);
	void setGunAng(float);
	void setGunRPM(float);
	glm::vec2 getVelocity() const;
	~heliSprite();
};