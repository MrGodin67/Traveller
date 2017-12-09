#include "stdafx.h"
#include "SpriteComp.h"
#include "Locator.h"
Sprite::Sprite(ID2D1Bitmap& image, const RectF& srcRect)
	:image(&image),srcRect(srcRect)
{
	
}

void Sprite::Update(const float & dt)
{
	destRect = transform->Rect();
	if (animated)
	{
		p_currentAnimation->timer += dt*1000.0f;

		int indexX = static_cast<int>(
			(int)(p_currentAnimation->timer / (float)p_currentAnimation->speed) %
			p_currentAnimation->indices.size());


		float w = transform->Rect().GetWidth();
		float h = transform->Rect().GetHeight();
		srcRect.top = h * p_currentAnimation->indexY;
		srcRect.left = w * p_currentAnimation->indices[indexX];
		srcRect.right = srcRect.left + w;
		srcRect.bottom = srcRect.top + h;
	}
}

void Sprite::Init()
{
	transform = &owner->Get<Transform>();
	
}

void Sprite::Draw()
{
	Locator::Graphics()->DrawSprite(transform->Matrix(),
		transform->Rect().ToD2D(), image, &srcRect.ToD2D(),transparency);
}

void Sprite::AddAnimationSequence(const std::string & id, const AnimationSeq & seq)
{
	animated = true;
	auto& result = animations.find(id);
	if (result == animations.end())
	{
		animations[id] = seq;
	}

}

void Sprite::SetCurrentAnimationSeq(const std::string & id)
{
	auto& result = animations.find(id);
	if (result != animations.end())
	{
		p_currentAnimation = &animations[id];
	}
}

void Sprite::Fade(const float & val)
{
	transparency = val;
}
