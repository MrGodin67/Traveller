#pragma once



#include "Types.h"
class Component;
class Entity;
class EntityManager;
using ComponentID = std::size_t;
using GroupID = std::size_t;

inline ComponentID getUniqueComponentTypeID()
{
	static ComponentID cID = 0;
	return cID++;
}
template <typename T>
inline ComponentID getComponentTypeID() noexcept
{
	static_assert(std::is_base_of<Component, T>::value,
		"T must must inherit from Component");
	static ComponentID id = getUniqueComponentTypeID();
	return id;
}

constexpr static  ComponentID maxComponents = 32;
constexpr static GroupID maxGroups = 32;
using ComponentBitSet = std::bitset<maxComponents>;
using ComponentArray = std::array<Component*, maxComponents>;
using GroupBitSet = std::bitset<maxGroups>;




class Component
{

public:
	virtual ~Component() {}
	Entity* owner;
	virtual void Update(const float& dt) {}
	virtual void Init() {};
	virtual void Draw() {};
	virtual void Fade(const float& dt) {}
};

class Entity
{
protected:
	ComponentBitSet m_componentBitset;
	ComponentArray m_componentArray;
	GroupBitSet m_groupBitSet;
	std::vector<std::unique_ptr<Component>> m_components;
	bool m_active = true;
	bool m_selected = false;
	std::wstring name;
	std::wstring description;
	EntityManager& manager;
public:
	Entity(EntityManager& manager)
		:manager(manager) {};
	virtual ~Entity() {}
	// Virtual functions
	virtual void Draw()
	{
		for (auto& comp : m_components)
			comp->Draw();
	};
	virtual void Update(const float& dt)
	{
		for (auto& comp : m_components)
			comp->Update(dt);
	};
	virtual bool OnMouseOver(const int& mX, const int& mY) { return false; };
	virtual bool OnMouseClick(const int& mX, const int& mY) { return false; };
	virtual void DiffuseAlpha(const float& val);
	//~
	bool Selected()const { return m_selected; }
	bool Active()const { return m_active; };
	void Destroy() { m_active = false; }
	template <typename Type>
	void Remove()
	{
		// cannot remove transform
     	if (std::is_same<Type, Transform>::value)
			return;
				
		bool result = Has<Type>();
		if (result)
		{
			m_components.erase(std::remove_if(std::begin(m_components), std::end(m_components),
				[=](const std::unique_ptr<Component>& comp)
			{
				return comp.get() == m_componentArray[getComponentTypeID<Type>()];
			})
				, std::end(m_components));
			m_componentArray[getComponentTypeID<Type>()] = nullptr;
			m_componentBitset[getComponentTypeID<Type>()] = false;
		}
	}
	template <typename Type>
	bool Has()const
	{
		return m_componentBitset[getComponentTypeID<Type>()];
	}
	
	template <typename Type, typename... TArgs>
	Type& Add(TArgs&&... mArgs)
	{
		assert(!Has<Type>());
		Type* comp(new Type(std::forward<TArgs>(mArgs)...));
		std::unique_ptr<Component> uPtr{ comp };
		m_components.emplace_back(std::move(uPtr));
		m_componentArray[getComponentTypeID<Type>()] = comp;
		m_componentBitset[getComponentTypeID<Type>()] = true;
		comp->owner = this;
		comp->Init();
		
		return *comp;
	}
	
	template<typename Type>
	Type& Get()const
	{
		
		auto ptr(m_componentArray[getComponentTypeID<Type>()]);
		return *static_cast<Type*>(ptr);
	}

	bool HasGroup(const GroupID& id)const
	{
		return m_groupBitSet[id];
	}
	void AddGroup(const GroupID& id);
	void RemoveGroup(const GroupID& id)
	{
		m_groupBitSet[id] = false;
	}
};


