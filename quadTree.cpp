#include "quadTree.h"
#include "entity.h"
#include "collisionHull.h"

bool quadTree::testBound(quadRegion* area, collisionHull* obj)
{
	AABB aabb = obj->getAABB();
	return  aabb.NW_Corner.x < area->NW_Corner.x &&
			aabb.NW_Corner.y < area->NW_Corner.y &&
			aabb.SE_Corner.x > area->SE_Corner.x &&
			aabb.SE_Corner.y > area->SE_Corner.y;
}

void quadTree::buildTree(std::vector<collisionHull*> targets)
{
	/*
	we have a set of collision hulls, each occupying some region of space, with some origin
	we will treat these as AABB for now in our broad phase.
	we will be successively subdividing our space (using a tree) into quadrants
	 
	for optimization purposes, only leave nodes will contain objects. this will be done
	by inserting particularrly large objects into the leave nodes of the smallest possible region they can occupy.
	*/

	/*
	next, we should devise a good algorithm to subdivide space such that:
	1. start at the root, test to see what region a given object falls into
		a. if the object falls into a specific region, try to insert it into that sub tree
		b. if it falls into multiple regions add it to both regions and terminate
		c. if it falls into none, don't add it to the tree at all (this would me that it's somehow outside the bounderies
		of our world).
	2. we repeate step 1 until it either reaches a leave node, or the maximum depth, in which case we add a leave node.
	*/
}