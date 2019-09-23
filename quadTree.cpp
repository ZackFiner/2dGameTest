#include "quadTree.h"
#include "entity.h"
#include "collisionHull.h"
#include "collisionUtil.h"

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
				(*region) = new quadTree(); //this doesn't really need to be dynamically allocated
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

void quadTree::queryTreeRec(collisionHull* obj, std::vector<collisionHull*>* intersectsSoFar) // returns all collision hulls with AABBs intersecting the specified collision hull.
{

	if (!collisionUtil::AABBIntersect(NW_Corner, SE_Corner, obj)) //if the aabb doesn't intersect this region
		return; //terminate: don't bother searching things that can't possibly collide

	for (auto o_obj : content) // test all collisions at this node's level
	{
		if (collisionUtil::AABBIntersect(o_obj.second, obj))
			intersectsSoFar->push_back(o_obj.second);
	}
	// then test all collisions for child level
	if (NW!=nullptr)
		NW->queryTreeRec(obj, intersectsSoFar);
	if (NE!=nullptr)
		NE->queryTreeRec(obj, intersectsSoFar);
	if (SE!=nullptr)
		SE->queryTreeRec(obj, intersectsSoFar);
	if (SW!=nullptr)
		SW->queryTreeRec(obj, intersectsSoFar);

}

std::vector<collisionHull*> quadTree::queryTree(collisionHull* obj)
{
	std::vector<collisionHull*> collisions;
	queryTreeRec(obj, &collisions);
	return collisions;
}

quadTree::~quadTree()
{
	// delete all child trees
	if (NW != nullptr)
		delete NW;
	if (NE != nullptr)
		delete NE;
	if (SE != nullptr)
		delete SE;
	if (SW != nullptr)
		delete SW;
}



void masterQuad::buildTree(std::vector<collisionHull*> targets)
{

	root = new quadTree();
	root->NW_Corner = worldSize / 2;
	root->SE_Corner = -worldSize / 2;
	for (auto obj : targets)
	{
		auto site = root->addEntry(obj);
		content.insert({ obj->owner->getID(), {obj, site} });
	}
}

collisionHull* masterQuad::popFromTree(collisionHull* obj)
{
	quadTree* holder = content[obj->owner->getID()].second;
	holder->content.erase(obj->owner->getID()); // remove the object from the trees content
	quadTree* snip_point = holder;
	quadTree* snip_child = nullptr;

	while ( //here, we travel up the tree, to see how far up the branch we can snip
		snip_point->content.size() == 0 &&
		snip_point->NE == nullptr &&
		snip_point->SE == nullptr &&
		snip_point->NW == nullptr &&
		snip_point->SW == nullptr
		)
	{
		snip_child = snip_point;
		snip_point = snip_point->parent;
	}

	if (snip_child != nullptr); // i should have used vectors for the child nodes, you'll see why below
	{
		if (snip_point->NE == snip_child)
		{
			snip_point->NE = nullptr;
			delete snip_child;
		}
		else if (snip_point->NW == snip_child)
		{
			snip_point->NW = nullptr;
			delete snip_child;
		}
		else if (snip_point->SE == snip_child)
		{
			snip_point->SE = nullptr;
			delete snip_child;
		}
		else if (snip_point->SW == snip_child)
		{
			snip_point->SW = nullptr;
			delete snip_child;
		}
	}
	return obj;
}

void masterQuad::removeEntry(collisionHull* obj)
{
	if (content.find(obj->owner->getID()) != content.end())
	{
		popFromTree(obj);
		content.erase(obj->owner->getID()); // finally, we remove the object from our fast lookup table
		deltas.erase(obj->owner->getID());
	}
}

void masterQuad::siftUpTree(collisionHull* obj)
{
	popFromTree(obj); // take the entry out of our quad tree
	quadTree* location = root->addEntry(obj); //add it to our tree
	content[obj->owner->getID()].second = location; //update the fast lookup table
}

void masterQuad::update()
{
	if (autoDetectUpdates)
	{
		if (deltas.size() <= 0) // if we haven't initialized our delta's
		{
			for (auto obj : content)
				deltas.insert({ obj.first, { obj.second.first->pos, obj.second.first->rot } });
			return;
		}
		for (auto obj : content)
		{
			auto hull = obj.second.first;
			auto pair = deltas[obj.first];
			if (pair.first != hull->pos || pair.second != hull->rot) // if an object has change it's position or rotation (thus changing what region it should belong to)
			{
				// here, we remove the object, then re-insert it
				siftUpTree(hull);
			}
		}
		for (auto obj : content)
			deltas[obj.first] = { obj.second.first->pos, obj.second.first->rot };
	}
}