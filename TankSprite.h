#pragma once
#include "solidEntity.h"
#include "motionPath.h"
class tankSprite : public solidEntity
{
	bool isDead();
public:
	tankSprite(entityManager*, collisionManager*, motionPath);
	void update();
	void draw() const;
	bool isDead() const;
	glm::vec2 getVelocity() const;
};