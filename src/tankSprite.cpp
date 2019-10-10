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
	solidEntity(em, cm, collisionHull()),
	img("T90.png")
{
	turretRot = 0.0f;
	hp = TANK_DEFAULT_HP;
	lifetime = TANK_LIFETIME;
	pathManager = manager;
	update();
	img.resize(70, 70);
	img.mirror(true, false);
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
	ofSetColor(ofColor::white);
	ofRotate(this->getRot());
	//ofSetColor(ofColor::blueViolet);
	//ofDrawRectangle(-dim / 2, dim.x, dim.y);
	//ofScale(glm::vec3(70.0f/512.0f,70.0f/512.0f,1));
	img.drawSubsection(-16, -30, 33, 49, 2, 8);
	
	ofPushMatrix();
		
		ofTranslate(glm::vec2(0,-5));
		ofRotate(this->turretRot);
		ofTranslate(glm::vec2(0,7));
		img.drawSubsection(-13, -29, 26, 58, 39, 0);
	
		ofPopMatrix();
	
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
	turretRot = -getRot(); // point the turrets forward for now
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