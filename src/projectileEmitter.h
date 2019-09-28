#pragma once
#include "emitter.h"

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
	float speed = 5.0f;
	long lstF = 0.0f;
	bool fire = false;
	glm::vec2 dir;
	ofSoundPlayer shootfx;
public:
	projectileEmitter(entityManager*);
	void setDir(const glm::vec2&);
	void toggleFire(bool);
	void fireOne();
	void update();
	void setFireRate(float);
	void setSpeed(float);
};