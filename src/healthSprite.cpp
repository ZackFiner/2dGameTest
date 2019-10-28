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

healthPack::healthPack(entityManager* em, collisionManager* cm, const glm::vec2& start) :
	solidEntity(em, cm, collisionHull()),
	img("hp_box.png")
{
	this->setPos(start);
	dim = glm::vec2(40, 40);
	hitBox.setBB(glm::vec2(10, 10), glm::vec2(-10, 10), glm::vec2(-10, -10), glm::vec2(10, -10));
	img.mirror(true, false);
	img.resize(dim.x, dim.y);
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
	
	img.draw(glm::vec2(0,0));
	
	ofPopMatrix();
}