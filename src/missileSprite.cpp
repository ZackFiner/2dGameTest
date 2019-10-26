#include "missileSprite.h"
#include "entityManager.h"
/*H******************************************************************
 * FILENAME: missileSprite.cpp
 * AUTHOR: Zackary Finer
 * DATE: 10/26/2019
 *
 * DESCRIPTION:
 * missileSprite is what is sounds like: a sprite for a missile.
 * it is an entity with an image associated with it, that moves through
 * space along a straight line (however, i make change the "straight
 * line" part of this).
 *
 * Right now, this entity is non-solid, meaning it will not have any
 * presence in collision detection calculations. However, I plan
 * to change this soon.
 *
 ********************************************************************/


missile::missile(entityManager* em,collisionManager* cm, const glm::vec2& origin, const glm::vec2& vel, EID _shotFrom)
	: solidEntity(em, cm, collisionHull()),
	img("bullet.png")
{
	shotFrom = _shotFrom;
	if (manager->getSprite(shotFrom) != nullptr)
		this->team = manager->getSprite(shotFrom)->getTeam();
	else
		this->team = TEAM_2;
	setPos(origin);
	float theta = glm::orientedAngle(glm::vec2(0.0, 1.0f), glm::normalize(vel));
	setRot(glm::degrees(glm::orientedAngle(glm::vec2(0.0,1.0f), glm::normalize(vel)))); // point the missile towards it's target
	velocity = vel;
	lifetime = MISSILE_LIFETIME;
	dim = glm::vec2(32.0f, 128.0f);
	hitBox.setBB(glm::vec2(-5,-20), glm::vec2(5,-20), glm::vec2(5,20), glm::vec2(-5,20));
	img.mirror(true, false);
	img.resize(dim.x, dim.y);
}

void missile::draw()
{
	ofPushMatrix();
	ofTranslate(getPos());
	ofRotate(getRot());
	img.draw(-dim / 2);
	ofPopMatrix();
}

void missile::update()
{
	auto hits = getCollisions();
	if (hits.size() > 0)
	{
		int score_gained = 0;
		for (auto hit : hits)
		{
			if (hit->getCollisionType() == COLLISION_TYPE_SOLID && hit->getTeam() != getTeam()) {
				hit->setHealth(hit->getHealth() - dmg);//if we hit multiple objects, disperse the damage amongst all of them
				if (hit->getHealth() <= 0) // if we killed it.
				{
					score_gained += hit->getPoints();
					if (manager->getSprite(shotFrom) != nullptr)
						manager->getSprite(shotFrom)->setScore(hit->getPoints());
				}
				dead = true; //we blew up
			}
		}
		if (dead) return; //terminate, don't waste any more time updating dead missiles
	}

	float dT = ofGetLastFrameTime();
	auto dim = glm::vec2(ofGetWidth(), ofGetHeight());
	auto pos = getPos();
	dead = glm::abs(pos.x) > dim.x / 2 || glm::abs(pos.y) > dim.y / 2; // delete if we're out of screen range
	entity::update();
	setPos(getPos() + velocity*dT*VEL_TIME_CONST);
}

bool missile::isDead() const
{
	return entity::isDead() || dead;
}

glm::vec2 missile::getVelocity() const
{
	return velocity * VEL_TIME_CONST;
}

int missile::getTeam() const {
	return team;
}
void missile::setDamage(int amnt) { dmg = amnt; }
int missile::getCollisionType() const {
	return COLLISION_TYPE_HOLLOW;
}