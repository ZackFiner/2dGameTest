#include "EID.h"

//namespace std {
//	/*
//		This overide is necessary in order for our ID to work properly in the unordered hash map.
//		Source: https://en.cppreference.com/w/cpp/utility/hash
//
//		We use the injected std::hash template specialization for convenience; i don't feel like adding a third parameter
//		for the hash function every time i try to insert.
//	*/
//	template <>
//	struct hash<EID>
//	{
//		size_t operator()(const EID & id) const noexcept
//		{
//			return hash<unsigned int>()(id.id); // very, very simple integer hash for now: we may want to make this more complicated.
//		}
//	};
//}
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