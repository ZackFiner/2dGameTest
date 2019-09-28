#pragma once
#include "entity.h"
class missile : public entity
{
	bool dead = false;
	glm::vec2 velocity;
	glm::vec2 dim;
	ofImage img;
public:
	/*
	manager, origin, velocity
	*/
	missile(entityManager*, const glm::vec2&, const glm::vec2&);
	void draw();
	void update(); //right now, travels to the edge of the screen and dies
	bool isDead() const;
	glm::vec2 getVelocity() const;
};