#include "quadTree.h"
#include "entity.h"
#include "collisionHull.h"

std::pair<glm::vec2, glm::vec2> quadTree::getSector(int region)
{
	/*
	----------
	| 0  | 3 |
	|--------
	| 1  | 2 |
	----------
	*/
	glm::vec2 mid = (SE_Corner+NW_Corner) / 2;
	switch (region)
	{
	case 0:
		return { NW_Corner, mid };
	case 1:
		return { glm::vec2(NW_Corner.x, mid.y), glm::vec2(mid.x, SE_Corner.y) };
	case 2:
		return { mid, SE_Corner };
	case 3:
		return { glm::vec2(mid.x, NW_Corner.y), glm::vec2(SE_Corner.x, NW_Corner.y) };
	}
}

bool quadTree::testInBound(quadTree* area, collisionHull* obj)
{
	AABB aabb = obj->getAABB();
	return  aabb.NW_Corner.x < area->NW_Corner.x &&
			aabb.NW_Corner.y < area->NW_Corner.y &&
			aabb.SE_Corner.x > area->SE_Corner.x &&
			aabb.SE_Corner.y > area->SE_Corner.y;
}

bool quadTree::testInBound(const glm::vec2& topCorner, const glm::vec2& bottomCorner, collisionHull* obj)
{
	AABB aabb = obj->getAABB();
	return  aabb.NW_Corner.x < topCorner.x &&
			aabb.NW_Corner.y < topCorner.y &&
			aabb.SE_Corner.x > bottomCorner.x &&
			aabb.SE_Corner.y > bottomCorner.y;
}

bool quadTree::testIntersect(const glm::vec2& topCorner, const glm::vec2& bottomCorner, collisionHull* obj)
{
	AABB aabb = obj->getAABB();
	
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
	
	/*
	When we're building our tree, we will be adding nodes as we go.
	In order to ensure that all leave nodes contain their parent nodes content, as we build we will maintain a stack of items from the parent.

	Thus, once we reach the leave node level, we can simply pop all items in this stack into the child leaves.
	*/
	root = new quadTree();
	root->NW_Corner = worldSize / 2;
	root->SE_Corner =-worldSize / 2;
	for (auto obj : targets)
	{
		insertObject(root, obj, 0);
	}
}

bool quadTree::insertObject(quadTree* currentRoot, collisionHull* obj, int depth)
{
	for (int i = 0; i < 4; i++)
	{
		auto sector = currentRoot->getSector(i);
		if (testInBound(sector.first, sector.second, obj))
		{
			quadTree** region;
			switch (i) {
			case 0:
				region = &(currentRoot->NW);
				break;
			case 1:
				region = &(currentRoot->SW);
				break;
			case 2:
				region = &(currentRoot->SE);
				break;
			case 3:
				region = &(currentRoot->NE);
				break;
			}

			if ((*region) == nullptr)
			{
				(*region) = new quadTree();
				(*region)->NW_Corner = sector.first;
				(*region)->SE_Corner = sector.second;
			}
			insertObject(*region, obj, depth++);
		}
	}
	
}