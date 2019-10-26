#include "entity.h"
#include "entityManager.h"

/*H******************************************************************
 * FILENAME: entityManager.cpp
 * AUTHOR: Zackary Finer
 * DATE: 10/26/2019
 *
 * DESCRIPTION:
 * This class is responsible for managing entities. That is, it must:
 * call entities update methods, delete entities when they "die", draw
 * entities, and add new entities to itself as needed.
 *
 * This is the "sprite manager" class for this project.
 *
 ********************************************************************/

entityManager::entityManager()
{}

void entityManager::addSprite(entity* target)
{
	if (contents.find(target->getID())==contents.end())
		contents.insert({ target->getID(), target });
}

EID entityManager::getPlayer() const { return playerEnt; }

void entityManager::deleteSprite(EID key)
{
	if (contents.find(key) != contents.end())
		delete contents[key];
	contents.erase(key);
}
void entityManager::deleteSprite(entity* target)
{
	deleteSprite(target->getID());
}

void entityManager::draw()
{
	for (auto pair : contents) // for every id, sprite* in our table
	{
		pair.second->draw(); // draw the sprite (second value in the pair).
	}
}

entity* entityManager::getSprite(EID key)
{
	auto result = contents.find(key);
	if (result == contents.end())
		return nullptr;
	return result->second;
}

bool entityManager::containsSprite(EID key)
{
	return !(contents.find(key) == contents.end());
}
bool entityManager::containsSprite(entity* target)
{
	return containsSprite(target->getID());
}

void entityManager::update()
{
	for (auto pair : contents)
	{
		pair.second->update();
	}

	auto it = contents.begin();
	while (it != contents.end())
	{
		float lt = it->second->getLifeTime();
		if ((lt > 0.0f && it->second->getAge() > lt) || it->second->isDead()) // when our entities lifetime is up
		{

			delete it->second; // de-allocate the entity
			it = contents.erase(it); // remove it from the table, then update our iterator
		}
		else
		{
			it++; //otherwise, just move on
		}
	}
}

void entityManager::clear()
{
	for (auto pair : contents)
	{
		entity* ent = pair.second;
		delete ent;
	}
	contents.clear();
}

entityManager::~entityManager()
{
	// you should manually call clear in the destructor instead of this
	//either that, or just have the collision detector be aggregated by this
	for (auto pair : contents) // There is an issue here, as the entity manager needs to be destroyed before the collision engine.
	{
		entity* ent = pair.second;
		delete ent;
	}
}

void entityManager::handleKeyPressed(int key)
{
	for (auto pair : contents)
	{
		pair.second->onKeyPress(key);
	}
}

void entityManager::handleKeyRelease(int key)
{
	for (auto pair : contents)
	{
		pair.second->onKeyRelease(key);
	}
}

int entityManager::getCount()
{
	return contents.size();
}

void entityManager::setPlayer(EID p)
{
	playerEnt = p;
}