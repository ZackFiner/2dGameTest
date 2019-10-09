#include "tankSpawner.h"
#include "TankSprite.h"

tankSpawner::tankSpawner(entityManager* em, collisionManager* cm) :
	emitter(em)
{
	hitManager = cm;
}

void tankSpawner::update()
{
	long cur = ofGetSystemTimeMillis();
	if (cur - last_spawn > (spawnRate*1000.0f))
	{
		
		new tankSprite(manager, hitManager,
			new sinPath(100.0f, 100.0f, 50.0f, 10.0f, glm::vec2(200,200), false));
	}
	
	
	last_spawn = cur;

}