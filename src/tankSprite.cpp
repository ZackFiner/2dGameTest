#include "TankSprite.h"
#include "motionPath.h"


tankSprite::tankSprite(entityManager* em, collisionManager* cm, motionPath* manager) :
	solidEntity(em, cm, collisionHull())
{
	hp = TANK_DEFAULT_HP;
	lifetime = TANK_LIFETIME;
	pathManager = manager;
}

void tankSprite::draw() const
{
	ofPushMatrix();
	ofTranslate(this->getPos());
	ofRotate(this->getRot());
	glm::vec2 dim = glm::vec2(20, 50);
	ofSetColor(ofColor::blueViolet);
	ofDrawRectangle(-dim / 2, dim.x, dim.y);
	ofPopMatrix();
}
void tankSprite::update()
{
	solidEntity::update();
	dead = hp < 0;
	setPos(pathManager->getPos(getAge()));
	setRot(pathManager->getRot(getAge()));
	vel = pathManager->getPos(getAge() + ofGetLastFrameTime()) - getPos();

}

bool tankSprite::isDead() const
{
	return dead || solidEntity::isDead();
}

glm::vec2 tankSprite::getVelocity() const
{
	return vel;
}

void tankSprite::setHealth(int _hp) { hp = _hp; }
int tankSprite::getHealth() const { return hp; }

int tankSprite::getPoints() const { return TANK_POINTS; }
tankSprite::~tankSprite()
{
	delete pathManager;
}