#pragma once
#include <thread>
#include <mutex>

class EID
{
	private:
		static std::mutex accessLock;
		static unsigned int lastID;
		static unsigned int getNewID();
	public:
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