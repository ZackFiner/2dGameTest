#pragma once
#include "solidEntity.h"
#include "emitter.h"
#include "projectileEmitter.h"
class heliSprite : public solidEntity
{
	int health = 100;
	projectileEmitter gun;
	glm::vec2 cont, vel;
	float angAcc, angV;
public:
	heliSprite(entityManager*, collisionManager*);
	void draw();
	bool isDead() const;
	void update();
	int getHealth() const;
	void setHealth(int);
	void handleKeyInput(int);
	void handleKeyRelease(int);
};