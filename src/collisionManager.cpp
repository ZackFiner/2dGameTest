#include "collisionManager.h"

collisionManager::collisionManager()
{
}

void collisionManager::addEntity(collisionHull* obj)
{
	broadPhaseDetector.addEntry(obj);
}

void collisionManager::removeEntity(collisionHull* obj)
{
	broadPhaseDetector.removeEntry(obj);
}