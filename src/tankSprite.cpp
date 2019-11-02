#include "TankSprite.h"
#include "motionPath.h"
#include "particleEmitter.h"
#include "healthSprite.h"
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
tankStaticData& getTankStaticData()
{
	static tankStaticData* tankSprite_staticData = new tankStaticData();
	return *tankSprite_staticData;
}


tankSprite::tankSprite(entityManager* em, collisionManager* cm, motionPath* manager) :
	solidEntity(em, cm, collisionHull())//,
	//img("T90.png")
{
	gun = new projectileEmitter(em, cm);
	gun->setSpeed(750.0f);
	gun->setParent((entity*)this);
	gun->setDir(glm::vec2(0.0f,1.0f));
	gun->setPos(glm::vec2(0.0f, 7.0f));
	gun->setFireRate(500.0f);
	gun->setDamage(5);
	gun->setRandomFire(true);
	gun->toggleFire(true);
	gun->setSpread(10.0f);
	turretRot = 0.0f;

	hp = TANK_DEFAULT_HP;
	lifetime = TANK_LIFETIME;
	pathManager = manager;
	update();
	setPos(pathManager->getPos(getAge()));
	//img.resize(70, 70);
	//img.mirror(true, false);
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
	getTankStaticData().tank_sprite.drawSubsection(-16, -30, 33, 49, 2, 8);
	
	ofPushMatrix();
		
		ofTranslate(glm::vec2(0,-5));
		ofRotate(this->turretRot);
		ofTranslate(glm::vec2(0,7));
		getTankStaticData().tank_sprite.drawSubsection(-13, -29, 26, 58, 39, 0);
	
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
	
	auto p = manager->getSprite(manager->getPlayer());
	
	float angToP;
	if (p != nullptr)
		angToP = -glm::degrees(glm::orientedAngle(glm::normalize(p->getPos() - getPos()), glm::vec2(0.0f, 1.0f)));
	else
		angToP = 180.0f;
	
	float newAng = angToP - getRot();
	lastTurretRot = turretRot;
	turretRot = newAng; // stuff and stuff here 

	
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
	if (getHealth() <= 0) {
		particleSystem* explosionSys = new particleSystem();
		explosionSys->initSoundPlay(&(sysStatic().getRandomExplosion()));
		auto e = explosionEmitter(explosionSys, 30, this->getPos());
		explosionSys->setLifetime(6.0f);
		manager->particleSystems.addParticleSystem(explosionSys);
	}
	delete pathManager;
	manager->deleteSprite(gun->getID());

	if (ofRandom(100.0f) < HEALTH_PACK_SPAWN_CHANCE)
	{
		manager->addSprite(new healthPack(manager, hitManager, getPos()));
	}

}

int tankSprite::getTeam() const { return TEAM_1; }

spaaSprite::spaaSprite(entityManager* manager, collisionManager* colMan, motionPath* path) :
	tankSprite(manager, colMan, path)
{
	burst_freq = 1000.0f;
	lst_burst = 0;
	gun->setDoubleBarrelDst(18.0f);
	gun->setFireRate(200.0f);
	gun->setRandomFire(false);
	gun->toggleFire(false);
	gun->setDamage(5);
	gun->setSpread(5.0f);
	
}

void spaaSprite::update() {
	tankSprite::update();
	if (ofGetSystemTimeMillis() - lst_burst > burst_freq)
	{
		gun->toggleFire();
		lst_burst = ofGetSystemTimeMillis();
	}
}

void spaaSprite::draw()
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
	getTankStaticData().spaa_sprite.drawSubsection(-10, -25, 21, 50, 7, 9);

	ofPushMatrix();

	ofTranslate(glm::vec2(0, 0));
	ofRotate(this->turretRot);
	ofTranslate(glm::vec2(0, -2));
	getTankStaticData().spaa_sprite.drawSubsection(-10, -14, 21, 28, 40, 18);

	ofPopMatrix();

	ofSetColor(ofColor::white);
	ofPopMatrix();
}

int spaaSprite::getPoints() const {
	return 50;
}