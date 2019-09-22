#include "quadTree.h"
#include "entity.h"
#include "collisionHull.h"

void quadTree::buildTree(std::vector<collisionHull*> targets)
{
	/*
	 we have a set of collision hulls, each occupying some region of space, with some origin
	 we will treat these as AABB for now in our broad phase.
	 we will be successively subdividing our space (using a tree) into quadrants
	 
	 for optimization purposes, only leave nodes will contain objects. this will be done
	 by inserting particularrly large objects into the leave nodes of the smallest possible region they can occupy.
	*/
}