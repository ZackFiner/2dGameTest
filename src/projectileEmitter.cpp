#include "projectileEmitter.h"
#include "missileSprite.h"

/*H******************************************************************
 * FILENAME: projectileEmitter.cpp
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

projectileEmitter::projectileEmitter(entityManager* em) :
	emitter(em)
{
	shootfx.load("mg_fire4.wav");
	shootfx.setVolume(0.2f);
}

void projectileEmitter::setDir(const glm::vec2& dir)
{
	this->dir = glm::normalize(dir);
}

void projectileEmitter::toggleFire(bool f)
{
	fire = f;
}

void projectileEmitter::fireOne()
{
	missile* msl = new missile(manager, getPos(), this->dir*speed);
	shootfx.play();
}

void projectileEmitter::update()
{
	if (fire)
	{
		long ct = ofGetCurrentTime().getAsMilliseconds();
		if (ct - lstF > frequency)
		{
			fireOne();
			lstF = ofGetCurrentTime().getAsMilliseconds();
		}
	}
}

void projectileEmitter::setFireRate(float fr) { frequency = fr; }
void projectileEmitter::setSpeed(float sp) { speed = sp; }