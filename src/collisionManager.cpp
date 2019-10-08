#include "collisionManager.h"
#include "entity.h"
#include "collisionUtil.h"
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


simpleCollisionManager::simpleCollisionManager()
{}

void simpleCollisionManager::addEntity(collisionHull* obj)
{
	content.insert_or_assign(obj->owner->getID(), obj);
}

void simpleCollisionManager::removeEntity(collisionHull* obj)
{
	if (content.find(obj->owner->getID()) != content.end())
		content.erase(obj->owner->getID());
}

void simpleCollisionManager::update()
{/*No processing here, this is a simple collision manager*/ }

void simpleCollisionManager::drawDebug()
{
	ofSetColor(ofColor::red);
	ofNoFill();
	for (auto pair : content)
	{
		ofDrawCircle(pair.second->getPos(), pair.second->getSweptRadius());
	}
	ofFill();
}

std::vector<collisionHull*> simpleCollisionManager::queryCollision(collisionHull * obj)
{
	/*
	Naieve collision query, O(n^2). We use swept radius (bounding radius + objects velocity)
	*/
	std::vector<collisionHull*> results;
	for (auto iter = content.begin(); iter != content.end(); ++iter)
	{
		if (iter->first == obj->owner->getID())
			continue; // we don't test collision against ourselves

		if (collisionUtil::sphereIntersect(obj->getPos(), obj->getSweptRadius(), iter->second->getPos(), iter->second->getSweptRadius()))
		{
			results.push_back(iter->second);
		}
	}
	return results;
}