#pragma once
#include "ofMain.h"
#include "EID.h"
class collisionHull;
class quadTree
{
private:
	glm::vec2 worldSize = glm::vec2(1000,1000);
	int max_Depth = 8;
	bool testInBound(quadTree*, collisionHull*);
	bool testInBound(const glm::vec2&, const glm::vec2&, collisionHull*);
	bool testIntersect(const glm::vec2&, const glm::vec2&, collisionHull*);
	bool insertObject(quadTree*, collisionHull*, int);
public:
	quadTree *NE = nullptr, *SE = nullptr, *SW = nullptr, *NW = nullptr;
	glm::vec2 NW_Corner, SE_Corner;
	std::pair<glm::vec2, glm::vec2> getSector(int);
	quadTree* root;
	void update();
	std::vector<collisionHull*> getNeigbors(collisionHull*);
	void buildTree(std::vector<collisionHull*>);
	void removeEntry(collisionHull*);
	void addEntry(collisionHull*);
	std::unordered_map<EID, collisionHull*> content; // note: we are going to use this to enumerate/search all entries without duplicates
};