#pragma once
#include "solidEntity.h"
#include "GameSettings.h"
/*H******************************************************************
 * FILENAME: healthSprite.h
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

class StaticPackResources
{
public:
	ofImage sprite;
	StaticPackResources()
	{
		sprite = ofImage();
		sprite.load("hp_box.png");
		sprite.mirror(true, false);
		sprite.resize(40, 40);
	}
};

class healthPack : public solidEntity
{
	glm::vec2 dim;
	bool dead = false;
public:
	healthPack(entityManager* em, collisionManager* cm, const glm::vec2& start);
	void update();
	void draw();
	bool isDead() const;
};