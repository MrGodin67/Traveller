#include "stdafx.h"
#include "Body.h"
#include "Locator.h"
void Body::Init()
{
	transform = &owner->Get<Transform>();
	transform->Resize(Vec2f(m_image->GetSize().width, m_image->GetSize().height));
}

void Body::Draw()
{
	Locator::Graphics()->DrawSprite(transform->Matrix(),
		transform->Rect().ToD2D(), m_image);
}
