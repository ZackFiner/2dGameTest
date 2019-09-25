#include "EID.h"

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