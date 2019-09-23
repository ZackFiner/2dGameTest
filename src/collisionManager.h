#pragma once
#include "quadTree.h"
#include "collisionHull.h"
class collisionManager
{
private:
	masterQuad broadPhaseDetector;
public:
	collisionManager();
	void addEntity(collisionHull*);
	void removeEntity(collisionHull*);
	void update();
	void drawDebug();

};