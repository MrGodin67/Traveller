#include "stdafx.h"
#include "Spring.h"


FollowCompanion::FollowCompanion()
{
}


FollowCompanion::~FollowCompanion()
{
}



void FollowCompanion::Update(const float & dt)
{
	Vec2f dist = (host->Get<Transform>().position - weight->Get<Transform>().position);
	float len = dist.Len();
	if (len > maxSeparation)
	{
		weight->Get<Transform>().position = host->Get<Transform>().position;
		dist = (host->Get<Transform>().position - weight->Get<Transform>().position);
	}
	dist.ConfineLength(len - separation);
	weight->Get<Transform>().velocity = dist*tension;
	

}

void FollowCompanion::Init()
{
	weight = owner;
}

SpringFrom::SpringFrom()
{
}


SpringFrom::~SpringFrom()
{
}



void SpringFrom::Update(const float & dt)
{
	Vec2f dist = (owner->Get<Transform>().position - weight->Get<Transform>().position);
	dist.ConfineLength(dist.Len() - separation);
	weight->Get<Transform>().velocity = dist*tension;
	weight->Get<Transform>().CapVelocity();

}

void SpringFrom::Init()
{
	host = owner;
}

