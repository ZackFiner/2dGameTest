#include "collisionManager.h"
/*H******************************************************************
 * FILENAME: collisionManager.cpp
 * AUTHOR: Zackary Finer
 *
 * DESCRIPTION:
 * collisionManager serves as a wrapper interface for collision
 * management systems. This way, I can experiment with different
 * collision detection techniques without needing to re-write
 * my entire code base.
 *
 * In here, we can see the implementation of the quadTreeCollision-
 * Manager class, which is really just a wrapper for our quadTree
 * class.
 *
 ********************************************************************/
quadTreeCollisionManager::quadTreeCollisionManager()
{
}

void quadTreeCollisionManager::addEntity(collisionHull* obj)
{
	broadPhaseDetector.addEntry(obj);
}

void quadTreeCollisionManager::removeEntity(collisionHull* obj)
{
	broadPhaseDetector.removeEntry(obj);
}
void quadTreeCollisionManager::update()
{
	broadPhaseDetector.update();
}

void quadTreeCollisionManager::drawDebug()
{
	broadPhaseDetector.drawDebug();
}

std::vector<collisionHull*> quadTreeCollisionManager::queryCollision(collisionHull* obj)
{
	return broadPhaseDetector.queryCollision(obj);
}