#pragma once
#include "solidEntity.h"
#include "emitter.h"
#include "projectileEmitter.h"
#include "spriteSheet.h"

/*H******************************************************************
 * FILENAME: heliSprite.h
 * AUTHOR: Zackary Finer
 * DATE: 10/26/2019
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
	int lastH = 100;
	bool shake = false;
	float shakeStart = -1.0f;
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

	int score = 0;
public:
	heliSprite(entityManager*, collisionManager*);
	void draw();
	bool isDead() const;
	void update();
	int getHealth() const;
	void setHealth(int);
	void onKeyPress(int);
	void onKeyRelease(int);
	void setUpdateCannonDir(bool);
	void setGunAng(float);
	void setGunRPM(float);
	glm::vec2 getVelocity() const;
	~heliSprite();
	void setScore(int);
	int getScore() const;
};