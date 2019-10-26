#include "TankSprite.h"
#include "motionPath.h"

/*H******************************************************************
 * FILENAME: tankSprite.cpp
 * AUTHOR: Zackary Finer
 * DATE: 10/26/2019
 *
 * DESCRIPTION:
 * Tank's are one of the basic entities in the game. They follow
 * a predetermined path of movement, and are spawned by a tank
 * -spawner. They shoot projectiles down towards the player at
 * random intervals.
 *
 ********************************************************************/

tankSprite::tankSprite(entityManager* em, collisionManager* cm, motionPath* manager) :
	solidEntity(em, cm, collisionHull()),
	img("T90.png")
{
	gun = new projectileEmitter(em, cm);
	gun->setSpeed(5.0f);
	gun->setParent((entity*)this);
	gun->setDir(glm::vec2(0.0f,1.0f));
	gun->setPos(glm::vec2(0.0f, 7.0f));
	gun->setFireRate(500.0f);
	gun->setDamage(5);
	gun->setRandomFire(true);
	gun->toggleFire(true);
	turretRot = 0.0f;

	hp = TANK_DEFAULT_HP;
	lifetime = TANK_LIFETIME;
	pathManager = manager;
	update();
	setPos(pathManager->getPos(getAge()));
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
	vel = pathManager->getPos(getAge() + ofGetLastFrameTime()) - pathManager->getPos(getAge());
	setPos(getPos()+vel);

	
	setRot(glm::degrees(pathManager->getRot(getAge())));
	
	auto border = glm::vec2(ofGetWidth(), ofGetHeight());
	
	turretRot = 180-getRot(); // point the turrets forward for now
	gun->setDir(glm::rotate(glm::vec2(0.0f, 1.0f), glm::radians(turretRot+getRot())));
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
	manager->deleteSprite(gun->getID());
}

int tankSprite::getTeam() const { return TEAM_1; }