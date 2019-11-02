#include "heliSprite.h"
#include "particleEmitter.h"
#include "GameSettings.h"
/*H******************************************************************
 * FILENAME: heliSprite.cpp
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

#define ACCEL_RATE 15.0f
#define DECEL_RATE 0.05f

heliSprite::heliSprite(entityManager* em, collisionManager* cm) :
	solidEntity(em, cm, collisionHull()),
	img("ah64.png"),
	rotor("rotor_sheet.png", 50.0f, glm::vec2(106.0f,106.0f), glm::vec2(364,364), 4)
{
	smoke_sys = new particleSystem();
	em->particleSystems.addParticleSystem(smoke_sys);
	smoke = new smokeEmitter(smoke_sys, (entity*)this);
	smoke->smokeColor = ofColor(45,45,45);
	smoke->setPos(glm::vec2(0.0f,0.0f));
	
	gun = new projectileEmitter(em, cm);
	gun->setSpeed(3000.0f);
	gun->setParent((entity*)this);
	gun->setDir(glm::vec2(0.0f, 1.0f));
	gun->setPos(glm::vec2(0.0f, 50.0f));
	dim = glm::vec2(150.0f, 150.0f);
	img.resize(dim.x, dim.y);
	img.mirror(true, false);
	
	main.load("rotor_loop.wav");
	main.setVolume(0.2f);
	main.setLoop(true);
	main.play();
	whine.load("rotor_loop.wav");
	whine.setVolume(0.2f);
	whine.setLoop(true);
	whine.play();
	
}

void heliSprite::draw()
{
	ofPushMatrix();
	ofTranslate(position);
	ofRotate(rot);
	if (getAge()-shakeStart < 0.35f)
	{
		ofSetColor(ofColor::red);
		ofTranslate(glm::ballRand(10.0f));
	}
	else
	{
		ofSetColor(ofColor::white);
	}
	//draw
	//ofDrawRectangle(-dim/2, dim.x,dim.y);
	img.draw(-dim / 2);
	rotor.draw(-rotor.getSize()/2 + glm::vec2(0.0f, 10.0f));
	ofSetColor(ofColor::white);
	ofPopMatrix();
}

bool heliSprite::isDead() const
{
	return health <= 0;
}

void heliSprite::update()
{
	if (getHealth() < 50)
		smoke->start();
	else
		smoke->stop();
	smoke->update();
	rotor.update();
	solidEntity::update();
	float dT = ofGetLastFrameTime();
	if (abs(f) > 0.0f || abs(b) > 0.0f)
		vel.y = glm::clamp(vel.y + (f - b)*ACCEL_RATE*dT, -5.0f, 5.0f);
	else
		vel.y -= vel.y*DECEL_RATE;

	if (abs(l) > 0.0f || abs(r) > 0.0f)
		vel.x = glm::clamp(vel.x + (l - r)*ACCEL_RATE*dT, -5.0f, 5.0f);
	else
		vel.x -= vel.x*DECEL_RATE;

	//vel *= 150.0f;
	whine.setSpeed(1+(glm::fastLength(vel)/5.0f)*0.2f);
	glm::vec2 front = glm::normalize(vel + glm::vec2(0, 15.0f));
	float theta = glm::degrees(glm::orientedAngle(glm::vec2(0.0f, 1.0f),front));
	if (updateCannon)
		gun->setDir(front);
	//std::cout << vel << std::endl;
	//std::cout << cont << std::endl;
	//std::cout << getPos() << std::endl;
	glm::vec2 scrnDim = glm::vec2(ofGetWidth(), ofGetHeight());
	glm::vec2 newPos = glm::clamp(vel*150.0f*dT + position, -scrnDim / 2, glm::vec2(scrnDim.x/2, 0.0f));
	setPos(newPos);
	setRot(theta);

	if (lastH != health)
	{
		shake = true;
		if (lastH > health)
			shakeStart = this->getAge();
		lastH = health;
	}
}

int heliSprite::getHealth() const { return health; }
void heliSprite::setHealth(int _health) { health = _health; }
glm::vec2 heliSprite::getVelocity() const
{
	return vel;
}
void heliSprite::onKeyPress(int key)
{
	switch (key)
	{
	case 'w':
	case 'W':
		f = 1.0f;
		break;
	case 's':
	case 'S':
		b = 1.0f;
		break;
	case 'a':
	case 'A':
		l = 1.0f;
		break;
	case 'd':
	case 'D':
		r = 1.0f;
		break;
	case ' ':
		gun->toggleFire(true);
		break;
	}
}

void heliSprite::onKeyRelease(int key)
{
	/*
	There is an issue here: if the player holds control while they release the movement
	keys, it does not register the key was released.
	*/
	switch (key)
	{
	case 'w':
	case 'W':
		f = 0.0f;
		break;
	case 's':
	case 'S':
		b = 0.0f;
		break;
	case 'a':
	case 'A':
		l = 0.0f;
		break;
	case 'd':
	case 'D':
		r = 0.0f;
		break;
	case ' ':
		gun->toggleFire(false);
		break;
	}
}

void heliSprite::setUpdateCannonDir(bool val) { updateCannon = val; }
void heliSprite::setGunAng(float rot) { this->gun->setDir(glm::rotate(glm::vec2(0.0f, 1.0f), glm::radians(rot))); }
void heliSprite::setGunRPM(float rpm) { this->gun->setFireRate(1000.0f*60.0f / rpm); }
int heliSprite::getScore() const { return score; }
void heliSprite::setScore(int amnt) { score += amnt; }
heliSprite::~heliSprite()
{
	/*WARNING: If you are having issues with things not getting iterated through, look here*/
	/*It may be possible for the cannon to get deleted in the while loop and */
	manager->deleteSprite(gun->getID());
	smoke_sys->setLifetime(6.0f);
	delete smoke;

	auto corpse = new deadHeliSprite(manager);
	corpse->setPos(getPos());
	corpse->setRot(getRot());
}

