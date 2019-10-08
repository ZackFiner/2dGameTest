#pragma once
#include "ofMain.h"
/*H******************************************************************
 * FILENAME: collisionUtil.h
 * AUTHOR: Zackary Finer
 *
 * DESCRIPTION:
 * This file contains declerations for methods used to detect
 * collisions between objects. It contains various methods for
 * detecting whether two objects are colliding.
 */
class collisionHull;
namespace collisionUtil
{
	bool AABBIntersect(const glm::vec2&, const glm::vec2&, collisionHull*);
	bool AABBIntersect(collisionHull*, collisionHull*);
	bool sphereIntersect(const glm::vec2&, float, const glm::vec2&, float);
}