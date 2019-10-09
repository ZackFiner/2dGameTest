#include "TankSprite.h"
#include "motionPath.h"

/*H******************************************************************
 * FILENAME: tankSprite.cpp
 * AUTHOR: Zackary Finer
 *
 * DESCRIPTION:
 *
 *
 ********************************************************************/

tankSprite::tankSprite(entityManager* em, collisionManager* cm, motionPath* manager) :
	solidEntity(em, cm, collisionHull())
{
	hp = TANK_DEFAULT_HP;
	lifetime = TANK_LIFETIME;
	pathManager = manager;
	update();
}

void tankSprite::draw()
{

	glm::vec2 dim = glm::vec2(20, 50);
	ofPushMatrix();
	ofTranslate(this->getPos());
	ofSetColor(ofColor::red);
	ofDrawRectangle(glm::vec2(-25.0f, -50.0f), 50.0f, 4.0f);
	ofSetColor(ofColor::green);
	ofDrawRectangle(glm::vec2(-25.0f, -50.0f), 50.0f*((float)getHealth() / TANK_DEFAULT_HP), 4.0f);
	ofRotate(this->getRot());
	ofSetColor(ofColor::blueViolet);
	ofDrawRectangle(-dim / 2, dim.x, dim.y);
	ofSetColor(ofColor::white);
	ofPopMatrix();
}
void tankSprite::update()
{
	solidEntity::update();
	dead = hp <= 0;
	setPos(pathManager->getPos(getAge()));
	setRot(glm::degrees(pathManager->getRot(getAge())));
	vel = pathManager->getPos(getAge() + ofGetLastFrameTime()) - getPos();
	auto border = glm::vec2(ofGetWidth(), ofGetHeight());
	if (glm::abs(getPos().x) > (border.x / 2 + DESPAWN_RADIUS) || glm::abs(getPos().y) > (border.y / 2 + DESPAWN_RADIUS))
		dead = true;
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