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
	// two AABB intersect if at least one of their edges passes through the other
	AABB aabb = obj->getAABB();
	return  aabb.NW_Corner.x >= bottomCorner.x && //make sure their max x is higher than our min x
			aabb.NW_Corner.y >= bottomCorner.y && //make sure their max y is higher than our min y
			aabb.SE_Corner.x <= topCorner.x && //make sure their min x is less than our max x
			aabb.SE_Corner.y <= topCorner.y; //make sure our min y is less than our max
}

void masterQuad::buildTree(std::vector<collisionHull*> targets)
{

	root = new quadTree();
	root->NW_Corner = worldSize / 2;
	root->SE_Corner =-worldSize / 2;
	for (auto obj : targets)
	{
		auto site = root->addEntry(obj);
		content.insert({ obj->owner->getID(), {obj, site} });
	}
}

quadTree* quadTree::addEntry(collisionHull* obj, int depth = 0)
{
	// test if any of our child nodes completely encapsulates the object
	// if it doesnt, just add the object to our own contents
	if (depth >= max_tree_depth)
	{
		content.insert({ obj->owner->getID(), obj });
		return this;
	}

	bool addedToChild = false;
	for (int i = 0; i < 4; i++)
	{
		auto sector = getSector(i);
		if (addedToChild = testInBound(sector.first, sector.second, obj))
		{
			quadTree** region;
			switch (i) {
			case 0:
				region = &NW;
				break;
			case 1:
				region = &SW;
				break;
			case 2:
				region = &SE;
				break;
			case 3:
				region = &NE;
				break;
			}

			if ((*region) == nullptr)
			{
				(*region) = new quadTree();
				(*region)->parent = this;
				(*region)->NW_Corner = sector.first;
				(*region)->SE_Corner = sector.second;
			}
			return (*region)->addEntry(obj, depth++); //descend deeper into the tree
		}
	}

	if (!addedToChild) // if the object is too big to be put into a subdivision, or just doesn't fit into one
	{
		content.insert({obj->owner->getID(), obj}); // put it into this node
		return this;
	}
	
}