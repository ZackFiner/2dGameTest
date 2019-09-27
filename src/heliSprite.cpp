#include "heliSprite.h"
#define DECEL_RATE 0.1f
heliSprite::heliSprite(entityManager* em, collisionManager* cm) :
	solidEntity(em, cm, collisionHull())
{
	gun = new projectileEmitter(em);
	gun->setParent((entity*)this);
	gun->setDir(glm::vec2(0.0f, 1.0f));
}

void heliSprite::draw()
{
	ofPushMatrix();
	ofTranslate(position);
	ofRotate(rot);
	//draw
	glm::vec2 dim = glm::vec2(50.0f, 50.0f);
	ofDrawRectangle(-dim/2, dim.x,dim.y);
	ofPopMatrix();
}

bool heliSprite::isDead() const
{
	return health <= 0;
}

void heliSprite::update()
{
	solidEntity::update();
	
	/*if (glm::abs(cont.x) < 0.9f && glm::abs(vel.x) > 0.0f)
	{
		vel.x = vel.x - DECEL_RATE * glm::sign(vel.x);
	}*/
	//else
	{
		vel.x = l-r;
	}
	/*if (abs(cont.y) < 0.9f && abs(vel.y) > 0.0f)
	{
		vel.y = vel.y - DECEL_RATE * glm::sign(vel.y);
	}*/
	//else
	{
		vel.y = f-b;
	}
	//std::cout << vel << std::endl;
	//std::cout << cont << std::endl;
	//std::cout << getPos() << std::endl;
	glm::vec2 scrnDim = glm::vec2(ofGetWidth(), ofGetHeight());
	glm::vec2 newPos = glm::clamp(vel + position, -scrnDim / 2, scrnDim / 2);
	setPos(newPos);

}

int heliSprite::getHealth() const { return health; }
void heliSprite::setHealth(int _health) { health = _health; }

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

heliSprite::~heliSprite()
{

}