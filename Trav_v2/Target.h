#pragma once
#include "Components.h"
class Target :
	public Component
{
	Entity* target = nullptr;
	bool canFire;
	bool targetAquired;
public:
	Target();
	Target(Entity* target)
		:target(target)
	{}
	~Target();
	Vec2f TargetCenter()
	{
		return target->Get<Transform>().Center();
	}
	void TargetAquired(const bool& val) 
	{ targetAquired = val; }

};

