#pragma once
#include <unordered_map>
#include "EID.h"

/*H******************************************************************
 * FILENAME: entityManager.h
 * AUTHOR: Zackary Finer
 *
 * DESCRIPTION:
 * This class is responsible for managing entities. That is, it must:
 * call entities update methods, delete entities when they "die", draw
 * entities, and add new entities to itself as needed.
 *
 * This is the "sprite manager" class for this project.
 *
 ********************************************************************/


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
	EID playerEnt;
public:
	
	entityManager();
	void addSprite(entity*);
	EID getPlayer() const;
	void setPlayer(EID);
	void deleteSprite(entity*);
	void deleteSprite(EID);
	void update();
	void clear();
	int getCount();
	void draw();

	entity* getSprite(EID);
	void handleKeyPressed(int key);
	void handleKeyRelease(int key);
	bool containsSprite(EID);
	bool containsSprite(entity*);
	~entityManager();
};