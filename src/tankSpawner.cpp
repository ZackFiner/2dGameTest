#include "tankSpawner.h"
#include "TankSprite.h"
#include "GameSettings.h"
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

void tankSpawner::spawnTank()
{
	glm::vec2 border = glm::vec2(ofGetWidth(), ofGetHeight());
	int spawnWidth = border.x / 2 + DESPAWN_RADIUS / 2;
	int medianSpawnHeight = border.y / 4;

	bool on_left_side = ofRandomuf() > 0.5f;
	bool linear = ofRandomuf() > 0.5f;
	if (linear)
		new tankSprite(manager, hitManager,
			new linearPath(
				glm::vec2(-spawnWidth * (on_left_side ? -1 : 1), medianSpawnHeight),
				glm::normalize(glm::vec2(spawnWidth * (on_left_side ? -1 : 1), ofRandom(-50.0f, 50.0f))),
				ofRandom(medianSpawnHeight, medianSpawnHeight*1.5))
		);
	else
		new tankSprite(manager, hitManager,
			new sinPath(ofRandom(5.0f, 50.0f), 100.0f, ofRandom(medianSpawnHeight*0.25, medianSpawnHeight*0.75), ofRandom(medianSpawnHeight*0.75, medianSpawnHeight*1.25), glm::vec2(-spawnWidth * (on_left_side ? -1 : 1), medianSpawnHeight), on_left_side));

}
void tankSpawner::spawnSpaa()
{
	glm::vec2 border = glm::vec2(ofGetWidth(), ofGetHeight());
	int spawnWidth = border.x / 2 + DESPAWN_RADIUS / 2;
	int medianSpawnHeight = border.y / 4;

	bool on_left_side = ofRandomuf() > 0.5f;
	bool linear = ofRandomuf() > 0.5f;
	if (linear)
		new spaaSprite(manager, hitManager,
			new linearPath(
				glm::vec2(-spawnWidth * (on_left_side ? -1 : 1), medianSpawnHeight),
				glm::normalize(glm::vec2(spawnWidth * (on_left_side ? -1 : 1), ofRandom(-50.0f, 50.0f))),
				ofRandom(medianSpawnHeight, medianSpawnHeight*1.5))
		);
	else
		new spaaSprite(manager, hitManager,
			new sinPath(ofRandom(5.0f, 50.0f), 100.0f, ofRandom(medianSpawnHeight*0.25, medianSpawnHeight*0.75), ofRandom(medianSpawnHeight*0.75, medianSpawnHeight*1.25), glm::vec2(-spawnWidth * (on_left_side ? -1 : 1), medianSpawnHeight), on_left_side));

}

void tankSpawner::spawnBatch()
{
	//i found that  when they spawn it batches, the game becomes really difficult really fast
	int amnt = (int)glm::clamp(ofRandom(glm::clamp(dif - 1, 1, 3)) , 1.0f, 3.0f);
	for (int i = 0; i < amnt; i++)
	{
		if (ofRandom(100.0f) < SPAA_SPAWN_CHANCE && dif > 3)
		{
			spawnSpaa();
		}
		else
		{
			spawnTank();
		}
	}
}

void tankSpawner::update()
{
	if (spawn)
	{
		unsigned long cur = ofGetCurrentTime().getAsMilliseconds();
		if (cur - last_spawn > (spawnRate*1000.0f))
		{
			/*Spawn a batch depending the difficulty*/
			spawnBatch();
			last_spawn = cur;
		}
	}

}

void tankSpawner::setSpawnRate(float rate)
{
	spawnRate = rate;
}

void tankSpawner::start()
{
	spawn = true;
}
void tankSpawner::stop()
{
	spawn = false;
}
bool tankSpawner::getRunning() const
{
	return spawn;
}

void tankSpawner::setDifficulty(int dif)
{
	this->dif = dif;
	spawnRate = glm::max(3.0f - (float)dif * 0.05f, 0.5f);
}