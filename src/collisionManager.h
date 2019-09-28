#pragma once
#include "quadTree.h"
#include "collisionHull.h"
/*H******************************************************************
 * FILENAME: collisionManager.h
 * AUTHOR: Zackary Finer
 *
 * DESCRIPTION:
 * collisionManager serves as a wrapper interface for collision
 * management systems. This way, I can experiment with different
 * collision detection techniques without needing to re-write
 * my entire code base.
 *
 ********************************************************************/
class collisionManager
{
public:
	virtual void addEntity(collisionHull*)= 0;
	virtual void removeEntity(collisionHull*) = 0;
	virtual void update() = 0;
	virtual void drawDebug() = 0;
	virtual std::vector<collisionHull*> queryCollision(collisionHull*) = 0;
};

class quadTreeCollisionManager : public collisionManager
{
private:
	masterQuad broadPhaseDetector;
public:
	quadTreeCollisionManager();
	void addEntity(collisionHull*);
	void removeEntity(collisionHull*);
	void update();
	void drawDebug();
	std::vector<collisionHull*> queryCollision(collisionHull*);
};