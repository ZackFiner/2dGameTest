#include "entity.h"
#include "entityManager.h"

entityManager::entityManager()
{}

void entityManager::addSprite(entity* target)
{
	contents.insert({ target->getID(), target });
}

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

entityManager::~entityManager()
{
	for (auto pair : contents)
	{
		delete pair.second;
	}
}