#pragma once
#include "entity.h"
class missile : public entity
{
	bool isDead = false;
public:
	/*
	manager, origin, velocity
	*/
	missile(entityManager* em, const glm::vec2&, const glm::vec2&);
	void draw();
	void update(); //right now, travels to the edge of the screen and dies
	void isDead();

};