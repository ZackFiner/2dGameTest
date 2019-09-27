#pragma once
#include "entityManager.h"
#include "entity.h"

class emitter :public entity
{
protected:
public:
	emitter(entityManager*);
	void draw();
};