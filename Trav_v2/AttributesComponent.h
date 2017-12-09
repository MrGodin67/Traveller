#pragma once
#include "EntityComponentSystem.h"


class Defence : public Component
{
public:
	float max_defence;
	float current_defence;
	float bonus;
	float reverse_damage;

};
class Attack : public Component
{
	float timer;
	bool can_attack;
public:
	float speed;
	float rate;
	float damage;
	float range;
	float bonus;
	Entity* target_entity = nullptr;
	Attack() = default;
	Attack(const float& damage,const float& rate,const float& speed)
		:speed(speed),rate(rate),damage(damage),can_attack(true)
	{}
	void  Update(const float& dt)override
	{
		if (!can_attack)
		{
			can_attack = (timer += dt) > rate;
		}
		 if (can_attack)timer = 0.0f;
	}
	
	
};
class Vitality : public Component
{
public:
	float dexterity;
	float hit_points;
	float max_hitpoints;
	float regeneration_rate;
	float strength;
	float vitality() { return hit_points / max_hitpoints; }
};
class Experience : public Component
{
public:
	float aquired_exp;
	int level() { return (int)floor(aquired_exp); }
	float level_completed() { return aquired_exp / next_level; }
	float next_level;

};
class Magic : public Component
{
	float fire;
	float ice;
	float healing;
	float stun;
	float teleport;
};


