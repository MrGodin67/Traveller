#include "stdafx.h"
#include "Animation.h"


Animation::Animation()
{
}




Animation::~Animation()
{
}

void Animation::Init()
{
	transform = &owner->Get<Transform>();
}

void Animation::Draw()
{
	Locator::Graphics()->DrawSprite(transform->Matrix(),
		transform->Rect().ToD2D(),image, &srcRect.ToD2D(), transparency);
}

void Animation::Update(const float & dt)
{
	if (active)
	{
		timer += dt;
		if (timer >= interval)
		{
			timer = 0.0f;
			int row = index / columns;
			int col = index % columns;
			index++;
			if (index >= frames)
			{
				if (loop)
					index = 0;
				else
				{
					done = true;
					return;
				}
			}

			srcRect = {
				frameSize * (float)col,
				frameSize * (float)row,
				frameSize * (float)(col + 1),
				frameSize * (float)(row + 1)
			};
		}
	}
	
}

void Animation::Fade(const float & val)
{
	transparency = val;
}

void Animation::Stop()
{
	active = false;
}

void Animation::Start()
{
	active = true;
}

bool Animation::Done() const
{
	return done;
}
