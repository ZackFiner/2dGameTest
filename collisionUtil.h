#pragma once
#include "ofMain.h"

class collisionHull;
namespace collisionUtil
{
	bool AABBIntersect(const glm::vec2&, const glm::vec2&, collisionHull*);
	bool AABBIntersect(collisionHull*, collisionHull*);
}