deadHeliSprite::deadHeliSprite(entityManager* em) :
	entity(em),
	img("ah64.png"),
	rotor("rotor_sheet.png", 50.0f, glm::vec2(106.0f, 106.0f), glm::vec2(364, 364), 4)
{
	smoke_sys = new particleSystem();
	em->particleSystems.addParticleSystem(smoke_sys);
	smoke = new smokeEmitter(smoke_sys, this);
	//smoke_sys->forces.erase(smoke_sys->forces.begin() + 1);
	smoke->smokeColor = ofColor(45, 45, 45);
	smoke->setPos(glm::vec2(0.0f, 0.0f));
	smoke->start();

	dim = glm::vec2(150.0f, 150.0f);
	img.resize(dim.x, dim.y);
	img.mirror(true, false);

	main.load("rotor_loop.wav");
	main.setVolume(0.2f);
	main.setLoop(true);
	main.play();

	lifetime = GAME_END_PHASE / 2000;
}

void deadHeliSprite::update()
{
	entity::update();
	smoke->update();
	float spooldown = ((lifetime - age) / lifetime);
	((screenDragForce*)(smoke_sys->forces[1]))->setSpeed((3000* spooldown));
	rotor.update();
	setPos(getPos() + glm::vec2(100.0f, -100.0f)*ofGetLastFrameTime());
	setRot(getRot() + 720.0f*ofGetLastFrameTime());
}

bool deadHeliSprite::isDead() const { return false;/*More like "un-dead" heli*/ }

void deadHeliSprite::draw()
{
	ofPushMatrix();
	ofTranslate(position);
	ofRotate(rot);
	ofSetColor(ofColor::white);

	//draw
	//ofDrawRectangle(-dim/2, dim.x,dim.y);
	img.draw(-dim / 2);
	rotor.draw(-rotor.getSize() / 2 + glm::vec2(0.0f, 10.0f));
	ofSetColor(ofColor::white);
	ofPopMatrix();
}

deadHeliSprite::~deadHeliSprite()
{
	smoke_sys->setLifetime(6.0f);
	delete smoke;

	particleSystem* explosionSys = new particleSystem();
	explosionSys->initSoundPlay(&(sysStatic().getRandomExplosion()));
	auto e = explosionEmitter(explosionSys, 30, this->getPos());
	explosionSys->forces.erase(explosionSys->forces.begin() + 1);
	explosionSys->setLifetime(6.0f);
	manager->particleSystems.addParticleSystem(explosionSys);
}



introHeliSprite::introHeliSprite(entityManager* em) :
	entity(em),
	img("ah64.png"),
	rotor("rotor_sheet.png", 50.0f, glm::vec2(106.0f, 106.0f), glm::vec2(364, 364), 4),
	rotor1_img("ah64_blade.png")
{
	wash_sys = new particleSystem();
	em->particleSystems.addParticleSystem(wash_sys);
	rotor_wash = new washEmitter(wash_sys, this);
	//smoke_sys->forces.erase(smoke_sys->forces.begin() + 1);
	rotor_wash->smokeColor = ofColor(232, 220, 125);
	rotor_wash->setPos(glm::vec2(0.0f, 0.0f));
	//rotor_wash->start();

	dim = glm::vec2(150.0f, 150.0f);
	img.resize(dim.x, dim.y);
	img.mirror(true, false);

	rotordim = glm::vec2(106.0f, 106.0f);
	rotor1_img.resize(rotordim.x, rotordim.y);
	rotor1_img.mirror(true, false);

	main.load("rotor_loop.wav");
	main.setVolume(0.2f);
	main.setLoop(true);
	//main.play();
}

void introHeliSprite::update()
{
	if (start)
	{
		spool += ofGetLastFrameTime() * 0.33;
		spool = glm::clamp(spool, 0.0f, 1.0f);
		main.setSpeed(spool);
		rotorSpin += spool * 3600.0f * ofGetLastFrameTime();
	}
	
	entity::update();
	rotor_wash->maxF = (0.1f + (1 - (spool - ((scale-0.5f) * 2.0f))));
	rotor_wash->minF = (0.05f + (1 - (spool - ((scale - 0.5f) * 2.0f))));
	if (scale > 0.7f)
		rotor_wash->stop();
	rotor_wash->update();

	rotor.update();
}

bool introHeliSprite::isDead() const { return false;/*More like "un-dead" heli*/ }

void introHeliSprite::draw()
{
	ofPushMatrix();
	ofTranslate(position);
	ofRotate(rot);
	ofScale(glm::vec3(scale));
	ofSetColor(ofColor::white);

	//draw
	//ofDrawRectangle(-dim/2, dim.x,dim.y);
	img.draw(-dim / 2);

	ofPushMatrix();
		ofSetColor(255, 255, 255, 255 * (1 - spool));
		ofTranslate(glm::vec2(0.0f, 10.0f));
		ofRotate(rotorSpin);
		rotor1_img.draw(-rotordim * 0.5f);
	ofPopMatrix();

	if (spool > 0.5f)
	{
		ofSetColor(255, 255, 255, 255 * (spool-0.5f)*2);
		rotor.draw(-rotor.getSize() *0.5f + glm::vec2(0.0f, 10.0f));
	}
	ofSetColor(ofColor::white);
	ofPopMatrix();
}

void introHeliSprite::startUp() { start = true; rotor_wash->start(); main.play(); }

introHeliSprite::~introHeliSprite()
{
	wash_sys->setLifetime(6.0f);
	delete rotor_wash;

}