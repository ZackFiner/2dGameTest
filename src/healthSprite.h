#pragma once
#include "solidEntity.h"
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

class healthPack : public solidEntity
{
public:
	healthPack(entityManager* em, collisionManager* cm, const glm::vec2& start);
	void update();
	void draw();
};