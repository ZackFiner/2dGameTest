#pragma once
#include <unordered_map>
#include "EID.h"
class entity;
class entityManager
{
	/*
	What do we want?
	We want a data structure that will allow for rapid access, traversal, and deletion/insertion. We don't
	necessarily need things to be sorted: just organized in way that makes it easy for us to access data.

	How are we going to do that?
	My proposal: we use an unordered map, where the key is a sprite ID, and the value is a pointer to a dynamically allocated
	sprite.
	
	Why?
	By using an unordered map (essentially a hash map), we are able to access entries randomly very quickly via an entity
	ID. Ontop of this, the STL provides iterators for the map which will make traversal very easy. Removal is also
	near constant time complexity.

	*/

private:
	std::unordered_map<EID, entity*> contents;
public:
	entityManager();
	void addSprite(entity*);

	void deleteSprite(entity*);
	void deleteSprite(EID);

	void draw();

	entity* getSprite(EID);

	bool containsSprite(EID);
	bool containsSprite(entity*);
	~entityManager();
};