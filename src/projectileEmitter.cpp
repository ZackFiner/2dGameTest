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

projectileEmitter::projectileEmitter(entityManager* em, collisionManager* coll) :
	emitter(em)
{
	hitManager = coll;
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
	missile* msl;
	if (this->getParent()!=nullptr)
		msl = new missile(manager, hitManager, getPos(), this->dir*speed, this->getParent()->getID());
	else
		msl = new missile(manager, hitManager, getPos(), this->dir*speed, EID::nilID());
	msl->setDamage(projectileDamage);
	shootfx.play();
}

void projectileEmitter::setDamage(int amnt) { projectileDamage = 5; }

void projectileEmitter::update()
{
	if (fire)
	{

		unsigned long ct = ofGetCurrentTime().getAsMilliseconds();
		if (randomFire)
		{
			if (ct - lstF > randomFreq)
			{
				fireOne();
				lstF = ct;
				randomFreq = (ofRandomf()+1.0f)*500.0f;
			}
		}
		else {
			if (ct - lstF > frequency)
			{
				fireOne();
				lstF = ct;
			}
		}
	}
}

void projectileEmitter::setFireRate(float fr) { frequency = fr; }
void projectileEmitter::setSpeed(float sp) { speed = sp; }
void projectileEmitter::setRandomFire(bool v) { randomFire = v; }