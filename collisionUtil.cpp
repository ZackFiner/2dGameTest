#include "collisionUtil.h"
#include "collisionHull.h"
bool collisionUtil::AABBIntersect(const glm::vec2& topCorner, const glm::vec2& bottomCorner, collisionHull* obj)
{
	// two AABB intersect if at least one of their edges passes through the other
	AABB aabb = obj->getAABB();
	return  aabb.NW_Corner.x >= bottomCorner.x && //make sure their max x is higher than our min x
		aabb.NW_Corner.y >= bottomCorner.y && //make sure their max y is higher than our min y
		aabb.SE_Corner.x <= topCorner.x && //make sure their min x is less than our max x
		aabb.SE_Corner.y <= topCorner.y; //make sure our min y is less than our max
}

bool collisionUtil::AABBIntersect(collisionHull* target, collisionHull* obj)
{
	// two AABB intersect if at least one of their edges passes through the other
	AABB aabb = target->getAABB();
	return AABBIntersect(aabb.NW_Corner, aabb.SE_Corner, obj);
}