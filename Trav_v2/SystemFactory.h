
#pragma once

#include "system.h"
using SystemID = std::size_t;


inline SystemID getUniqueSystemTypeID()
{
	static SystemID cID = 0;
	return cID++;
}
template <typename T>
inline SystemID getSystemTypeID() noexcept
{
	static_assert(std::is_base_of<System, T>::value,
		"T must must inherit from System");
	static SystemID id = getUniqueSystemTypeID();
	return id;
}

constexpr static  SystemID maxSystems = 32;

using SystemBitSet = std::bitset<maxSystems>;
using SystemArray = std::array<System*, maxSystems>;



class SystemFactory
{
	SystemBitSet m_systemBitset;
	SystemArray m_systemArray;
	std::vector < std::unique_ptr<System> > m_systems;
	template <typename SystemType>
	bool Has()const
	{
		return m_systemBitset[getSystemTypeID<SystemType>()];
	}
public:
	SystemFactory();
	~SystemFactory();
	template <typename SystemType, typename... SystemArgs>
	SystemType& Make(SystemArgs&&... mArgs)
	{
		
		assert(!Has < SystemType >());
		
		SystemType* sys(new SystemType(std::forward<SystemArgs>(mArgs)...));
		std::unique_ptr<System> uPtr{ sys };
		m_systems.emplace_back(std::move(uPtr));
		m_systemArray[getSystemTypeID<SystemType>()] = sys;
		m_systemBitset[getSystemTypeID<SystemType>()] = true;
		return *sys;
	}
	template<typename SystemType>
	SystemType* Get()
	{
		assert(Has < SystemType >());
		return (SystemType*)m_systemArray[getSystemTypeID<SystemType>()];
		
		
	}
};

