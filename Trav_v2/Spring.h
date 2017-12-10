#pragma once
#include "Components.h"
class FollowCompanion :
	public Component
{
	Entity* host;
	Entity* weight;
	float separation = 64.0f;
	float tension = 0.07f;
	float friction = 0.978f;
	float maxSeparation;
public:
	FollowCompanion();
	FollowCompanion(Entity* companionToFollow,float maxSepartionBeforeReappear)
		: host(companionToFollow),maxSeparation(maxSepartionBeforeReappear)
	{}
	~FollowCompanion();
	virtual void Update(const float& dt)override;
	virtual void Init()override;
};
class SpringFrom :
	public Component
{
	Entity* host;
	Entity* weight;
	float separation = 164.0f;
	float tension = 0.7f;
	float friction = 0.978f;
public:
	SpringFrom();
	SpringFrom(Entity* weight)
		:weight(weight)
	{}
	~SpringFrom();
	virtual void Update(const float& dt)override;
	virtual void Init();
};
