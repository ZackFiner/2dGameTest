#pragma once
#include "solidEntity.h"
#include "projectileEmitter.h"
class heliSprite : public solidEntity
{
	int health = 100;
	projectileEmitter gun;
public:
	heliSprite(entityManager*, collisionManager*);
	void draw() const;
	bool isDead() const;
	void update();
	int getHealth() const;
	void setHealth(int);
	void handleInput();
};