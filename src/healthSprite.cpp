#include "healthSprite.h"
#include "heliSprite.h"
/*H******************************************************************
 * FILENAME: healthSprite.cpp
 * AUTHOR: Zackary Finer
 * DATE: 10/27/2019
 *
 * DESCRIPTION:
 * healthSprite is essentially a health pack for the player. It will
 * be dropped at random when enemies die, moving down the screen
 * until the player eventually runs into it (where it will boost their
 * health by a certain amount), or it reaches the boundry of the play
 * area (where it will be deleted).
 *
 ********************************************************************/

StaticPackResources& stuff()
{
	static StaticPackResources* deep_stuff = new StaticPackResources();
	return *deep_stuff;
}

healthPack::healthPack(entityManager* em, collisionManager* cm, const glm::vec2& start) :
	solidEntity(em, cm, collisionHull())
{
	this->setPos(start);
	dim = glm::vec2(40, 40);
	hitBox.setBB(glm::vec2(10, 10), glm::vec2(-10, 10), glm::vec2(-10, -10), glm::vec2(10, -10));
}

void healthPack::update() {
	this->setPos(this->getPos() - glm::vec2(0, GAME_SCROLL_RATE)*ofGetLastFrameTime());
	
	auto hits = this->getCollisions();
	auto playerID = manager->getPlayer();
	for (auto hitEnt : hits)
	{
		if (hitEnt->getID() == playerID)
		{
			heliSprite* player = (heliSprite*)hitEnt;
			player->setHealth(glm::min(100, player->getHealth() + HEALTH_PACK_AMNT));
			dead = true;
			std::stringstream ss;
			ss << "+" << HEALTH_PACK_AMNT << " HP";
			auto notif = new popupNotification(ss.str(), 1.0f, position, 30.0f);
			notif->setColor(ofColor::green);
			manager->display->addNotification((onScreenNotification*)notif);
			break;
		}
	}

	if (glm::abs(getPos().x) > (ofGetWidth() / 2 + DESPAWN_RADIUS) || glm::abs(getPos().y) > (ofGetHeight() / 2 + DESPAWN_RADIUS))
		dead = true;
}

bool healthPack::isDead() const {
	return solidEntity::isDead() || dead;
}

void healthPack::draw() {
	ofPushMatrix();
	ofTranslate(getPos() - dim / 2);
	ofRotate(getRot());
	ofSetColor(ofColor::white);
	
	stuff().sprite.draw(glm::vec2(0,0));
	
	ofPopMatrix();
}

int healthPack::getHealth() const { return 1; }