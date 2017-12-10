#pragma once




class Component;
class Entity;
class EntityManager;
enum GroupLabels;
using ComponentID = std::size_t;
using GroupID = std::size_t;

inline ComponentID getComponentTypeID()
{
	static ComponentID cID = 0;
	return cID++;
}
template <typename T>
inline ComponentID getComponentTypeID() noexcept
{
	static ComponentID id = getComponentTypeID();
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
	static EntityManager* manager;
public:
	Entity() = default;
	static void SetManager(EntityManager* mgr);
	virtual ~Entity() {}
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


