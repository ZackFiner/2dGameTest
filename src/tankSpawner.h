#pragma once
#include "emitter.h"
#include "collisionManager.h"

#define DEFAULT_SPAWN_RATE 1.0f

/*H******************************************************************
 * FILENAME: tankSpawner.h
 * AUTHOR: Zackary Finer
 * DATE: 10/26/2019
 *
 * DESCRIPTION:
 * The tank spawner is a specialized type of sprite emitter which
 * dynamically creates "tank" entities. It does this by creating
 * them on either side of the play screen and intializing them
 * to move to the other side of the screen.
 *
 *
 ********************************************************************/

class tankSpawner : public emitter
{
	float spawnRate = DEFAULT_SPAWN_RATE;
	unsigned long last_spawn;
	collisionManager* hitManager;
	bool spawn = false;
public:
	tankSpawner(entityManager* em, collisionManager* cm);
	void setSpawnRate(float);
	void update();
	void start();
	void stop();
	bool getRunning() const;
};