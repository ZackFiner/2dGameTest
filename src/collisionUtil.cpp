#include "collisionUtil.h"
#include "collisionHull.h"

/*H******************************************************************
 * FILENAME: collisionUtil.cpp
 * AUTHOR: Zackary Finer
 *
 * DESCRIPTION:
 * This file contains definitions for methods used to detect
 * collisions between objects. It contains various methods for
 * detecting whether two objects are colliding.
 */

bool collisionUtil::AABBIntersect(const glm::vec2& topCorner, const glm::vec2& bottomCorner, collisionHull* obj)
{

	/*
	This problem can be simplified by inspecting intersection by axis.

	An AABB is essentially a range of numbers along spatial axis representing a volume
	As such, if two AABBs are intersecting, then the ranges established by their width and height
	(and length if we're in 3 dimensions) must overlap.

	Thus, to test whether two AABBs intersect, we simply test to see if these ranges
	overlap.

	NW_Corner & topCorner represent the maxes for each range
	SE_Corner & bottomCorner represent the mins.

	consider two ranges (a,b) and (c,d)
	these intersect if:
	b >= c (b is infront of c, or c is behind b or equal) and 
	d >= a (d is indeed infront of a or equal)
	now just apply this same logic to our aabb along each axis:
	*/
	AABB aabb = obj->getAABB();
	return  aabb.NW_Corner.x >= bottomCorner.x &&
			aabb.SE_Corner.x <= topCorner.x &&
			aabb.NW_Corner.y >= bottomCorner.y &&
			aabb.SE_Corner.y <= topCorner.y;
}

bool collisionUtil::AABBIntersect(collisionHull* target, collisionHull* obj)
{
	// two AABB intersect if at least one of their edges passes through the other
	AABB aabb = target->getAABB();
	return AABBIntersect(aabb.NW_Corner, aabb.SE_Corner, obj);
}

bool collisionUtil::sphereIntersect(const glm::vec2& orig1, float r1, const glm::vec2& orig2, float r2)
{
	glm::vec2 diff = orig1 - orig2;
	float sqrDst = glm::dot(diff, diff);
	float minSafeDistSqr = (r1 + r2)*(r1 + r2);
	return sqrDst <= minSafeDistSqr;
}