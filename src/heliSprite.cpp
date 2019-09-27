#include "heliSprite.h"
#define DECEL_RATE 0.1f
heliSprite::heliSprite(entityManager* em, collisionManager* cm) :
	solidEntity(em, cm, collisionHull()),
	gun(em)
{
	gun.setParent((entity*)this);
}

void heliSprite::draw()
{
	ofPushMatrix();
	ofTranslate(position);
	ofRotate(rot);
	//draw
	glm::vec2 dim = glm::vec2(50.0f, 50.0f);
	ofDrawRectangle(dim/2, dim.x,dim.y);
	ofPopMatrix();
}

bool heliSprite::isDead() const
{
	return health <= 0;
}

void heliSprite::update()
{
	solidEntity::update();
	
	if (glm::abs(cont.x) < 0.9f && glm::abs(vel.x) > 0.0f)
	{
		vel.x = glm::clamp(vel.x - DECEL_RATE * glm::sign(vel.x), 0.0f, 10* glm::sign(vel.x));
	}
	else
	{
		vel.x = cont.x;
	}
	if (abs(cont.y) < 0.9f && abs(vel.y) > 0.0f)
	{
		vel.y = glm::clamp(vel.y - DECEL_RATE * glm::sign(vel.y), 0.0f, 10 * glm::sign(vel.y));
	}
	else
	{
		vel.y = cont.y;
	}
	glm::vec2 scrnDim = glm::vec2(ofGetScreenWidth(), ofGetScreenHeight());
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
		cont += glm::vec2(1.0f, 0.0f);
		break;
	case 's':
	case 'S':
		cont += glm::vec2(-1.0f, 0.0f);
		break;
	case 'a':
	case 'A':
		cont += glm::vec2(0.0f, 1.0f);
		break;
	case 'd':
	case 'D':
		cont += glm::vec2(0.0f, -1.0f);
		break;
	}
}

void heliSprite::handleKeyRelease(int key)
{
	switch (key)
	{
	case 'w':
	case 'W':
		cont -= glm::vec2(1.0f, 0.0f);
		break;
	case 's':
	case 'S':
		cont -= glm::vec2(-1.0f, 0.0f);
		break;
	case 'a':
	case 'A':
		cont -= glm::vec2(0.0f, 1.0f);
		break;
	case 'd':
	case 'D':
		cont -= glm::vec2(0.0f, -1.0f);
		break;
	}
}