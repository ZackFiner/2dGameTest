#pragma once
#include "emitter.h"

class projectileEmitter : public emitter
{
	float frequency;
	glm::vec3 dir;
public:
	projectileEmitter(entityManager*);
};