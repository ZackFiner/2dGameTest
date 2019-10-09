#pragma once
#include "emitter.h"
#include "collisionManager.h"

#define DEFAULT_SPAWN_RATE 1.0f
class tankSpawner : public emitter
{
	float spawnRate = DEFAULT_SPAWN_RATE;
	long last_spawn;
	collisionManager* hitManager;
public:
	tankSpawner(entityManager* em, collisionManager* cm);
	void update();
};