#include "heliSprite.h"

/*H******************************************************************
 * FILENAME: heliSprite.cpp
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

#define ACCEL_RATE 0.1f
#define DECEL_RATE 0.05f

heliSprite::heliSprite(entityManager* em, collisionManager* cm) :
	solidEntity(em, cm, collisionHull()),
	img("ah64.png"),
	rotor("rotor_sheet.png", 50.0f, glm::vec2(106.0f,106.0f), glm::vec2(364,364), 4)
{
	gun = new projectileEmitter(em, cm);
	gun->setSpeed(20.0f);
	gun->setParent((entity*)this);
	gun->setDir(glm::vec2(0.0f, 1.0f));
	gun->setPos(glm::vec2(0.0f, 50.0f));
	dim = glm::vec2(150.0f, 150.0f);
	img.resize(dim.x, dim.y);
	img.mirror(true, false);
	/*
	main.load("rotor_loop.wav");
	main.setVolume(0.2f);
	main.setLoop(true);
	main.play();
	whine.load("whine_loop.wav");
	whine.setVolume(0.2f);
	whine.setLoop(true);
	whine.play();
	*/
}

void heliSprite::draw()
{
	ofPushMatrix();
	ofTranslate(position);
	ofRotate(rot);
	//draw
	//ofDrawRectangle(-dim/2, dim.x,dim.y);
	img.draw(-dim / 2);
	rotor.draw(-rotor.getSize()/2 + glm::vec2(0.0f, 10.0f));
	ofPopMatrix();
}

bool heliSprite::isDead() const
{
	return health <= 0;
}

void heliSprite::update()
{
	rotor.update();
	solidEntity::update();
	float dT = ofGetLastFrameTime()*VEL_TIME_CONST;
	if (abs(f) > 0.0f || abs(b) > 0.0f)
		vel.y = glm::clamp(vel.y + (f - b)*ACCEL_RATE*dT, -5.0f, 5.0f);
	else
		vel.y -= vel.y*DECEL_RATE;

	if (abs(l) > 0.0f || abs(r) > 0.0f)
		vel.x = glm::clamp(vel.x + (l - r)*ACCEL_RATE*dT, -5.0f, 5.0f);
	else
		vel.x -= vel.x*DECEL_RATE;

	whine.setSpeed(1+(glm::fastLength(vel)/5.0f)*0.2f);
	glm::vec2 front = glm::normalize(vel + glm::vec2(0, 15.0f));
	float theta = glm::degrees(glm::orientedAngle(glm::vec2(0.0f, 1.0f),front));
	if (updateCannon)
		gun->setDir(front);
	//std::cout << vel << std::endl;
	//std::cout << cont << std::endl;
	//std::cout << getPos() << std::endl;
	glm::vec2 scrnDim = glm::vec2(ofGetWidth(), ofGetHeight());
	glm::vec2 newPos = glm::clamp(vel*dT + position, -scrnDim / 2, glm::vec2(scrnDim.x/2, 0.0f));
	setPos(newPos);
	setRot(theta);
}

int heliSprite::getHealth() const { return health; }
void heliSprite::setHealth(int _health) { health = _health; }
glm::vec2 heliSprite::getVelocity() const
{
	return vel;
}
void heliSprite::handleKeyInput(int key)
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

void heliSprite::handleKeyRelease(int key)
{
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
heliSprite::~heliSprite()
{

}