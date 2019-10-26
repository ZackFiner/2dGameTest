#pragma once
#include "emitter.h"
#include "collisionManager.h"
/*H******************************************************************
 * FILENAME: projectileEmitter.h
 * AUTHOR: Zackary Finer
 *
 * DESCRIPTION:
 * This emitter is used to emit projectiles (such as bullets or missiles).
 * It 'shoots' these projectiles from it's origin point, in a direction
 * specified during it's creation (dir), at a frequency specified
 * (frequency, in ms).
 * 
 * The projectiles created by this emitter will travel at a speed
 * specified by the speed member variable.
 *
 ********************************************************************/

class projectileEmitter : public emitter
{
	float frequency = 100.0f;//ms between shots
	float randomFreq = 100.0f;
	float speed = 5.0f;
	int projectileDamage = 25;
	unsigned long lstF = 0;
	bool fire = false;
	glm::vec2 dir;
	ofSoundPlayer shootfx;
	collisionManager* hitManager;
	bool randomFire = false;
public:
	projectileEmitter(entityManager*, collisionManager*);
	void setDir(const glm::vec2&);
	void toggleFire(bool);
	void fireOne();
	void update();
	void setFireRate(float);
	void setSpeed(float);
	void setDamage(int);
	void setRandomFire(bool);
};