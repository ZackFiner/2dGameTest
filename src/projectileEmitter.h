#pragma once
#include "emitter.h"

class projectileEmitter : public emitter
{
	float frequency = 100.0f;//ms between shots
	float speed = 5.0f;
	float lstF = 0.0f;
	bool fire = false;
	glm::vec2 dir;
public:
	projectileEmitter(entityManager*);
	void setDir(const glm::vec2&);
	void toggleFire(bool);
	void fireOne();
	void update();
	void setFireRate(float);
	void setSpeed(float);
};