#pragma once
#include "ofMain.h"
#include "EID.h"

static int max_tree_depth = 8;
class collisionHull;
class quadTree
{
private:
	int max_Depth = 8;
	bool testInBound(quadTree*, collisionHull*);
	bool testInBound(const glm::vec2&, const glm::vec2&, collisionHull*);
	bool testIntersect(const glm::vec2&, const glm::vec2&, collisionHull*);
	bool insertObject(quadTree*, collisionHull*, int);
public:
	quadTree *NE = nullptr, *SE = nullptr, *SW = nullptr, *NW = nullptr, *parent = nullptr;
	glm::vec2 NW_Corner, SE_Corner;
	std::pair<glm::vec2, glm::vec2> getSector(int);
	unordered_map<EID, collisionHull*> content;
	void update();
	std::vector<collisionHull*> queryTree(collisionHull*);//returns all collision hulls which interset the given collision hull
	void removeEntry(collisionHull*);
	quadTree* addEntry(collisionHull*, int);
	~quadTree();
	
};

class masterQuad
{

	glm::vec2 worldSize = glm::vec2(1000, 1000);
	quadTree* root;
	std::unordered_map<EID, std::pair<collisionHull*, quadTree*>> content; // note: we are going to use this to enumerate/search all entries without duplicates
	void buildTree(std::vector<collisionHull*>);
};