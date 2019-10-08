#pragma once
#include "solidEntity.h"
#include "motionPath.h"

#define TANK_DEFAULT_HP 100
#define TANK_LIFETIME 20.0f
#define TANK_POINTS 20
class tankSprite : public solidEntity
{
	motionPath* pathManager;
	int hp;
	bool dead = false;
	glm::vec2 vel;
public:
	tankSprite(entityManager*, collisionManager*, motionPath*);
	void update();
	void draw() const;
	bool isDead() const;
	glm::vec2 getVelocity() const;
	void setHealth(int);
	int getHealth() const;
	int getPoints() const;
	~tankSprite();
};