#pragma once
#include "entity.h"
#include "collisionHull.h"
#include "collisionManager.h"

class solidEntity : public entity
{
protected:
	collisionManager * hitManager;
	collisionHull hitBox;
	std::vector<entity*> getCollisions();
public:
	solidEntity(entityManager*, collisionManager*, collisionHull);
	void update();
	void draw() const;
	~solidEntity();
};