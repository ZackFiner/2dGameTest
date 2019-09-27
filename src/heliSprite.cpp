#include "heliSprite.h"
#define ACCEL_RATE 0.5f
#define DECEL_RATE 0.05f
heliSprite::heliSprite(entityManager* em, collisionManager* cm) :
	solidEntity(em, cm, collisionHull()),
	img("ah64.png")
{
	gun = new projectileEmitter(em);
	gun->setSpeed(20.0f);
	gun->setParent((entity*)this);
	gun->setDir(glm::vec2(0.0f, 1.0f));
	gun->setPos(glm::vec2(0.0f, 50.0f));
	dim = glm::vec2(150.0f, 150.0f);
	img.resize(dim.x, dim.y);
	img.mirror(true, false);
}

void heliSprite::draw()
{
	ofPushMatrix();
	ofTranslate(position);
	ofRotate(rot);
	//draw
	//ofDrawRectangle(-dim/2, dim.x,dim.y);
	img.draw(-dim / 2);
	ofPopMatrix();
}

bool heliSprite::isDead() const
{
	return health <= 0;
}

void heliSprite::update()
{
	solidEntity::update();
	
	if (abs(f) > 0.0f || abs(b) > 0.0f)
		vel.y = glm::clamp(vel.y + (f - b)*ACCEL_RATE, -5.0f, 5.0f);
	else
		vel.y -= vel.y*DECEL_RATE;

	if (abs(l) > 0.0f || abs(r) > 0.0f)
		vel.x = glm::clamp(vel.x + (l - r)*ACCEL_RATE, -5.0f, 5.0f);
	else
		vel.x -= vel.x*DECEL_RATE;


	glm::vec2 front = glm::normalize(vel + glm::vec2(0, 15.0f));
	float theta = glm::degrees(glm::orientedAngle(glm::vec2(0.0f, 1.0f),front));
	gun->setDir(front);
	//std::cout << vel << std::endl;
	//std::cout << cont << std::endl;
	//std::cout << getPos() << std::endl;
	glm::vec2 scrnDim = glm::vec2(ofGetWidth(), ofGetHeight());
	glm::vec2 newPos = glm::clamp(vel + position, -scrnDim / 2, scrnDim / 2);
	setPos(newPos);
	setRot(theta);
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