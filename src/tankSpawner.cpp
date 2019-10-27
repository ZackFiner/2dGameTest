#include "tankSpawner.h"
#include "TankSprite.h"
/*H******************************************************************
 * FILENAME: tankSpawner.cpp
 * AUTHOR: Zackary Finer
 * DATE: 10/26/2019
 *
 * DESCRIPTION:
 * The tank spawner is a specialized type of sprite emitter which
 * dynamically creates "tank" entities. It does this by creating
 * them on either side of the play screen and intializing them
 * to move to the other side of the screen.
 *
 ********************************************************************/
tankSpawner::tankSpawner(entityManager* em, collisionManager* cm) :
	emitter(em)
{
	hitManager = cm;
}

void tankSpawner::update()
{
	unsigned long cur = ofGetCurrentTime().getAsMilliseconds();
	if (cur - last_spawn > (spawnRate*1000.0f))
	{
		bool on_left_side = ofRandomuf() > 0.5f;
		bool linear = ofRandomuf() > 0.5f;
		if (linear)
			new tankSprite(manager, hitManager,
				new linearPath(
					glm::vec2(-600 * (on_left_side ? -1 : 1), 200),
					glm::normalize(glm::vec2(600 * (on_left_side ? -1 : 1), ofRandom(-50.0f, 50.0f))), 
					ofRandom(200.0f, 300.0f))
				);
		else
			new tankSprite(manager, hitManager,
				new sinPath(ofRandom(5.0f,50.0f), 100.0f, ofRandom(50.0f,150.0f), ofRandom(150.0f,250.0f), glm::vec2(-600*(on_left_side ? -1 : 1), 200), on_left_side));


		last_spawn = cur;
	}
	

}

void tankSpawner::setSpawnRate(float rate)
{
	spawnRate = rate;
}