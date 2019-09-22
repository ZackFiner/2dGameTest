#pragma once
#include "ofMain.h"
#include "EID.h"
class collisionHull;
class quadRegion
{
	/*
	I've opted to use a hash map here, but this may not be the most efficient, as hash maps
	tend to under perform when we're doing a bunch of insertions/deletions. I may consider using
	a ordered map (red black tree) instead. Or, if the overhead ends up being too much, maybe just a regular
	vector.
	*/
	std::unordered_map<EID, collisionHull*> content;
	quadRegion *NE, *SE, *SW, *NW;
	glm::vec2 NW_Corner, SE_Corner;
};

class quadTree
{
	quadRegion* root;
	void update();
	std::vector<collisionHull*> getNeigbors(quadRegion*);
	void buildTree(std::vector<collisionHull>*);
	void removeEntry(collisionHull*);
	void addEntry(collisionHull*);
};