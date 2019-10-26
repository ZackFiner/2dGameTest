#include "EID.h"

/*H******************************************************************
 * FILENAME: EID.cpp
 * AUTHOR: Zackary Finer
 *
 * DESCRIPTION:
 * EID (Entity IDentifier) is class used to uniquely identify an entity
 * in our game. It is also responsible for generating new unique
 * identification numbers.
 *
 * I've tried to implement this class atomically, although I have not 
 * tested how well it works.
 *
 ********************************************************************/

std::mutex EID::accessLock;
unsigned int EID::lastID;
unsigned int EID::getNewID()
{
	unsigned int id;
	accessLock.lock();
	
	id = lastID++;// maybe handle overflow at somepoint aswell

	accessLock.unlock();
	return id;
}
EID::EID(int _id) { id = _id; }
EID EID::nilID() {
	EID nil(-1);
	return nil;
}
EID::EID() : id(getNewID())
{}

EID::EID(const EID& other) : id(other.id)
{}

EID& EID::operator=(const EID& other)
{
	id = other.id;
	return *this;
}

bool EID::operator==(const EID& other)
{
	return id == other.id;
}

bool operator==(const EID& o1, const EID& o2)
{
	return o1.id == o2.id;
}