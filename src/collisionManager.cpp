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
void collisionManager::update()
{
	broadPhaseDetector.update();
}

void collisionManager::drawDebug()
{
	broadPhaseDetector.drawDebug();
}

std::vector<collisionHull*> collisionManager::queryCollision(collisionHull* obj)
{
	return broadPhaseDetector.queryCollision(obj);
}