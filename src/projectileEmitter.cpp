#include "projectileEmitter.h"
#include "missileSprite.h"

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