#pragma once
#include "Components.h"
class EntityContainer
{
	std::vector<Entity*> entities;
public:
	EntityContainer();
	~EntityContainer();
};

