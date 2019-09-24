#pragma once
#include "ofMain.h"
#include "EID.h"

/*H******************************************************************
 * FILENAME: quadTree.h
 * AUTHOR: Zackary Finer
 *
 * DESCRIPTION:
 * This file contains an implementation of a quad tree. The pseudocode
 * (not the actual code) was taken from the wikipedia article:
 * https://en.wikipedia.org/wiki/Quadtree
 *
 * The quadtree is used in close conjunction with the collision hull
 * object, and serves to provide an efficient way to query objects
 * for collision.
 *
 * masterQuad is essentially a wrapper class around the quadTree class,
 * and adds a fast lookup table for objects aswell as methods to remove
 * objects from the tree quickly.
 */

static int max_tree_depth = 8;
class collisionHull;
class quadTree
{
private:
	int max_Depth = 8;
	bool testInBound(quadTree*, collisionHull*);
	bool testInBound(const glm::vec2&, const glm::vec2&, collisionHull*);
	void queryTreeRec(collisionHull*, std::vector<collisionHull*>*);
public:
	void drawDebug();
	quadTree *NE = nullptr, *SE = nullptr, *SW = nullptr, *NW = nullptr, *parent = nullptr;

	glm::vec2 NW_Corner, SE_Corner;
	std::pair<glm::vec2, glm::vec2> getSector(int);
	unordered_map<EID, collisionHull*> content;
	std::vector<collisionHull*> queryTree(collisionHull*);//returns all collision hulls which interset the given collision hull
	quadTree* addEntry(collisionHull*, int);
	~quadTree();
	
};

class masterQuad
{

	glm::vec2 worldSize = glm::vec2(1000, 1000);
	quadTree* root;
	std::unordered_map<EID, std::pair<glm::vec2, float>> deltas;
	std::unordered_map<EID, std::pair<collisionHull*, quadTree*>> content; // note: we are going to use this to enumerate/search all entries without duplicates
	collisionHull* popFromTree(collisionHull*);
	void siftUpTree(collisionHull*);
public:
	void drawDebug();
	masterQuad();
	bool autoDetectUpdates = true;
	void update();
	void buildTree(std::vector<collisionHull*>);
	std::vector<collisionHull*> queryCollision(collisionHull*);
	void addEntry(collisionHull*);
	void removeEntry(collisionHull*);
	~masterQuad();
};