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
public:
	quadRegion *NE, *SE, *SW, *NW;
	glm::vec2 NW_Corner, SE_Corner;
};

struct quadRegionLeave : public quadRegion
{
	std::unordered_map<EID, collisionHull*> content;
};

class quadTree
{
private:
	glm::vec2 worldSize = glm::vec2(1000,1000);
	int max_Depth = 8;
	bool testBound(quadRegion*, collisionHull*);
public:
	quadRegion* root;
	void update();
	std::vector<collisionHull*> getNeigbors(quadRegionLeave*);
	void buildTree(std::vector<collisionHull*>);
	void removeEntry(collisionHull*);
	void addEntry(collisionHull*);
	std::unordered_map<EID, collisionHull*> content; // note: we are going to use this to enumerate/search all entries without duplicates
};