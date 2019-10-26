#pragma once
#include "entity.h"
#include "collisionHull.h"
#include "collisionManager.h"

/*H******************************************************************
 * FILENAME: solidEntity.h
 * AUTHOR: Zackary Finer
 * DATE: 10/26/2019
 *
 * DESCRIPTION:
 * This subclass of entity essentially integrates the entity class with
 * the collision management system. As such, solidEntities are considered
 * in collsion detection calculations, and should be used to implement
 * sprites (entities) that can be hit by other entities.
 *
 ********************************************************************/

class solidEntity : public entity
{
protected:
	collisionManager * hitManager;
	collisionHull hitBox;
	std::vector<entity*> getCollisions();
public:
	solidEntity(entityManager*, collisionManager*, collisionHull);
	void update();
	void draw();
	void setPos(const glm::vec2&);
	void setRot(float);
	~solidEntity();
};