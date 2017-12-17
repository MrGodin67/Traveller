#pragma once
#include "Components.h"
class Ammo :
	public Component
{
	float acceleration;
	float damage;
	float areaOfEffect;
public:
	Ammo();
	Ammo(const float& speed, const float& dmg, const float& areaOfEffect)
		:acceleration(speed), damage(dmg), areaOfEffect(areaOfEffect)
	{}
	~Ammo();
	void Init()override
	{
		owner->Get<Transform>().acceleration = acceleration;
	}
};

