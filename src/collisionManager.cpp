#include "collisionManager.h"

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