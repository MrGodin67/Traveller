#pragma once
#include "Components.h"

class Light : public Component
{
	float range;
public:
	Light(const float& range)
		:range(range)
	{}
	float Range()const
	{
		return range;
	}
	void Range(const float& val)
	{
		range = val;
	}
};