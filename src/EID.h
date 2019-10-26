#pragma once
#include <thread>
#include <mutex>
/*H******************************************************************
 * FILENAME: EID.h
 * AUTHOR: Zackary Finer
 * DATE: 10/26/2019
 *
 * DESCRIPTION:
 * EID (Entity IDentifier) is class used to uniquely identify an entity
 * in our game. It is also responsible for generating new unique 
 * identification numbers.
 * 
 * Ontop of this, the header includes an injected std::hash template
 * specialization for EID so that objects of this class can be used
 * as the key in unordered_maps (hash maps).
 *
 ********************************************************************/
class EID
{
	private:
		static std::mutex accessLock;
		static unsigned int lastID;
		static unsigned int getNewID();
		EID(int id);
	public:
		static EID nilID();
		EID(); // we'll do something neat, and make the constructor automatically create a new id.
		EID(const EID&);
		EID& operator=(const EID&);
		bool operator==(const EID&);
		friend bool operator==(const EID&, const EID&);
		unsigned int id;
};

namespace std {
	template<> struct hash<EID>
	{
		size_t operator()(const EID & id) const noexcept
		{
			return hash<unsigned int>()(id.id); // very, very simple integer hash for now: we may want to make this more complicated.
		}
	};
}