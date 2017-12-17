#include "stdafx.h"
#include "Path.h"


Path::Path()
{
}

Path::Path(const std::vector<Vec2f>& data)
	:positions(data)
{
}


Path::~Path()
{
}

void Path::Init()
{
	transform = &owner->Get<Transform>();
	currentIndex = 0llu;
	float angle = GetAngleBetweenPoints(transform->Center(), positions[currentIndex]);
	transform->Rotate(angle);
	transform->velocity = transform->Facing();
}

void Path::Update(const float & dt)
{
	if (moving)
	{
		
		float lenSq = (transform->Center() - positions[currentIndex]).LenSq();
		if (lenSq < sq<float>((transform->acceleration*dt)))
		{
			currentIndex++;
			done = currentIndex >= positions.size();
			if (!done)
			{
				float angle = GetAngleBetweenPoints(transform->Center(), positions[currentIndex]);
				transform->Rotate(angle);
				transform->velocity = transform->Facing();
			}
			else
			{
				transform->velocity = { 0.0f,0.0f };
				//owner->Remove<Path>();
				return;
			}
		}
	}
}

void Path::Draw()
{
	for (int i : Iterate(0, positions.size()-1))
	{
		D2DPointF pts[2] = { positions[i].ToD2DPointF() , positions[i + 1].ToD2DPointF() };
		Locator::Graphics()->DrawLine(D2D1::Matrix3x2F::Identity(), pts, D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f));
	}
	
}

bool Path::Completed() const
{
	return done;
}

bool Path::Moving() const
{
	return moving;
}

void Path::Moving(const bool & value)
{
	moving = value;
}
